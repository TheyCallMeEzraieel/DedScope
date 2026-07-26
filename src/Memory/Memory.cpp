#include "Memory/Memory.h"
#include <windows.h>

Memory::Memory(Process& process) : process_(process){};

bool Memory::ReadBuffer(uintptr_t address, void *buffer, size_t size) const noexcept
{
    SIZE_T bytesRead;
    BOOL result = ReadProcessMemory(process_.GetHandle(), reinterpret_cast<LPCVOID>(address), buffer, size, &bytesRead);
    return result && bytesRead == size;
}

std::vector<uint8_t> Memory::ReadBuffer(uintptr_t address, size_t size) const
{
    std::vector<uint8_t> buffer(size);

    const bool result = ReadBuffer(address, buffer.data(), size);

    if (result)
        return buffer;
    else
        return {};

}

bool Memory::Protect(uintptr_t address, size_t size, DWORD newProtect, DWORD &oldProtect) noexcept
{
    return VirtualProtectEx(process_.GetHandle(), reinterpret_cast<LPVOID>(address), size, newProtect, &oldProtect);
}

uintptr_t Memory::Allocate(size_t size, DWORD protect, DWORD allocationType) noexcept
{
    LPVOID address = VirtualAllocEx(process_.GetHandle(), nullptr, size, allocationType, protect);
    return reinterpret_cast<uintptr_t>(address);
}

bool Memory::Free(uintptr_t address) noexcept
{
    return VirtualFreeEx(process_.GetHandle(), reinterpret_cast<LPVOID>(address), 0, MEM_RELEASE);
}