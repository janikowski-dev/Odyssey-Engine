#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view SaveSceneKey = "save_scene";

    struct SaveSceneRequest
    {
    };

    struct SaveSceneResponse
    {
    };
}