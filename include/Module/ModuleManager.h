#pragma once

#include "Module.h"
#include <vector>
#include <optional>

class ModuleManager
{
public:

    static std::vector<Module> Enumerate(DWORD pid);

    static std::optional<Module> FindByName(DWORD pid, const wchar_t* name);

    static std::optional<Module> FindMainModule(DWORD pid);

private:

    template<typename Predicate>
    static std::vector<Module> FindIf(DWORD pid, Predicate predicate);

    template<typename Predicate>
    static std::optional<Module> FindFirstIf(DWORD pid, Predicate predicate);
};

template<typename Predicate>
std::vector<Module> ModuleManager::FindIf(DWORD pid, Predicate predicate)
{
    std::vector<Module> matches = ModuleManager::Enumerate(pid);

    for (auto& module : matches)
    {
        if (predicate(module))
        {
            matches.emplace_back(std::move(module));
        }
    }

    return matches;
}

template<typename Predicate>
std::optional<Module> ModuleManager::FindFirstIf(DWORD pid, Predicate predicate)
{
    std::vector<Module> matches = ModuleManager::Enumerate(pid);

    for (auto& module : matches)
    {
        if (predicate(module))
        {
            return std::move(module);
        }
    }

    return std::nullopt;
}

