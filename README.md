# DedScope

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-blue)
![License](https://img.shields.io/badge/License-MIT-green)
![Status](https://img.shields.io/badge/Status-Active%20Development-orange)

DedScope is a modern C++ library for Windows process inspection and memory manipulation.

The goal of this project is to provide a clean, lightweight, and reusable API for reverse engineering, debugging, game hacking research, and memory analysis.

> ⚠️ This project is currently under active development.

## Features

### Process
- Process abstraction
- Process enumeration
- Find process by PID
- Find process by name
- Automatic HANDLE management (RAII)

### Module
- Module abstraction
- Module enumeration
- Find module by name

### Memory
- ReadProcessMemory wrapper
- WriteProcessMemory wrapper
- VirtualProtectEx wrapper
- VirtualAllocEx wrapper
- VirtualFreeEx wrapper

### Pattern
- Pattern parser
- Wildcard (`??`) support

## Project Structure

```
DedScope/
│
├── Common/
├── Memory/
├── Module/
├── Process/
├── Scanner/
├── Utils/
└── Tests/
```

## Example

```cpp
auto process = ProcessManager::FindByPID(GetCurrentProcessId());

if (!process)
    return;

process->Open();

Memory memory(*process);

int value = 0;

memory.Read(address, value);
```

## Roadmap

- [x] Process abstraction
- [x] Process manager
- [x] Module manager
- [x] Memory API
- [x] Pattern parser
- [ ] Pattern scanner
- [ ] Pointer utilities
- [ ] Memory region enumeration
- [ ] PE parser
- [ ] Multithreaded scanner
- [ ] SIMD optimized scanner

## Requirements

- Windows
- C++20
- CMake

## License

MIT License