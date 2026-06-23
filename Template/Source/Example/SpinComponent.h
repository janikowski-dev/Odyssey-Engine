#pragma once

#include "Core/Minimal.h"

namespace Game::Example
{
    struct COMPONENT SpinComponent
    {
        PROPERTY() Vector3 Speed { 0.0f };
    };
}