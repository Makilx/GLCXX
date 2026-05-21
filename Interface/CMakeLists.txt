# Versioning & Configuration
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
project(GLEInterface LANGUAGES CXX)

add_library(
    GLEInterface
    src/dummy.cpp
)

target_include_directories(
    GLEInterface
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Linking
add_subdirectory(
    ../Core 
    ${CMAKE_BINARY_DIR}/Core
)

target_link_libraries(GLEInterface
    PUBLIC
        GLECore
)