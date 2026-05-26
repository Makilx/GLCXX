# Versioning & Configuration
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
project(GLECore LANGUAGES CXX)
add_library(
    GLECore 
    src/logger.cpp
)
target_include_directories(GLECore
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(GLECore
    PUBLIC
        cxx_std_20
)