cmake_minimum_required(VERSION 3.16)
project(MatrixSwap LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(task1 main.cpp matrix.cpp)

if(MSVC)
    target_compile_options(task1 PRIVATE /W4)
else()
    target_compile_options(task1 PRIVATE -Wall -Wextra)
endif()
