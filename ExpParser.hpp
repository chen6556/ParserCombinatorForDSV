#pragma once
#include <string>
#include <fstream>
#include "Parser.hpp"


namespace ExpParser
{

class Importer
{
public:
    static Parser<bool> exper, term, factor;

public:
    void add();

    void sub();

    void mul();

    void div();

    void num(const int value);
};

bool parse(std::string_view &stream);

bool parse(std::ifstream &stream);

};