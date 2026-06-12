#pragma once

#include "Minimal.h"

#include "Serialization/SceneSerializer.h"
#include "Resources/ResourceCache.h"
#include "Messaging/MessageBus.h"
#include "Platform/Window.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"

namespace Source::Core
{
    struct Context
    {
		UniquePtr<Serialization::SceneSerializer> SceneSerializer;
		UniquePtr<Resources::ResourceCache> ResourceCache;
		UniquePtr<Messaging::MessageBus> MessageBus;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<ECS::Registry> World;
    };
}