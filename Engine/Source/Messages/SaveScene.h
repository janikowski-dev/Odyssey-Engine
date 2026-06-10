#pragma once

#include "../Core/Types.h"

namespace Source::Events
{
    inline constexpr std::string_view SaveSceneKey = "save_scene";

    struct SaveSceneRequest
    {
        std::string Path;
    };

    struct SaveSceneResponse
    {
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SaveSceneRequest, Path);
}