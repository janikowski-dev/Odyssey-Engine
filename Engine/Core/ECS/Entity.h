#pragma once

#include <cstdint>

namespace Core::ECS
{
    struct Entity
    {
        std::uint32_t Index = 0;
        std::uint32_t Version = 0;

        bool operator==(const Entity& Other) const { return Index == Other.Index && Version == Other.Version; }
        bool operator!=(const Entity& Other) const { return !(*this == Other); }
    };

    inline constexpr Entity NULL_ENTITY{ ~0u, ~0u };
}
