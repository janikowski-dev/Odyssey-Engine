#pragma once

#include "Core/Minimal.h"

namespace Source::Runtime
{
    struct Runtimer
    {
        float DeltaTime = 0.0f;
        bool IsPlaying = false;
        Time CurrentTime {};
    };
}