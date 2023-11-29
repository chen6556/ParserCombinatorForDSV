#include <iostream>
#include "Parser.hpp"


class Importer
{
private:
    size_t count = 0;

public:
    void print()
    {
        std::cout << "Get " << count << " times." << std::endl;
    }

    void print(const std::string &str)
    {
        std::cout << "Get " << count++ << " : " << str << std::endl;
    }

    void print(const double value)
    {
        std::cout << "Get " << count++ << " : " << value << std::endl;
    }
};


int main()
{
    Importer importer;
    Action<void> print_a(&importer, &Importer::print);
    Action<std::string> prints_a(&importer, &Importer::print);
    Action<double> printd_a(&importer, &Importer::print);

    Parser<bool> key, value, array;
    key = confix_p(ch_p('\"'), (*anychar_p())[prints_a], ch_p('\"'));
    value = key | float_p()[([&](const double v) { importer.print(v); })] | ref(array);
    array = pair(ch_p('['), list(value, *ch_p(' ') >> ch_p(',') >> *ch_p(' ')), ch_p(']'));

    std::string_view text("[123, [23, 45], 76]");
    array(text);

    return 0;
}