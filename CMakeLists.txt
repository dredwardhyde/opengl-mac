cmake_minimum_required(VERSION 3.10)
project(opengl-mac)

set(CMAKE_CXX_STANDARD 11)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "AppleClang")
    set(CMAKE_CXX_FLAGS "-O3 -std=c++11 -stdlib=libc++ -Wall -Wextra -lglfw -framework CoreVideo -framework OpenGL -framework IOKit -framework Cocoa -framework Carbon")
    include_directories("GLFW")
    include_directories("GLFW/GL")
    include_directories("GLFW/KHR")
    add_executable(triangle triangle.cpp "${PROJECT_SOURCE_DIR}/GLFW/gl3w.c")
endif()