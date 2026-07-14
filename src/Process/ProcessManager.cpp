#include "Process/ProcessManager.h"
#include "Utils/Logger.h"
#include <tlhelp32.h>

std::vector<Process> ProcessManager::Enumerate()
{
    std::vector<Process> processes;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE)    
    {
        Logger::Error("Couldn't create Snapshot.");
        return processes;
    }

    PROCESSENTRY32W entry{};

    entry.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(snapshot, &entry))
    {
        Logger::Error("Couldn't get FirstProcess Snapshot.");
        CloseHandle(snapshot);
        return processes;
    }

    do
    {
        processes.emplace_back(entry.th32ProcessID, entry.szExeFile);
    } while (Process32NextW(snapshot, &entry));
    

    CloseHandle(snapshot);
    return processes;
}

std::optional<Process> ProcessManager::FindByPID(DWORD pid)
{
    return FindFirstIf([pid](const Process& process)
    {
        return process.GetPID() == pid;
    });
}

std::vector<Process> ProcessManager::FindByName(const wchar_t* name)
{
    return  FindIf([name](const Process& process)
    {
        return wcscmp(process.GetName(), name) == 0;       
    });
}