#pragma once

#include "Core/Minimal.h"

namespace Source::Components
{
    struct CameraComponent
    {
        Vector3 Position { 0.0f, 2.0f, 0.0f };
        Vector3 Target { 0.0f, 0.0f, 0.0f };
        Vector3 Up { 0.0f, 1.0f, 0.0f };

        float FovDegrees = 60.0f;
        float Aspect = 16.0f / 9.0f;
        float Near = 0.1f;
        float Far = 100.0f;

        int32 Priority;
    };
}
