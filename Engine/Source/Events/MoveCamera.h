#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view MoveCameraKey = "move_camera";

    enum class MoveCameraDirection
    {
        None = 0,
        Up = 1 << 0,
        Down = 1 << 1,
        Left = 1 << 2,
        Right = 1 << 3,
        Forward = 1 << 4,
        Back = 1 << 5
    };

    struct MoveCameraRequest
    {
        MoveCameraDirection Direction;
        bool Move;
    };

    struct MoveCameraResponse
    {
    };
    
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(MoveCameraRequest, Direction, Move);
}