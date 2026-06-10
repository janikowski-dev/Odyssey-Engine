#pragma once

#include "Types.h"

#include "../Serialization/SceneSerializer.h"
#include "../Systems/RenderSystem.h"
#include "../Messaging/MessageBus.h"
#include "../Systems/SpinSystem.h"
#include "../Platform/Window.h"
#include "../Editor/Bridge.h"
#include "../ECS/Registry.h"

namespace Source::Core
{
    struct Context
    {
		UniquePtr<Serialization::SceneSerializer> SceneSerializer;
		UniquePtr<Systems::RenderSystem> RenderSystem;
		UniquePtr<Messaging::MessageBus> MessageBus;
		UniquePtr<Systems::SpinSystem> SpinSystem;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<ECS::Registry> World;
    };
}