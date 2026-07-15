#include "Module/Module.h"

Module::Module(DWORD pid, uintptr_t baseAddress, DWORD size, const wchar_t* name) : pid_(pid), baseAddress_(baseAddress), size_(size)
{
    wcsncpy_s(name_, DedScope::Constants::MaxPathSize, name, _TRUNCATE);
}

Module::Module(Module&& other) noexcept
: pid_(other.pid_),
  baseAddress_(other.baseAddress_),
  size_(other.size_)
{
    wcsncpy_s(name_, DedScope::Constants::MaxPathSize, other.name_, _TRUNCATE);

    other.pid_ = 0;
    other.baseAddress_ = 0;
    other.size_ = 0;
    other.name_[0] = L'\0';
}

Module& Module::operator=(Module&& other) noexcept
{
    if (this != &other)
    {

        pid_ = other.pid_;
        baseAddress_ = other.baseAddress_;
        size_ = other.size_;

        wcsncpy_s(name_, DedScope::Constants::MaxPathSize, other.name_, _TRUNCATE);

        other.pid_ = 0;
        other.baseAddress_ = 0;
        other.size_ = 0;
        other.name_[0] = L'\0';

    }

    return *this;
}

DWORD Module::GetPID() const noexcept
{
    return pid_;
}

uintptr_t Module::GetBaseAddress() const noexcept
{
    return baseAddress_;
}

DWORD Module::GetSize() const noexcept
{
    return size_;
}

const wchar_t* Module::GetName() const noexcept
{
    return name_;
}
