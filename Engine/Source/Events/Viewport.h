#pragma once

#include "../Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view ViewportKey = "get_viewport";

    struct ViewportRequest
    {
    };

    struct ViewportResponse
    {
        uint64 Hwnd;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ViewportResponse, Hwnd);
}