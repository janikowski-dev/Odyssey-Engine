#pragma once

#include "../Core/Types.h"

namespace Source::Events
{
    inline constexpr std::string_view ViewportKey = "get_viewport";

    struct ViewportRequest
    {
    };

    struct ViewportResponse
    {
        uint64 hwnd;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ViewportResponse, hwnd);
}