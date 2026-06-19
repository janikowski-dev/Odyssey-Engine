#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view GetTelemetryKey = "get_telemetry";

    struct GetTelemetryRequest
    {
    };

    struct GetTelemetryResponse
    {
        float FPS;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetTelemetryResponse, FPS);
}