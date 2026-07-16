#pragma once

#include "Process/Process.h"

class Memory
{
public:

    explicit Memory(Process& process);

    template<typename T>
    bool Read(uintptr_t address, T& value) const;

    template<typename T>
    bool Write(uintptr_t address, const T& value) const;

    [[nodiscard]]
    bool Protect(uintptr_t address, size_t size, DWORD newProtect, DWORD& oldProtect) noexcept;

    [[nodiscard]]
    uintptr_t Allocate(size_t size, DWORD protect = PAGE_READWRITE, DWORD allocationType = MEM_RESERVE | MEM_COMMIT) noexcept;

    bool Free(uintptr_t address) noexcept;

private:

    Process& process_;
};

template<typename T>
bool Memory::Read(uintptr_t address, T& value) const
{
    SIZE_T bytesRead;
    BOOL result = ReadProcessMemory(process_.GetHandle(), reinterpret_cast<LPCVOID>(address), &value, sizeof(T), &bytesRead);
    return result && bytesRead == sizeof(T);
}

template<typename T>
bool Memory::Write(uintptr_t address, const T& value) const
{
    SIZE_T bytesWritten;
    BOOL result = WriteProcessMemory(process_.GetHandle(), reinterpret_cast<LPVOID>(address), &value, sizeof(T), &bytesWritten);
    return result && bytesWritten == sizeof(T);
}