#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view CreateExampleEntityKey = "create_example_entity";

    struct CreateExampleEntityRequest
    {
    };

    struct CreateExampleEntityResponse
    {
        uint32 Index;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateExampleEntityResponse, Index);
}