#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view LoadSceneKey = "load_scene";

    struct LoadSceneRequest
    {
        std::string Path;
    };

    struct LoadSceneResponse
    {
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(LoadSceneRequest, Path);
}