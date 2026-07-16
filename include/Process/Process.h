#pragma once

#include <windows.h>
#include "Common/Constants.h"

class Process
{
public:

    Process(DWORD pid, const wchar_t* name);
    ~Process();

    Process(const Process&) = delete;
    Process& operator=(const Process&) = delete;

    Process(Process&& other) noexcept;
    Process& operator=(Process&& other) noexcept;

    bool Open(DWORD desiredAccess = PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION); 
    void Close(); 

    bool IsOpen() const; 

    DWORD GetPID() const noexcept;
    const wchar_t* GetName() const noexcept;
    HANDLE GetHandle() const noexcept;
private:

    DWORD pid_;
    wchar_t name_[DedScope::Constants::MaxPathSize];
    HANDLE handle_ = nullptr;
};