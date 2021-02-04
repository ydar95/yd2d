cmake_minimum_required(VERSION 3.17)
project(yd2d)

set(CMAKE_CXX_STANDARD 17)

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


include_directories(SYSTEM  ./)
add_executable(yd2d main.cpp yd2d/platforms/platform_windows.cpp yd2d/renderers/renderer_gl10_windows.cpp  yd2d/yd2d_game_engine.cpp yd2d/base/rcode.hpp yd2d/texture/texture2d.cpp yd2d/texture/texture2d.hpp)