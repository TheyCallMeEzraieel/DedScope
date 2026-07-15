#include "Tests/ModuleTests.h"

#include "Module/ModuleManager.h"
#include "Utils/Console.h"

#include <windows.h>
#include <cstdio>

void RunModuleTests()
{

    Console::Write("=== Module Enumeration Test ===\n");

    auto modules = ModuleManager::Enumerate(GetCurrentProcessId());

    char buffer[128];

    for (const auto& module : modules)
    {
        std::snprintf(
            buffer,
            sizeof(buffer),
            "Base: 0x%p  Size: %lu ",
            reinterpret_cast<void*>(module.GetBaseAddress()),
            static_cast<unsigned long>(module.GetSize()));

        Console::Write(buffer);
        Console::Write(module.GetName());
        Console::Write("\n");
    }

    std::snprintf(
        buffer,
        sizeof(buffer),
        "\nTotal Modules: %zu\n",
        modules.size());

    Console::Write(buffer);
}