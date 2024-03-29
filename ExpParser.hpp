#pragma once
#include <string>
#include <fstream>
#include <stack>
#include <variant>
#include "Parser/ParserGen2.hpp"


namespace ExpParser
{

class Importer
{
private:
    enum Operator {ADD, SUB, MUL, DIV};
    std::stack<std::variant<double, Operator>> _expression;
    std::vector<std::variant<double, Operator>> _cache;

public:
    void add();

    void sub();

    void mul();

    void div();

    void num(const int value);

    void solve();
};

struct Parsers
{
    static Parser<bool> exper, term, factor;
};

bool parse(std::string_view &stream);

bool parse(std::ifstream &stream);

};