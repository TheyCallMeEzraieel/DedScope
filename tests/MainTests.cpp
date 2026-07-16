#include "Tests/ProcessTests.h"
#include "Tests/ModuleTests.h"
#include "Tests/MemoryTests.h"
#include "Tests/PatternTests.h"

int main()
{
    RunProcessTests();
    RunModuleTests();
    RunReadWriteTests();
    RunPafTests();
    RunPatternTests();
    return 0;
}