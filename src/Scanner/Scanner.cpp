#include "Scanner/Scanner.h"

std::optional<uintptr_t> Scanner::ScanFirst(const std::vector<uint8_t>& buffer, uintptr_t baseAddress, const Pattern& pattern)
{
    const auto& bytes = pattern.GetBytes();

    if (bytes.size() > buffer.size())
    {
        return std::nullopt;
    }

    for (size_t offset=0; offset<=buffer.size() - bytes.size(); ++offset)
    {
        if (Match(buffer, offset, pattern))
        {
            return baseAddress + offset;
        }
    }

    return std::nullopt;
}

std::vector<uintptr_t> Scanner::ScanAll(const std::vector<uint8_t>& buffer, uintptr_t baseAddress, const Pattern& pattern)
{
    const auto& bytes = pattern.GetBytes();
    std::vector<uintptr_t> results;

    if (bytes.size() > buffer.size())
    {
        return results;
    }

    for (size_t offset=0; offset<=buffer.size() - bytes.size(); ++offset)
    {
        if (Match(buffer, offset, pattern))
        {
            results.push_back(baseAddress + offset);
        }
    }

    return results;
}

bool Scanner::Match(const std::vector<uint8_t>& buffer, size_t offset, const Pattern& pattern)
{
    const auto& bytes = pattern.GetBytes();    

    if (offset + bytes.size() > buffer.size())
    {
        return false;
    }

    for (size_t i=0; i<bytes.size(); i++)
    {
        if (bytes[i].wildcard)
            continue;

       if (buffer[offset + i] != bytes[i].value)
        {
            return false;
        }
    }

    return true;
}