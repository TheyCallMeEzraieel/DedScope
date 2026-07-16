#include "Process/Process.h"
#include "Utils/Logger.h"

Process::Process(DWORD pid, const wchar_t* name) : pid_(pid)
{

    wcsncpy_s(name_, DedScope::Constants::MaxPathSize, name, _TRUNCATE);
}

Process::Process(Process&& other) noexcept
    : pid_(other.pid_)
    , handle_(other.handle_)
{
    wcsncpy_s(name_, DedScope::Constants::MaxPathSize, other.name_, _TRUNCATE);

    other.handle_ = nullptr;
}

Process& Process::operator=(Process&& other) noexcept
{
    if (this != &other)
    {
        Close();

        pid_ = other.pid_;

        wcsncpy_s(name_, DedScope::Constants::MaxPathSize, other.name_, _TRUNCATE);

        handle_ = other.handle_;

        other.handle_ = nullptr;
        other.pid_ = 0;
        other.name_[0] = L'\0';
    }

    return *this;
}

Process::~Process()
{

    Close();
}

bool Process::Open(DWORD desiredAccess)
{

    handle_ = OpenProcess(desiredAccess , FALSE, GetPID());
    if (IsOpen())
        return true;
    else
    {
        Logger::Error("Failed to open process");
        return false;
    }
}

void Process::Close()
{

    if (handle_){
        CloseHandle(handle_);
        handle_ = nullptr;
    }
}

bool Process::IsOpen() const
{

    return handle_ != nullptr;
}

DWORD Process::GetPID() const noexcept
{

    return pid_;
}

const wchar_t* Process::GetName() const noexcept
{

    return name_;
}

HANDLE Process::GetHandle() const noexcept
{

    return handle_;
}