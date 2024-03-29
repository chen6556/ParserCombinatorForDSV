#include "ExpParser.hpp"
#include <iostream>
#include <sstream>



namespace ExpParser
{

void Importer::add()
{
    std::cout << '+' << ' ';
    _expression.push(Operator::ADD);
}

void Importer::sub()
{
    std::cout << '-' << ' ';
    _expression.push(Operator::SUB);
}

void Importer::mul()
{
    std::cout << '*' << ' ';
    _expression.push(Operator::MUL);
}

void Importer::div()
{
    std::cout << '/' << ' ';
    _expression.push(Operator::DIV);
}

void Importer::num(const int value)
{
    std::cout << value << ' ';
    _expression.push(value);
}

void Importer::solve()
{
    double temp;
    size_t count;
    while (!_expression.empty())
    {
        _cache.push_back(_expression.top());
        _expression.pop();
        count = _cache.size();
        while (count >= 3 && _cache[count - 1].index() == 0 
            && _cache[count - 2].index() == 0 && _cache[count - 3].index() == 1)
        {
            switch (std::get<Operator>(_cache[count - 3]))
            {
            case Operator::ADD:
                temp = std::get<double>(_cache[count - 1]) + std::get<double>(_cache[count - 2]);
                break;
            case Operator::SUB:
                temp = std::get<double>(_cache[count - 1]) - std::get<double>(_cache[count - 2]);
                break;
            case Operator::MUL:
                temp = std::get<double>(_cache[count - 1]) * std::get<double>(_cache[count - 2]);
                break;
            case Operator::DIV:
                temp = std::get<double>(_cache[count - 1]) / std::get<double>(_cache[count - 2]);
                break;
            }
            _cache.pop_back();
            _cache.pop_back();
            _cache.back() = temp;
            count = _cache.size();
        }
    }
    _cache.clear();
    std::cout << "= " << temp << std::endl;
}

static Importer importer;

static Action<void> add_a(&importer, &Importer::add);
static Action<void> sub_a(&importer, &Importer::sub);
static Action<void> mul_a(&importer, &Importer::mul);
static Action<void> div_a(&importer, &Importer::div);
static Action<int> num_a(&importer, &Importer::num);

Parser<char> space = ch_p(' ');

Parser<bool> Parsers::exper = std::ref(term) >>
    *(*space >> ((ch_p('+') >> std::ref(term))[add_a] | (ch_p('-') >> std::ref(term))[sub_a]));

Parser<bool> Parsers::term = std::ref(factor) >>
    *(*space >> ((ch_p('*') >> std::ref(factor))[mul_a] | (ch_p('/') >> std::ref(factor))[div_a]));

Parser<bool> Parsers::factor = *space >> (int_p()[num_a] | pair(ch_p('('), std::ref(exper),  *space >> ch_p(')')));


bool ExpParser::parse(std::string_view &stream)
{
    const bool result = Parsers::exper(stream);
    importer.solve();
    return result;
}

bool ExpParser::parse(std::ifstream &stream)
{
    std::stringstream sstream;
    sstream << stream.rdbuf();
    std::string str(sstream.str());
    std::string_view temp(str);
    return Parsers::exper(temp);
}


}