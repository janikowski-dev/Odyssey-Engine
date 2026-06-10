#pragma once

#include "../Types.h"

namespace Core::Events
{
    inline constexpr std::string_view CreateEntityKey = "create_entity";

    struct CreateEntiryRequest
    {
    };

    struct CreateEntityResponse
    {
    };
}