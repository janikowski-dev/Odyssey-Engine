#pragma once

#include "Resources/ResourceCache.h"
#include "Platform/Window.h"
#include "Platform/Input.h"
#include "Editor/Bridge.h"
#include "Core/Minimal.h"
#include "ECS/Registry.h"

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

    struct Workspace
    {
        enum class Direction
        {
            None = 0,
            Up = 1 << 0,
            Down = 1 << 1,
            Left = 1 << 2,
            Right = 1 << 3,
            Forward = 1 << 4,
            Back = 1 << 5
        };

        Vector3 CameraPosition { 1.0f };
        Vector3 CameraRotation { 0.0f };

        float FovDegrees = 60.0f;
        float Aspect = 16.0f / 9.0f;
        float Near = 0.1f;
        float Far = 100.0f;

        int SelectedIndex = -1;
        
        int CameraMoveDirection = 0;
        float CameraXDelta = 0.0f;
        float CameraYDelta = 0.0f;
    };

    struct Context
    {
		UniquePtr<Resources::ResourceCache> ResourceCache;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Core::Workspace> Workspace;
		UniquePtr<Platform::Window> Window;
		UniquePtr<Platform::Input> Input;
		UniquePtr<Core::Runtime> Runtime;
		UniquePtr<ECS::Registry> World;
		UniquePtr<Core::Time> Time;
    };
}