#pragma once

#include "../Types.h"

namespace Core::Events
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