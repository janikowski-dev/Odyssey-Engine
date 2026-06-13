#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view CreateCameraEntityKey = "create_camera_entity";

    struct CreateCameraEntityRequest
    {
    };

    struct CreateCameraEntityResponse
    {
        uint32 Index;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateCameraEntityResponse, Index);
}