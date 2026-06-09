# General setup
cmake_minimum_required(VERSION 3.10)

project(LLP_Engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
include(Dependencies.cmake)

# Projects
add_subdirectory(Engine)
add_subdirectory(Runtime)
