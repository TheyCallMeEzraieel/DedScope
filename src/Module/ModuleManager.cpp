#include "Module/ModuleManager.h"
#include "Utils/Logger.h"
#include <tlhelp32.h>

std::vector<Module> ModuleManager::Enumerate(DWORD pid)
{
    std::vector<Module> modules;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pid);

    if (snapshot == INVALID_HANDLE_VALUE)
    {
        Logger::Error("Failed to snapshot");
        return modules;
    }

    MODULEENTRY32W entry{};

    entry.dwSize = sizeof(MODULEENTRY32W);

    if (!Module32FirstW(snapshot, &entry))
    {
        Logger::Error("Couldn't find the FirstModule.");
        CloseHandle(snapshot);
        return modules;
    }

    do
    {
        modules.emplace_back(pid, reinterpret_cast<uintptr_t>(entry.modBaseAddr), entry.modBaseSize, entry.szModule);
    } while (Module32NextW(snapshot, &entry));
    
    CloseHandle(snapshot);
    return modules;
}

std::optional<Module> ModuleManager::FindByName(DWORD pid, const wchar_t* name)
{
    return FindFirstIf(pid, [name](const Module& module)
    {
        return wcscmp(module.GetName(), name) == 0;
    });
}

std::optional<Module> ModuleManager::FindMainModule(DWORD pid)
{
    std::vector<Module> matches = Enumerate(pid);

    if (matches.empty())
        return std::nullopt;

    return std::move(matches.front());
}