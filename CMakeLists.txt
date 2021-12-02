# Basic configuration
cmake_minimum_required(VERSION 3.13)
project("Markdown HTML Converter" LANGUAGES C)
enable_language(C)
set(CC gcc)
set(CXX g++)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_compile_options(-fdiagnostics-color=auto -Wall -Wextra -pedantic)

# Enable CTest
enable_testing()
include(CTest)

# Compile src
add_subdirectory(src)
