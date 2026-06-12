#pragma once

#include "Resources/ResourceCache.h"
#include "Messaging/MessageBus.h"
#include "Platform/Window.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"
#include "Core/Minimal.h"

namespace Source::Core
{
    struct Context
    {
		UniquePtr<Resources::ResourceCache> ResourceCache;
		UniquePtr<Messaging::MessageBus> MessageBus;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<ECS::Registry> World;
    };
}