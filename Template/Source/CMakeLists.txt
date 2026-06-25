#
# Game
#

cmake_minimum_required(VERSION 3.20)
project(Game)

# Engine setup
if(DEFINED ENV{ODYSSEY_ENGINE_ROOT})
    set(ODYSSEY_ENGINE_ROOT "$ENV{ODYSSEY_ENGINE_ROOT}")
endif()

# Sources
set(SOURCES
    Example/SpinComponent.h
    Example/SpinModule.h
)

# Properties parsing
file(GLOB_RECURSE GAME_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
)

set_property(GLOBAL APPEND PROPERTY ODYSSEY_EXTRA_REFLECT_HEADERS
    ${GAME_HEADERS}
)

# Engine
add_subdirectory("${ODYSSEY_ENGINE_ROOT}/Launcher" "${CMAKE_CURRENT_BINARY_DIR}/Launcher")
add_subdirectory("${ODYSSEY_ENGINE_ROOT}/Source" "${CMAKE_CURRENT_BINARY_DIR}/Source")

# Project
add_library(Game STATIC)

target_sources(Game PRIVATE
    ${SOURCES}
)

target_link_libraries(Game PRIVATE Source)

target_include_directories(Game PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Includes
file(GLOB_RECURSE ALL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

set(INCLUDE_DIRS "")
foreach(HEADER ${ALL_HEADERS})
    get_filename_component(DIR ${HEADER} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR})
endforeach()

get_property(EXTRA_INCLUDE_DIRS GLOBAL PROPERTY ODYSSEY_EXTRA_INCLUDE_DIRS)
list(APPEND INCLUDE_DIRS ${EXTRA_INCLUDE_DIRS})

list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(Source PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIRS}
)