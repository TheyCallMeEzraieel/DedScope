#include "Tests/MemoryTests.h"

#include "Memory/Memory.h"
#include "Process/ProcessManager.h"
#include "Utils/Console.h"

#include <windows.h>
#include <cstdio>

void RunMemoryTests()
{

    Console::Write("=== Memory Test ===\n");

    auto process = ProcessManager::FindByPID(GetCurrentProcessId());

    if (!process)
    {
        Console::Write("Failed to find current process.\n");
    }
    else
    {
        if(!process->Open())
        {
            Console::Write("Failed to open current process.\n");
        }
        else
        {
            Memory memory(*process);

            int orgValue = 12345678;

            int readValue = 0;

            if (memory.Read(reinterpret_cast<uintptr_t>(&orgValue), readValue))
            {
                char buffer[128];

                std::snprintf(buffer, sizeof(buffer), "Read Success! Value = %d\n", readValue);

                Console::Write(buffer);
            }
            else
            {
                Console::Write("Read failed.\n");
            }

            int newValue = 1337;

            if (memory.Write(reinterpret_cast<uintptr_t>(&orgValue), newValue))
            {
                char buffer[256];

                std::snprintf(buffer, sizeof(buffer), "Write Success! The New Value = %d\n", orgValue);

                Console::Write(buffer);
            }
            else
            {
                Console::Write("Write failed.\n");
            }
        }
        
        process->Close();
    }
}