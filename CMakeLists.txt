cmake_minimum_required(VERSION 3.17)
project(yd2d)

set(CMAKE_CXX_STANDARD 17)


include_directories(./include)

add_executable(yd2d main.cpp ${yd2d_includes})