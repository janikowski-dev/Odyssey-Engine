#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view CreateEntityKey = "create_entity";

    struct CreateEntiryRequest
    {
    };

    struct CreateEntityResponse
    {
        uint32 Index;
        Json Info;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreateEntityResponse, Index, Info);
}