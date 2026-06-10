#pragma once

#include "../Core/Types.h"

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