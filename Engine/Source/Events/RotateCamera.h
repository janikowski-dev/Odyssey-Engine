#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view RotateCameraKey = "rotate_camera";

    struct RotateCameraRequest
    {
        float XDelta;
        float YDelta;
    };

    struct RotateCameraResponse
    {
    };
    
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RotateCameraRequest, XDelta, YDelta);
}