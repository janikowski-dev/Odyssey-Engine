#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view DestroyEntityKey = "destroy_entity";

    struct DestroyEntityRequest
    {
        uint32 Index;
    };

    struct DestroyEntityResponse
    {
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DestroyEntityRequest, Index);
}