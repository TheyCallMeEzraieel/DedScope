#pragma once

#include <cstdint>
#include <vector>

struct PatternByte
{
    uint8_t value;
    bool wildcard;
};

class Pattern
{
public:

    explicit Pattern(const char* pattern);

    const std::vector<PatternByte>& GetBytes() const noexcept;

private:

    std::vector<PatternByte> bytes_;

};