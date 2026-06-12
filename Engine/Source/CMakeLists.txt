#
# Source
#

set(SOURCES
    Core/ApplicationConfig.h
    Core/Application.cpp
    Core/Application.h
    Core/Context.h
    Core/IModule.h
    Core/Minimal.h

    Components/CameraComponent.h
    Components/RendererComponent.h
    Components/SpinComponent.h
    Components/TransformComponent.h

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

    Rendering/Mesh.cpp
    Rendering/Mesh.h
    Rendering/Renderer.cpp
    Rendering/Renderer.h
    Rendering/Shader.cpp
    Rendering/Shader.h

    Serialization/ECSBinding.h
    Serialization/ECSBinding.inl
    Serialization/FieldMeta.h
    Serialization/FieldTraits.h
    Serialization/PropertyAnnotations.h
    Serialization/ReflectionHandler.cpp
    Serialization/ReflectionHandler.h
    Serialization/TypeBuilder.h
    Serialization/TypeBuilder.inl
    Serialization/TypeInfo.h
    Serialization/TypeRegistry.cpp
    Serialization/TypeRegistry.h
    Serialization/TypeRegistry.inl

    Serialization/SceneSerializer.cpp
    Serialization/SceneSerializer.h

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
    Modules/ResourcesModule.cpp
    Modules/ResourcesModule.h
    Modules/SerializationModule.cpp
    Modules/SerializationModule.h
    Modules/SystemsModule.cpp
    Modules/SystemsModule.h

    Resources/ResourceCache.h
    Resources/ResourceLibrary.h
    Resources/ResourceLibrary.inl
)

add_library(Source STATIC)

target_sources(Source PRIVATE ${SOURCES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

add_compile_definitions(
    GLFW_INCLUDE_NONE
)

target_link_libraries(Source glfw)
target_link_libraries(Source glad)
target_link_libraries(Source glm)
target_link_libraries(Source nlohmann_json)

target_include_directories(Source PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

#file(GLOB_RECURSE ALL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
#
#set(INCLUDE_DIRS "")
#foreach(HEADER ${ALL_HEADERS})
#    get_filename_component(DIR ${HEADER} DIRECTORY)
#    list(APPEND INCLUDE_DIRS ${DIR})
#endforeach()
#list(REMOVE_DUPLICATES INCLUDE_DIRS)
#
#target_include_directories(Source PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}
#    ${INCLUDE_DIRS}
#)
