cmake_minimum_required(VERSION 3.20)

project(renderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(renderer
    src/main.cpp
    src/shader.cpp
    src/window.cpp
    src/stb_image.cpp
    extern/glad/src/glad.c
)

target_include_directories(renderer PRIVATE 
    include
    extern/glad/include
    extern/stb
)

target_link_libraries(renderer PRIVATE
    OpenGL::GL
    glfw
)