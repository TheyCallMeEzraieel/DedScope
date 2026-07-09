#include "Utils/Console.h"

#include <cstdio>

void Console::Write(const char* text)
{
    printf("%s", text);
}