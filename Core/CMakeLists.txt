# Versioning & Configuration
cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Library
project(GLECore LANGUAGES CXX)
add_library(GLECore INTERFACE)
target_include_directories(GLECore
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_compile_features(GLECore
    INTERFACE
        cxx_std_20
)

# Tooling target (safe to delete later)

# add_library(GLEngineTooling STATIC
#     tools/dummy.cpp
# )

# target_link_libraries(GLEngineTooling
#     PRIVATE
#         GLECore
# )