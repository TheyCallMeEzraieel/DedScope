cmake_minimum_required(VERSION 3.20)

project(DedScope LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(DedScope
    src/main.cpp
    src/Utils/Logger.cpp
    src/Utils/Console.cpp
)

target_include_directories(DedScope PRIVATE include)