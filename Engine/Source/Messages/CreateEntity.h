#pragma once

#include "../Core/Types.h"

namespace Source::Events
{
    inline constexpr std::string_view CreateEntityKey = "create_entity";

    struct CreateEntiryRequest
    {
    };

    struct CreateEntityResponse
    {
    };
}