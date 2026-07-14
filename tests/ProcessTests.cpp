#include "Tests/ProcessTests.h"

#include "Process/ProcessManager.h"
#include "Utils/Console.h"

#include <cstdio>

void RunProcessTests()
{
    Console::Write("=== Process Enumeration Test ===\n");

    auto processes = ProcessManager::Enumerate();

    char buffer[64];

    for (const auto& process : processes)
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "PID: %lu ",
            static_cast<unsigned long>(process.GetPID()));

        Console::Write(buffer);
        Console::Write(process.GetName());
        Console::Write("\n");
    }

    std::snprintf(
        buffer,
        sizeof(buffer),
        "\nTotal Processes: %zu\n",
        processes.size());

    Console::Write(buffer);
    Console::Write("\nFind a Process: ");
    DWORD mypid;
    scanf("%d", &mypid);
    if (ProcessManager::FindByPID(mypid))
    {
        Console::Write("\n Found it out");
    }
    else
    {
        Console::Write("\n Couldn't found it out");
    }
}