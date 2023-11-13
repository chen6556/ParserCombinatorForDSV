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

    auto key = confix_p(ch_p('\"'), (*anychar_p())[prints_a], ch_p('\"'));
    auto value = key | float_p()[([&](const double v) { importer.print(v); })];
    auto array = confix_p(ch_p('['), *((float_p()[printd_a] | key) >> *ch_p(' ') >> ch_p(',')) >> *ch_p(' ') >> !(float_p()[printd_a] | key), ch_p(']'))[print_a];

    std::string_view text("[123, \"Hello\"]");
    array(text);

    return 0;
}