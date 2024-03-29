#include <iostream>
#include "ExpParser.hpp"


int main()
{
    std::string_view exp0(" 12 + 24 * 4 - 7 * 8 ");
    ExpParser::parse(exp0);
    std::cout << std::endl;

    std::string_view exp1("12 + 24 * ( 4 + 7 ) / 8");
    ExpParser::parse(exp1);
    std::cout << std::endl;

    return 0;
}