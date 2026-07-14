#include "Utils/Console.h"

#include <cstdio>

void Console::Write(const char* text)
{
    printf("%s", text);
}

void Console::Write(const wchar_t* text)
{
    wprintf(L"%ls", text);
}