# EasyEasings

EasyEasings is a small header-only C++20 library that provides a full set of easing functions from easings.net

## Requirements

- C++20 compatible compiler
- GLFW
- OpenGL
- Dear ImGui (with backends)

## Usage

Include the header:

```cpp
#include "EasyEasings.hpp"
```

Call any easing function with an arithmetic type (`int`, `float`, `double`, etc). Integer inputs will return `double`.

Example:

```cpp
float x = 0.5f;
auto result = EasyEasings::EaseOutBounce(x);
```

All functions are `constexpr` and can be used at compile time.

## Building the Viewer

1. Clone the repository
2. Set up ImGui with OpenGL and GLFW backends
3. Compile `main.cpp` with the appropriate includes and link GLFW/OpenGL

The viewer displays all 30 easing functions in a 6x5 grid and resizes the window to fit the plots.