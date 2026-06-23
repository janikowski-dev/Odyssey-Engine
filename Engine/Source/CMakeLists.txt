#
# Source
#

set(SOURCES
    Core/ApplicationConfig.h
    Core/Application.cpp
    Core/Application.h
    Core/Context.h
    Core/IModule.h
    Core/IModuleRegistrar.h
    Core/Minimal.h

    Components/CameraComponent.h
    Components/RendererComponent.h
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

    Events/GetSchema.h
    Events/GetTelemetry.h
    Events/GetViewport.h
    Events/LoadScene.h
    Events/Ping.h
    Events/SaveScene.h
    Events/SelectEntity.h

    Platform/Window.cpp
    Platform/Window.h

    Rendering/Mesh.cpp
    Rendering/Mesh.h
    Rendering/Renderer.cpp
    Rendering/Renderer.h
    Rendering/Shader.cpp
    Rendering/Shader.h

    Runtime/Runtimer.h

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

    Messages/AddedEntityMessage.h

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
    Modules/PersistanceModule.cpp
    Modules/PersistanceModule.h
    Modules/PlatformModule.cpp
    Modules/PlatformModule.h
    Modules/ResourcesModule.cpp
    Modules/ResourcesModule.h
    Modules/RenderingModule.cpp
    Modules/RenderingModule.h
    Modules/RuntimeModule.cpp
    Modules/RuntimeModule.h
    Modules/WorldModule.cpp
    Modules/WorldModule.h

    Resources/ResourceCache.h
    Resources/ResourceLibrary.h
    Resources/ResourceLibrary.inl
)

include(Dependencies.cmake)

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

# Code generation - general
find_package(Python3 REQUIRED COMPONENTS Interpreter)

file(GLOB_RECURSE ENGINE_HEADERS CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

get_property(EXTRA_REFLECT_HEADERS GLOBAL PROPERTY ODYSSEY_EXTRA_REFLECT_HEADERS)

set(ALL_HEADERS ${ENGINE_HEADERS} ${EXTRA_REFLECT_HEADERS})
list(REMOVE_DUPLICATES ALL_HEADERS)

set(_reflect_libclang_arg "")
if(REFLECTGEN_LIBCLANG)
    set(_reflect_libclang_arg --libclang "${REFLECTGEN_LIBCLANG}")
endif()

# Code generation - serialization
set(REFLECTGEN_COMPONENTS_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../Codegen/Serialization.py")

set(REFLECT_COMPONENT_HEADERS "")
foreach(HEADER ${ALL_HEADERS})
    file(STRINGS ${HEADER} HEADER_CONTENTS REGEX "COMPONENT")
    if(HEADER_CONTENTS)
        list(APPEND REFLECT_COMPONENT_HEADERS ${HEADER})
    endif()
endforeach()

set(REFLECTION_COMPONENTS_GENERATED
    "${CMAKE_CURRENT_BINARY_DIR}/Serialization.generated.cpp"
)

add_custom_command(
    OUTPUT  "${REFLECTION_COMPONENTS_GENERATED}"
    COMMAND ${Python3_EXECUTABLE} "${REFLECTGEN_COMPONENTS_SCRIPT}"
            --out "${REFLECTION_COMPONENTS_GENERATED}"
            --std c++20
            -I "${CMAKE_CURRENT_SOURCE_DIR}"
            --include-root "${CMAKE_CURRENT_SOURCE_DIR}"
            "$<$<BOOL:$<TARGET_PROPERTY:glm,INTERFACE_INCLUDE_DIRECTORIES>>:-I$<JOIN:$<TARGET_PROPERTY:glm,INTERFACE_INCLUDE_DIRECTORIES>,;-I>>"
            "$<$<BOOL:$<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>>:-I$<JOIN:$<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>,;-I>>"
            ${_reflect_libclang_arg}
            ${REFLECT_COMPONENT_HEADERS}
    DEPENDS ${REFLECT_COMPONENT_HEADERS} "${REFLECTGEN_COMPONENTS_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "reflectgen: generating component reflection"
    VERBATIM
)

set_source_files_properties("${REFLECTION_COMPONENTS_GENERATED}" PROPERTIES GENERATED TRUE)
target_sources(Source PRIVATE "${REFLECTION_COMPONENTS_GENERATED}")

# Code generation - external modules
set(REFLECTGEN_MODULES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/../Codegen/Modules.py")

set(REFLECT_MODULE_HEADERS "")
foreach(HEADER ${ALL_HEADERS})
    file(STRINGS ${HEADER} HEADER_CONTENTS REGEX "MODULE")
    if(HEADER_CONTENTS)
        list(APPEND REFLECT_MODULE_HEADERS ${HEADER})
    endif()
endforeach()

set(REFLECTION_MODULES_GENERATED
    "${CMAKE_CURRENT_BINARY_DIR}/Modules.generated.cpp"
)

add_custom_command(
    OUTPUT  "${REFLECTION_MODULES_GENERATED}"
    COMMAND ${Python3_EXECUTABLE} "${REFLECTGEN_MODULES_SCRIPT}"
            --out "${REFLECTION_MODULES_GENERATED}"
            --std c++20
            -I "${CMAKE_CURRENT_SOURCE_DIR}"
            --include-root "${CMAKE_CURRENT_SOURCE_DIR}"
            "$<$<BOOL:$<TARGET_PROPERTY:glm,INTERFACE_INCLUDE_DIRECTORIES>>:-I$<JOIN:$<TARGET_PROPERTY:glm,INTERFACE_INCLUDE_DIRECTORIES>,;-I>>"
            "$<$<BOOL:$<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>>:-I$<JOIN:$<TARGET_PROPERTY:nlohmann_json,INTERFACE_INCLUDE_DIRECTORIES>,;-I>>"
            ${_reflect_libclang_arg}
            ${REFLECT_MODULE_HEADERS}
    DEPENDS ${REFLECT_MODULE_HEADERS} "${REFLECTGEN_MODULES_SCRIPT}"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "reflectgen: generating component reflection"
    VERBATIM
)

set_source_files_properties("${REFLECTION_MODULES_GENERATED}" PROPERTIES GENERATED TRUE)
target_sources(Source PRIVATE "${REFLECTION_MODULES_GENERATED}")

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
