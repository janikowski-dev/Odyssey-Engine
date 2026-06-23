# General setup
cmake_minimum_required(VERSION 3.10)

project(Odyssey_Engine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Projects
add_subdirectory(Launcher)
add_subdirectory(Source)
