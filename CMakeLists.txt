cmake_minimum_required(VERSION 3.8)
project(n_lexer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp lib/NFA.cpp lib/NFA.h lib/Analyzer.cpp lib/Analyzer.h lib/DFA.cpp lib/DFA.h lib/ODFA.cpp lib/ODFA.h lib/Token.cpp lib/Token.h re/RE.h)
add_executable(n_lexer ${SOURCE_FILES})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)