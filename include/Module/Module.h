#include <Common/Constants.h>
#include <windows.h>

class Module
{
public:
    Module (DWORD pid, uintptr_t baseAddress, DWORD size, const wchar_t* name);

    Module(const Module&) = delete;
    Module& operator=(const Module&) = delete;

    Module(Module&& other) noexcept;
    Module& operator=(Module&& other) noexcept;

    DWORD GetPID() const noexcept;
    uintptr_t GetBaseAddress() const noexcept;
    DWORD GetSize() const noexcept;
    const wchar_t* GetName() const noexcept;

private:
    DWORD pid_;
    uintptr_t baseAddress_;
    DWORD size_;
    wchar_t name_[DedScope::Constants::MaxPathSize];
};