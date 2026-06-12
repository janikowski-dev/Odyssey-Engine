#pragma once

#include "Core/Minimal.h"

namespace Source::Components
{
    struct TransformComponent
    {
        Vector3 Position { 0.0f };
        Vector3 Rotation { 0.0f };
        Vector3 Scale { 1.0f };
    };
}
