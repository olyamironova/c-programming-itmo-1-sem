cmake_minimum_required(VERSION 3.26)
project(LW6)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(LW6
        src/main.cpp
        src/Parser.cpp
        include/Parser.h
        src/Hamming.cpp
        include/Hamming.h
        src/Archiving.cpp
        include/Archiving.h)
