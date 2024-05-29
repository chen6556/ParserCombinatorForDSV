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

    Parser<std::string> test = pair(ch_p('<'), ch_p('>'));
    std::string_view exp2("< 12 + 24 * ( 4 + 7 ) / 8> abc");
    std::optional<std::string> result = test(exp2);
    if (result.has_value())
    {
        std::cout << result.value() << std::endl;
    }

    return 0;
}