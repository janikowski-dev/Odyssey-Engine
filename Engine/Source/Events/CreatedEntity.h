#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view CreatedEntityKey = "created_entity";

    struct CreatedEntity
    {
        uint32 Index;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CreatedEntity, Index);
}