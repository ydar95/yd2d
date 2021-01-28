cmake_minimum_required(VERSION 3.17)
project(yd2d)

set(CMAKE_CXX_STANDARD 17)

include_directories(SYSTEM  ./)
add_executable(yd2d main.cpp yd2d/platforms/platform_windows.cpp yd2d/platforms/platform_windows.hpp yd2d/renderers/base_renderder.hpp yd2d/renderers/renderer_gl10_windows.cpp yd2d/renderers/renderer_gl10_windows.hpp)