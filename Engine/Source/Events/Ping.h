#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view PingKey = "ping";

    struct PingRequest
    {
    };

    struct PingResponse
    {
    };
}