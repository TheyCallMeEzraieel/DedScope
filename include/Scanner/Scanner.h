#pragma once

#include <vector>
#include <optional>
#include <cstdint>
#include "Pattern.h"

class Scanner
{
public:

    [[nodiscard]]
    static std::optional<uintptr_t> ScanFirst(const std::vector<uint8_t>& buffer, uintptr_t baseAddress, const Pattern& pattern) noexcept;

    [[nodiscard]]
    static std::vector<uintptr_t> ScanAll(const std::vector<uint8_t>& buffer, uintptr_t baseAddress, const Pattern& pattern) noexcept;

private:

    static bool Match(const std::vector<uint8_t>& buffer, size_t offset, const Pattern& pattern) noexcept;

};