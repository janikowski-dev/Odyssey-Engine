#
# Core
#

set(SOURCES
    ApplicationConfig.h
    Application.cpp
    Application.h
    Context.h
    IModule.h
    Types.h

    Components/MeshRenderer.h
    Components/Spin.h
    Components/Transform.h

    Config/EngineConfig.h
    Config/LaunchType.h
    Config/WindowConfig.h

    Editor/Connection.cpp
    Editor/Connection.h
    Editor/Bridge.cpp
    Editor/Bridge.h
    Editor/Bridge.inl

    ECS/Entity.h
    ECS/Pool.h
    ECS/Pool.inl
    ECS/Registry.cpp
    ECS/Registry.h
    ECS/Registry.inl

    Events/CreateEntity.h
    Events/LoadScene.h
    Events/Ping.h
    Events/SaveScene.h
    Events/Viewport.h

    Platform/Window.cpp
    Platform/Window.h

    Rendering/Camera.h
    Rendering/Mesh.cpp
    Rendering/Mesh.h
    Rendering/Renderer.cpp
    Rendering/Renderer.h
    Rendering/Shader.cpp
    Rendering/Shader.h

    Serialization/ComponentRegistry.cpp
    Serialization/ComponentRegistry.h
    Serialization/ComponentRegistry.inl
    Serialization/SceneSerializer.cpp
    Serialization/SceneSerializer.h

    Systems/RenderSystem.h
    Systems/SpinSystem.h

    Messaging/MessageBus.cpp
    Messaging/MessageBus.h
    Messaging/MessageBus.inl
    Messaging/HandlerData.h
    Messaging/HandlerData.cpp
    Messaging/Subscription.cpp
    Messaging/Subscription.h

    Modules/EditorModule.cpp
    Modules/EditorModule.h
    Modules/MessagingModule.cpp
    Modules/MessagingModule.h
    Modules/PlatformModule.cpp
    Modules/PlatformModule.h
    Modules/SerializationModule.cpp
    Modules/SerializationModule.h
    Modules/SystemsModule.cpp
    Modules/SystemsModule.h
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
