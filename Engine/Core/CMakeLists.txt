#
# Core
#

set(SOURCES
    Application.cpp
    Application.h

    Components/MeshRenderer.h
    Components/Spin.h
    Components/Transform.h

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

    Rendering/Camera.h
    Rendering/Mesh.cpp
    Rendering/Mesh.h
    Rendering/Renderer.cpp
    Rendering/Renderer.h
    Rendering/Shader.cpp
    Rendering/Shader.h

    Systems/RenderSystem.h
    Systems/SpinSystem.h

    Messaging/EventBus.cpp
    Messaging/EventBus.h
    Messaging/EventBus.inl
    Messaging/HandlerData.h
    Messaging/HandlerData.cpp
    Messaging/Subscription.cpp
    Messaging/Subscription.h
)

add_library(Core STATIC)

target_sources(Core PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Core glfw)
target_link_libraries(Core glad)
target_link_libraries(Core glm)
target_link_libraries(Core nlohmann_json)

target_include_directories(Core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
