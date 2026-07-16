#include "Scanner/Pattern.h"
#include "Scanner/PatternParser.h"

Pattern::Pattern(const char* pattern)
{
    bytes_ = PatternParser::Parse(pattern);
}
 
const std::vector<PatternByte>& Pattern::GetBytes() const noexcept
{
    return bytes_;
}