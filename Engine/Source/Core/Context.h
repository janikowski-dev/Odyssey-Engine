#pragma once

#include "Resources/ResourceCache.h"
#include "Platform/Window.h"
#include "Platform/Input.h"
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
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<Platform::Input> Input;
		UniquePtr<Core::Runtime> Runtime;
		UniquePtr<ECS::Registry> World;
		UniquePtr<Core::Time> Time;
    };
}