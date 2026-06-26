#pragma once

#include "Core/Minimal.h"

namespace Source::Rendering
{
    class Transform
    {
    public:
        Transform(const Vector3& Position, const Vector3& Rotation, const Vector3& Scale);

    public:
        Matrix4 Matrix { 1.0f };
    };
}