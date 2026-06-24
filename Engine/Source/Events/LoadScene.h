#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view LoadSceneKey = "load_scene";

    struct LoadSceneRequest
    {
    };

    struct LoadSceneResponse
    {
    };
}