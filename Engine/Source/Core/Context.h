#pragma once

#include "Types.h"

#include "../Serialization/SceneSerializer.h"
#include "../Messaging/MessageBus.h"
#include "../Platform/Window.h"
#include "../Editor/Bridge.h"
#include "../ECS/Registry.h"

namespace Source::Core
{
    struct Context
    {
		UniquePtr<Serialization::SceneSerializer> SceneSerializer;
		UniquePtr<Messaging::MessageBus> MessageBus;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<ECS::Registry> World;
    };
}