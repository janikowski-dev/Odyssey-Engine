#pragma once

#include "Core/Minimal.h"

namespace Source::Components
{
    struct COMPONENT TransformComponent
    {
        PROPERTY() Vector3 Position { 0.0f };
        PROPERTY() Vector3 Rotation { 0.0f };
        PROPERTY() Vector3 Scale { 1.0f };
    };
}
