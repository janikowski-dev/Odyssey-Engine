#pragma once

#include "Core/Minimal.h"

namespace Source::Components
{
    struct COMPONENT CameraComponent
    {
        PROPERTY() Vector3 Position { 0.0f, 2.0f, 0.0f };
        PROPERTY() Vector3 Target { 0.0f, 0.0f, 0.0f };
        PROPERTY() Vector3 Up { 0.0f, 1.0f, 0.0f };

        PROPERTY() float FovDegrees = 60.0f;
        PROPERTY() float Aspect = 16.0f / 9.0f;
        PROPERTY() float Near = 0.1f;
        PROPERTY() float Far = 100.0f;

        PROPERTY() int32 Priority;
    };
}
