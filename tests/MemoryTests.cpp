#include "Tests/MemoryTests.h"

#include "Memory/Memory.h"
#include "Process/ProcessManager.h"
#include "Utils/Console.h"

#include <windows.h>
#include <cstdio>

void RunReadWriteTests()
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

void RunPafTests()
{

    Console::Write("=== Memory Protect/Allocate/Free Test ===\n");

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

            auto address = memory.Allocate(sizeof(int), PAGE_READWRITE);

            if (!address)
            {
                Console::Write("Allocation failed.\n");
            }
            else
            {
                int value = 1337;

                memory.Write(address, value);

                DWORD oldProtect = 0;

                if (memory.Protect(address, sizeof(int), PAGE_READONLY, oldProtect))
                {
                    Console::Write("Protect Success\n");
                }
                else
                {
                    Console::Write("Protect Failed\n");
                }

                int read = 0;

                memory.Read(address, read);

                char buffer[128];

                snprintf(buffer, sizeof(buffer), "Read = %d\n", read);

                Console::Write(buffer);

                if (memory.Free(address))
                {
                    Console::Write("Free Success.\n");
                }
                else
                {
                    Console::Write("Free Failed.\n");
                }
            }
        }
        
        process->Close();
    }

}