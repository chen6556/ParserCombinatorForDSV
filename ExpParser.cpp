#include "ExpParser.hpp"
#include "Parser.hpp"
#include <iostream>
#include <sstream>



namespace ExpParser
{

void Importer::add()
{
    std::cout << '+' << ' ';
}

void Importer::sub()
{
    std::cout << '-' << ' ';
}

void Importer::mul()
{
    std::cout << '*' << ' ';
}

void Importer::div()
{
    std::cout << '/' << ' ';
}

void Importer::num(const int value)
{
    std::cout << value << ' ';
}

static Importer importer;

static Action<void> add_a(&importer, &Importer::add);
static Action<void> sub_a(&importer, &Importer::sub);
static Action<void> mul_a(&importer, &Importer::mul);
static Action<void> div_a(&importer, &Importer::div);
static Action<int> num_a(&importer, &Importer::num);

Parser<bool> Importer::exper = std::ref(term) >>
    *((ch_p('+') >> std::ref(term))[add_a] | (ch_p('-') >> std::ref(term))[sub_a]);

Parser<bool> Importer::term = std::ref(factor) >>
    *((ch_p('*') >> std::ref(factor))[mul_a] | (ch_p('/') >> std::ref(factor))[div_a]);

Parser<bool> Importer::factor = int_p()[num_a] | confix_p(ch_p('('), std::ref(exper), ch_p(')'));


bool ExpParser::parse(std::string_view &stream)
{
    return Importer::exper(stream);
}

bool ExpParser::parse(std::ifstream &stream)
{
    std::stringstream sstream;
    sstream << stream.rdbuf();
    std::string str(sstream.str());
    std::string_view temp(str);
    return Importer::exper(temp);
}


}