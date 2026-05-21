# Versioning & Configuration
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
project(GLEngine LANGUAGES CXX)

add_library(
    GLEngine
    src/dummy.cpp
    src/instance/instance.cpp
    src/services/runService.cpp
)

target_include_directories(
    GLEngine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Linking
add_subdirectory(
    ../Core 
    ${CMAKE_BINARY_DIR}/Core
)

target_link_libraries(GLEngine
    PUBLIC
        GLECore
)