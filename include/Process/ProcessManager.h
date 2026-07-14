#include "Process.h"
#include <vector>
#include <optional>

class ProcessManager
{
public:

    ProcessManager() = delete;

    static std::vector<Process> Enumerate();
    
    static std::optional<Process> FindByPID(DWORD pid);

    static std::vector<Process> FindByName(const wchar_t* name);

    static std::optional<Process> GetCurrentProcess();

private:

    template<typename Predicate>
    static std::vector<Process> FindIf(Predicate predicate);

    template<typename Predicate>
    static std::optional<Process> FindFirstIf(Predicate predicate);
};

template<typename Predicate>
std::vector<Process> ProcessManager::FindIf(Predicate predicate)
{
    auto processes = Enumerate();
    std::vector<Process> matches;

    for (auto& process : processes)
    {
        if (predicate(process))
        {
            matches.emplace_back(std::move(process));
        }
    }

    return matches;
}

template<typename Predicate>
std::optional<Process> ProcessManager::FindFirstIf(Predicate predicate)
{
    auto processes = Enumerate();

    for (auto& process : processes)
    {
        if (predicate(process))
        {
            return std::move(process);
        }
    }

    return std::nullopt;
}