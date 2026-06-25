#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view RefreshResourcesKey = "refresh_resources";

    struct RefreshResourcesRequest
    {
    };

    struct RefreshResourcesResponse
    {
    };
}