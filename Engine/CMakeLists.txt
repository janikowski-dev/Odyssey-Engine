#
# Engine
#

set(SOURCES
    Application.cpp
    Application.h

    Editor/Connection.cpp
    Editor/Connection.h
    Editor/Bridge.cpp
    Editor/Bridge.h
    Editor/JsonProxy.cpp
    Editor/JsonProxy.h
    Editor/JsonProxy.inl

    ECS/Entity.h
    ECS/Pool.h
    ECS/Pool.inl
    ECS/Registry.cpp
    ECS/Registry.h
    ECS/Registry.inl

    Config/ApplicationConfig.h
    Config/LaunchType.h
    Config/WindowConfig.h

    Platform/Window.cpp
    Platform/Window.h

    Messaging/EventBus.cpp
    Messaging/EventBus.h
    Messaging/EventBus.inl
    Messaging/HandlerData.h
    Messaging/HandlerData.cpp
    Messaging/Subscription.cpp
    Messaging/Subscription.h
)

add_library(Engine STATIC)

target_sources(Engine PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Engine glfw)
target_link_libraries(Engine glad)
target_link_libraries(Engine glm)
target_link_libraries(Engine nlohmann_json)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
