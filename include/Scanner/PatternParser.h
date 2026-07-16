#pragma once

#include "Pattern.h"

class PatternParser
{
public:

    static std::vector<PatternByte> Parse(const char* pattern);
};