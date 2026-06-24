#pragma once

#include "Resources/ResourceCache.h"
#include "Messaging/MessageBus.h"
#include "Platform/Window.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"
#include "Core/Minimal.h"

namespace Source::Core
{
    struct Runtime
    {
        bool ShouldBePlaying = false;
        bool BeganPlaying = false;
        bool EndedPlaying = false;
        bool IsPlaying = false;
    };

    struct Time
    {
        float DeltaTime = 0.0f;
    };

    struct Context
    {
		UniquePtr<Resources::ResourceCache> ResourceCache;
		UniquePtr<Messaging::MessageBus> MessageBus;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<Core::Runtime> Runtime;
		UniquePtr<ECS::Registry> World;
		UniquePtr<Core::Time> Time;
    };
}