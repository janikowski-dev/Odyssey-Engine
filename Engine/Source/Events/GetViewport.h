#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view GetViewportKey = "get_viewport";

    struct GetViewportRequest
    {
    };

    struct GetViewportResponse
    {
        uint64 Hwnd;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetViewportResponse, Hwnd);
}