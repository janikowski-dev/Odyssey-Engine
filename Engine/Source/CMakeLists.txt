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
    Events/GetSchema.h
    Events/GetViewport.h
    Events/LoadScene.h
    Events/Ping.h
    Events/SaveScene.h

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
    Serialization/ReflectionHandler.cpp
    Serialization/ReflectionHandler.h
    Serialization/TypeBuilder.h
    Serialization/TypeBuilder.inl
    Serialization/TypeInfo.h
    Serialization/TypeRegistry.cpp
    Serialization/TypeRegistry.h
    Serialization/TypeRegistry.inl

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

# Libraries
target_link_libraries(Source glfw)
target_link_libraries(Source glad)
target_link_libraries(Source glm)
target_link_libraries(Source nlohmann_json)

# Code generation
find_package(Python3 REQUIRED COMPONENTS Interpreter)
 
set(REFLECTGEN_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/CodeGenerator.py")

file(GLOB_RECURSE ALL_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

set(REFLECT_HEADERS "")
foreach(HEADER ${ALL_HEADERS})
    file(STRINGS ${HEADER} HEADER_CONTENTS REGEX "COMPONENT")
    if(HEADER_CONTENTS)
        list(APPEND REFLECT_HEADERS ${HEADER})
    endif()
endforeach()

set(REFLECTION_GENERATED
    "${CMAKE_CURRENT_BINARY_DIR}/Serialization.generated.cpp"
)

set(_reflect_libclang_arg "")
if(REFLECTGEN_LIBCLANG)
    set(_reflect_libclang_arg --libclang "${REFLECTGEN_LIBCLANG}")
endif()

add_custom_command(
    OUTPUT  "${REFLECTION_GENERATED}"
    COMMAND ${Python3_EXECUTABLE} "${REFLECTGEN_SCRIPT}"
            --out "${REFLECTION_GENERATED}"
            --std c++20
            -I "${CMAKE_CURRENT_SOURCE_DIR}"
            --include-root "${CMAKE_CURRENT_SOURCE_DIR}"
            "$<$<BOOL:$<TARGET_PROPERTY:glm,INTERFACE_INCLUDE_DIRECTORIES>>:-I$<JOIN:$<TARGET_PROPERTY:glm,INTERFACE_INCLUDE_DIRECTORIES>,;-I>>"
            "$<$<BOOL:$<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>>:-I$<JOIN:$<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>,;-I>>"
            ${_reflect_libclang_arg}
            ${REFLECT_HEADERS}
    DEPENDS ${REFLECT_HEADERS} "${REFLECTGEN_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "reflectgen: generating component reflection"
    VERBATIM
)

set_source_files_properties("${REFLECTION_GENERATED}" PROPERTIES GENERATED TRUE)
target_sources(Source PRIVATE "${REFLECTION_GENERATED}")

# Includes
file(GLOB_RECURSE ALL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

set(INCLUDE_DIRS "")
foreach(HEADER ${ALL_HEADERS})
    get_filename_component(DIR ${HEADER} DIRECTORY)
    list(APPEND INCLUDE_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES INCLUDE_DIRS)

target_include_directories(Source PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIRS}
)
