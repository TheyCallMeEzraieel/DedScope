#include "Scanner/Pattern.h"
#include "Scanner/PatternParser.h"

#include <cstdlib>
#include <cstdint>

std::vector<PatternByte> PatternParser::Parse(const char* pattern)
{
    std::vector<PatternByte> bytes;

    while (*pattern)
    {
        while (*pattern == ' ')
            ++pattern;

        if (*pattern == '\0')
            break;

        if (pattern[0] == '?' && pattern[1] == '?')
        {
            bytes.emplace_back(PatternByte{0x00, true});
        }
        else
        {
            if (pattern[1] == '\0')
                break;

            char hex[3] = { pattern[0], pattern[1], '\0' };

            uint8_t value = static_cast<uint8_t>(
                std::strtoul(hex, nullptr, 16));

            bytes.emplace_back(PatternByte{ value, false });
        }

        pattern += 2;
    }

    return bytes;
}