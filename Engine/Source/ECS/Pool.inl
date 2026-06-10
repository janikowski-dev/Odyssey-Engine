#pragma once

#include "Pool.h"

namespace Source::ECS
{
    template<typename T>
    bool Pool<T>::Has(uint32 Index) const
    {
        return Index < Sparse.size() && Sparse[Index] != INVALID_SLOT;
    }

    template<typename T>
    template<typename... Args>
    T& Pool<T>::Add(uint32 Index, Args&&... InArgs)
    {
        if (Index >= Sparse.size())
        {
            Sparse.resize(Index + 1, INVALID_SLOT);
        }

        Sparse[Index] = static_cast<uint32>(Components.size());
        Packed.push_back(Index);
        Components.emplace_back(std::forward<Args>(InArgs)...);
        return Components.back();
    }

    template<typename T>
    void Pool<T>::Clear()
    {
        Sparse.clear();
        Packed.clear();
        Components.clear();
    }

    template<typename T>
    void Pool<T>::Remove(uint32 Index)
    {
        if (!Has(Index))
        {
            return;
        }

        const uint32 Slot = Sparse[Index];
        const uint32 Last = static_cast<uint32>(Components.size() - 1);

        Components[Slot] = std::move(Components[Last]);
        Packed[Slot] = Packed[Last];
        Sparse[Packed[Slot]] = Slot;

        Components.pop_back();
        Packed.pop_back();
        Sparse[Index] = INVALID_SLOT;
    }

    template<typename T>
    T& Pool<T>::Get(uint32 Index)
    {
        return Components[Sparse[Index]];
    }
}
