cmake_minimum_required(VERSION 3.14)
project(EasyEasingsViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    main.cpp
    DemoDependencies/imgui.cpp
    DemoDependencies/imgui_draw.cpp
    DemoDependencies/imgui_tables.cpp
    DemoDependencies/imgui_widgets.cpp
    DemoDependencies/imgui_demo.cpp
    DemoDependencies/imgui_impl_glfw.cpp
    DemoDependencies/imgui_impl_opengl3.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    DemoDependencies
)

# Manually specify GLFW and OpenGL locations
# You can download GLFW from https://www.glfw.org/download.html
# Or install using a package manager like vcpkg, or manually link OpenGL

set(GLFW_DIR "path/to/glfw")
include_directories(${GLFW_DIR}/include)
link_directories(${GLFW_DIR}/lib)

find_package(OpenGL REQUIRED)
add_executable(EasyEasingsViewer ${SOURCES})

target_link_libraries(EasyEasingsViewer
    OpenGL::GL
    glfw3dll
)
