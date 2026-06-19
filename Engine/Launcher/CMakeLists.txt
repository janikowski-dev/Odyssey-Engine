#
# Launcher
#

set(SOURCES
    CLIParser.cpp
    CLIParser.h
    Main.cpp
)

add_executable(Launcher)

target_sources(Launcher PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Launcher Source)

#set_target_properties(Launcher PROPERTIES
#    WIN32_EXECUTABLE TRUE
#)

target_link_options(Launcher PRIVATE "/ENTRY:mainCRTStartup")

set_target_properties(Launcher PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Launcher"
)
