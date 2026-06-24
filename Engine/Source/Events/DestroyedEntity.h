#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view DestroyedEntityKey = "destroyed_entity";

    struct DestroyedEntity
    {
        uint32 Index;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DestroyedEntity, Index);
}