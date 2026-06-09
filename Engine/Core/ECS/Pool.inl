#pragma once

#include "Pool.h"

namespace Engine::ECS
{
    template<typename T>
    bool Pool<T>::Has(std::uint32_t Index) const
    {
        return Index < Sparse.size() && Sparse[Index] != INVALID_SLOT;
    }

    template<typename T>
    template<typename... Args>
    T& Pool<T>::Add(std::uint32_t Index, Args&&... InArgs)
    {
        if (Index >= Sparse.size())
        {
            Sparse.resize(Index + 1, INVALID_SLOT);
        }

        Sparse[Index] = static_cast<std::uint32_t>(Components.size());
        Packed.push_back(Index);
        Components.emplace_back(std::forward<Args>(InArgs)...);
        return Components.back();
    }

    template<typename T>
    void Pool<T>::Remove(std::uint32_t Index)
    {
        if (!Has(Index))
        {
            return;
        }

        const std::uint32_t Slot = Sparse[Index];
        const std::uint32_t Last = static_cast<std::uint32_t>(Components.size() - 1);

        Components[Slot] = std::move(Components[Last]);
        Packed[Slot] = Packed[Last];
        Sparse[Packed[Slot]] = Slot;

        Components.pop_back();
        Packed.pop_back();
        Sparse[Index] = INVALID_SLOT;
    }

    template<typename T>
    T& Pool<T>::Get(std::uint32_t Index)
    {
        return Components[Sparse[Index]];
    }
}
