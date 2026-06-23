#pragma once

#include "Core/Minimal.h"

namespace Source::Events
{
    inline constexpr std::string_view AddedEntityKey = "added_entity";

    struct AddedEntity
    {
        uint32 Index;
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AddedEntity, Index);
}