#include "Tests/ProcessTests.h"
#include "Tests/ModuleTests.h"
#include "Tests/MemoryTests.h"

int main()
{
    RunProcessTests();
    RunModuleTests();
    RunReadWriteTests();
    RunPafTests();
    return 0;
}