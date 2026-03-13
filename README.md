# Optikos

A lightweight cross-platform C++ UI framework.

![demo](https://github.com/IlanVinograd/Optikos/blob/main/res/images/example1.gif?raw=true)

![example](https://github.com/IlanVinograd/Optikos/blob/main/res/images/example2.png?raw=true)

[example1.cpp](https://github.com/IlanVinograd/Optikos/blob/main/examples/example1.cpp)

## Example
```cpp
#include "optikos.hpp"

int main()
{
    Optikos::Optikos app("Hello", 800, 480);

    auto btn = std::make_unique<Optikos::Button>(120, 30, Optikos::Vec2(20, 20), "Click me");
    btn->setEvent([]() { std::cout << "Clicked!\n"; });
    app.addWidget(1, std::move(btn));

    while (!app.should_close())
    {
        app.begin();
        app.end();
    }
}
```

---

## Backends

|          | GLFW | SDL |
|----------|------|-----|
| Windows  | ✅   | ❌  |
| Linux    | ✅   | ❌  |
| macOS    | ✅   | ❌  |

|          | OpenGL | Vulkan | DirectX |
|----------|--------|--------|---------|
| Renderer | ✅     | ❌     | ❌      |

---

## Getting Started

Add Optikos to your project via CMake `FetchContent`:

```cmake
cmake_minimum_required(VERSION 3.20)
project(TestApp LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OPTIKOS_RENDERER "OPENGL" CACHE STRING "" FORCE)
set(OPTIKOS_PLATFORM "GLFW"   CACHE STRING "" FORCE)
set(OPTIKOS_INPUT    "GLFW"   CACHE STRING "" FORCE)

include(FetchContent)
FetchContent_Declare(
    Optikos
    GIT_REPOSITORY https://github.com/IlanVinograd/Optikos
    GIT_TAG main
)
FetchContent_MakeAvailable(Optikos)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad  CONFIG REQUIRED)

add_executable(TestApp main.cpp)

target_link_libraries(TestApp PRIVATE 
    Optikos::Optikos
    glfw
    glad::glad
)

target_compile_definitions(TestApp PRIVATE
    OPTIKOS_RES_DIR="${optikos_SOURCE_DIR}/res/"
)

optikos_copy_resources(TestApp)
```

---

## Build (Windows)

```powershell
cmake --preset windows-msvc
```

```powershell
cmake --preset windows-msvc && cmake --build build && .\build\Debug\Optikos.exe
```

With GPU profiling:

```powershell
cmake --preset windows-msvc -D ENABLE_GPU_PROFILING=ON && cmake --build build && .\build\Debug\Optikos.exe
```
