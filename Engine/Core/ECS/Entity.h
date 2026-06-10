#pragma once

#include "../Types.h"

#include <cstdint>

namespace Core::ECS
{
    struct Entity
    {
        uint32 Index = 0;
        uint32 Version = 0;

        bool operator==(const Entity& Other) const { return Index == Other.Index && Version == Other.Version; }
        bool operator!=(const Entity& Other) const { return !(*this == Other); }
    };

    inline constexpr Entity NULL_ENTITY{ ~0u, ~0u };
}
