cmake_minimum_required(VERSION 3.20)

project(DedScope LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(DedScopeLib
    src/Utils/Logger.cpp
    src/Utils/Console.cpp
    src/Process/Process.cpp
    src/Process/ProcessManager.cpp
    src/Module/Module.cpp
    src/Module/ModuleManager.cpp
    src/Memory/Memory.cpp
)

target_include_directories(DedScopeLib PUBLIC include)

add_executable(DedScope
    src/main.cpp
)

target_link_libraries(DedScope PRIVATE DedScopeLib)

add_executable(DedScopeTests
    tests/MainTests.cpp
    tests/ProcessTests.cpp
    tests/ModuleTests.cpp
    tests/MemoryTests.cpp
)

target_link_libraries(DedScopeTests PRIVATE DedScopeLib)