# C/C++ Project Template

A CMake preset-based C/C++ project template for VSCode with clangd IntelliSense, Unity unit testing, and Ninja builds.

---

## Requirements

### Windows
| Tool | Purpose | PATH required |
|---|---|---|
| [LLVM](https://releases.llvm.org/) | clang, clang++, llvm-rc, clangd | Yes — add `LLVM/bin` |
| [Ninja](https://ninja-build.org/) | Build system | Yes |
| [CMake](https://cmake.org/) 3.20+ | Build configuration | Yes |

### Linux
| Tool | Purpose |
|---|---|
| `gcc`, `g++` | Compiler |
| `ninja-build` | Build system |
| `cmake` 3.20+ | Build configuration |

```bash
# Ubuntu/Debian
sudo apt install gcc g++ ninja-build cmake
```

---

## Project Structure

```
.
├── src/                        # Source files — headers live next to sources
│   └── MyModule/
│       ├── myModule.h
│       └── myModule.cpp
├── tests/
│   ├── unity/                  # Unity test framework (submodule)
│   ├── unit/                   # Unit test files
│   │   └── test_myModule.cpp
│   ├── CMakeLists.txt
│   └── test.c                  # Test runner entry point
├── .vscode/
│   ├── settings.json           # clangd + cmake-tools config
│   ├── launch.json             # Debug config (cppvsdbg)
│   └── c-cpp.code-snippets     # Project snippets
├── CMakeLists.txt
├── CMakePresets.json
├── .clang-format
└── .clangd
```

---

## Build

### Configure

```bash
# Windows
cmake --preset windows-clang-debug

# Linux
cmake --preset linux-gcc-debug
```

### Build

```bash
# Windows
cmake --build --preset windows-clang-debug

# Linux
cmake --build --preset linux-gcc-debug
```

### Available presets

| Preset | OS | Compiler | Type |
|---|---|---|---|
| `windows-clang-debug` | Windows | clang | Debug |
| `windows-clang-release` | Windows | clang | Release |
| `linux-gcc-debug` | Linux | gcc | Debug |
| `linux-gcc-release` | Linux | gcc | Release |

> In VSCode, select the preset from the cmake-tools status bar and click **Configure**, then **Build**.

---

## Test

```bash
ctest --preset windows-clang-debug
ctest --preset linux-gcc-debug
```

Tests are built as separate executables using the [Unity](https://github.com/ThrowTheSwitch/Unity) framework.

To add a test see [CONTRIBUTING.md](CONTRIBUTING.md).

---

## Debug

Debugging is configured via `launch.json` using `cppvsdbg` (Windows) or `gdb` (Linux).

In VSCode: set a breakpoint → press `F5` or use the cmake-tools debug button in the status bar.

---

## IntelliSense

IntelliSense is provided by **clangd** (not the built-in cpptools engine).

clangd reads `compile_commands.json` from the workspace root. This file is generated automatically by cmake-tools after each configure. It is gitignored — each developer generates their own.

If squiggles appear after adding new files, run **CMake: Configure** to regenerate it.

---

## Snippets

Type the prefix in any `.c` or `.cpp` file and press `Tab`.

| Prefix | Expands to |
|---|---|
| `guard` | Include guard using filename |
| `cls` | C++ class skeleton |
| `str` | C typedef struct |
| `enm` | `enum class` with underlying type |
| `extc` | `extern "C"` block for C/C++ compatible headers |
| `fori` | Index-based `for` loop |
| `forr` | Range-based `for` loop (C++) |
| `sw` | `switch` statement |
| `todo` | `// TODO:` comment |
| `banner` | Section separator comment |

---

## License

MIT — see [LICENSE](LICENSE).
