#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view StopKey = "stop";

    struct StopRequest
    {
    };

    struct StopResponse
    {
    };
}