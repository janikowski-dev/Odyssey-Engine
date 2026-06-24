#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view GetEntitiesKey = "get_entities";

    struct GetEntitiesRequest
    {
    };

    struct GetEntitiesResponse
    {
        std::vector<uint32> Indexes;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(GetEntitiesResponse, Indexes);
}