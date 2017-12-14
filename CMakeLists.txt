cmake_minimum_required(VERSION 3.8)
project(n_lexer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NFA.cpp NFA.h)
add_executable(n_lexer ${SOURCE_FILES})