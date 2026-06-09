#
# Runtime
#

set(SOURCES
    CLIParser.cpp
    CLIParser.h
    Main.cpp
)

add_executable(Runtime)

target_sources(Runtime PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Runtime Engine)

set_target_properties(Runtime PROPERTIES
    WIN32_EXECUTABLE TRUE
)

target_link_options(Runtime PRIVATE "/ENTRY:mainCRTStartup")

set_target_properties(Runtime PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Runtime"
)
