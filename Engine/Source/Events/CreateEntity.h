#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view CreateEntityKey = "create_entity";

    struct CreateEntityRequest
    {
    };

    struct CreateEntityResponse
    {
    };
}