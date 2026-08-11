cmake_minimum_required(VERSION 3.10)
project(weaver)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(mybrowser 
    src/main.cpp 
    src/html/lexer.cpp 
    src/html/parser.cpp
)