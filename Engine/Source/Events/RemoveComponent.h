#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view RemoveComponentKey = "remove_component";

    struct RemoveComponentRequest
    {
        std::string Component;
        uint32 Index;
    };

    struct RemoveComponentResponse
    {
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(RemoveComponentRequest, Component, Index);
}