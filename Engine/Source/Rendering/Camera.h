#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Camera
    {
    public:
        Camera(const Vector3& Position, const Vector3& Rotation, const float& FovDegrees, const float& Aspect, const float& Near, const float& Far);

    public:
        Matrix4 Projection { 1.0f };
        Matrix4 View { 1.0f };
    };
}