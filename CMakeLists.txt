cmake_minimum_required(VERSION 3.10)
project(weaver)

# We are using modern C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Tell CMake which files to compile
add_executable(mybrowser 
    src/main.cpp 
    src/html/lexer.cpp 
    # We will add dom.cpp later when we need it
)