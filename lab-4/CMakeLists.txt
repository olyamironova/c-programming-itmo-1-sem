cmake_minimum_required(VERSION 3.12)

project(
    labwork4
    VERSION 1.0
    DESCRIPTION "C++ Year 2023 labwork4"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(argparser STATIC
    src/ArgParser.cpp
    src/FlagArgument.cpp
    src/HelpArgument.cpp
    src/IntArgument.cpp
    src/StringArgument.cpp
)

target_include_directories(argparser PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()
add_subdirectory(tests)
