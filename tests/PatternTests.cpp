#include "Tests/PatternTests.h"
#include "Utils/Console.h"
#include "Scanner/Pattern.h"

#include <cstdio>

void RunPatternTests()
{
    Pattern pattern("48 8B ?? FF");

    for (const auto& byte : pattern.GetBytes())
    {
        if (byte.wildcard)
        {
            Console::Write("?? ");
        }
        else
        {
            char buffer[8];

            std::snprintf(
                buffer,
                sizeof(buffer),
                "%02X ",
                byte.value);

            Console::Write(buffer);
        }
    }

    Console::Write("\n");
}