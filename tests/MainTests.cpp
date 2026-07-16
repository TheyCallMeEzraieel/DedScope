#include "Tests/ProcessTests.h"
#include "Tests/ModuleTests.h"
#include "Tests/MemoryTests.h"

int main()
{
    RunProcessTests();
    RunModuleTests();
    RunMemoryTests();
    return 0;
}