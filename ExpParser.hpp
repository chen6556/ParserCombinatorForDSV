#pragma once
#include <string>
#include <fstream>
#include "Parser/ParserGen2.hpp"


namespace ExpParser
{

class Importer
{
public:
    void add();

    void sub();

    void mul();

    void div();

    void num(const int value);
};

struct Parsers
{
    static Parser<bool> exper, term, factor;
};

bool parse(std::string_view &stream);

bool parse(std::ifstream &stream);

};