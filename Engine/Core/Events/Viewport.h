#pragma once

#include "../Types.h"

namespace Core::Events
{
    inline constexpr std::string_view ViewportKey = "get_viewport";

    struct ViewportRequest
    {
    };

    struct ViewportResponse
    {
        uint64_t hwnd;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ViewportResponse, hwnd);
}