# Contributing

---

## Adding a New Module

Each module lives in its own subdirectory under `src/`. Headers go next to sources — no separate `include/` tree.

```
src/
└── MyModule/
    ├── myModule.h
    └── myModule.cpp
```

CMake automatically picks up all sources under `src/` via `file(GLOB_RECURSE ...)` in the root `CMakeLists.txt`, so no CMake changes are needed when adding a new module.

---

## Mixing C and C++

If a module must be callable from both C and C++ code, wrap its public declarations in an `extern "C"` guard:

```c
#ifndef MY_MODULE_H
#define MY_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

void myFunction(void);

#ifdef __cplusplus
}
#endif

#endif // MY_MODULE_H
```

Use the `extc` snippet (prefix `extc` → Tab) to insert this block.

---

## Adding a Unit Test

Tests use the [Unity](https://github.com/ThrowTheSwitch/Unity) framework. Each test file has its own `main()`.

**1. Create the test file** in `tests/unit/`:

```cpp
// tests/unit/test_myModule.cpp
#include "../unity/src/unity.h"
#include "MyModule/myModule.h"

void setUp(void)   {}
void tearDown(void) {}

void test_something(void)
{
    TEST_ASSERT_EQUAL_INT(expected, actual);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_something);
    return UNITY_END();
}
```

**2. Register it** in `tests/CMakeLists.txt`:

```cmake
set(UNITY_SRC ${CMAKE_CURRENT_SOURCE_DIR}/unity/src/unity.c)

add_unit_test(test_myModule
    ${CMAKE_CURRENT_SOURCE_DIR}/unit/test_myModule.cpp
    ${UNITY_SRC}
)
```

The `add_unit_test` function automatically links all `src/` files (except `main`) and sets include paths, so your module's header is available as `#include "MyModule/myModule.h"`.

**3. Run tests:**

```bash
ctest --preset windows-clang-debug --output-on-failure
ctest --preset linux-gcc-debug     --output-on-failure
```

---

## Code Style

Formatting is enforced by `.clang-format` at the repo root (Allman braces, 4-space indent, 100-column limit).

Format on save is enabled in `.vscode/settings.json`. To format manually:

```bash
clang-format -i src/MyModule/myModule.cpp
```

Naming conventions:
- Types and classes: `PascalCase`
- Functions and variables: `camelCase`
- Constants / `constexpr`: `UPPER_SNAKE_CASE`
- Private members: no prefix required — keep it consistent within a class

---

## Commit Messages

Use the imperative mood, present tense:

```
Add circular buffer module
Fix off-by-one in tick() transition logic
Update CMakePresets for clang on Windows
```

Keep the subject line under 72 characters. Add a body if the change needs explanation.
