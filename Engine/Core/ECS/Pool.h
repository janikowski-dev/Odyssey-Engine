#pragma once

#include "../Types.h"

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace Core::ECS
{
    inline constexpr uint32 INVALID_SLOT = ~0u;

    class IPool
    {
    public:
        virtual ~IPool() = default;
        virtual bool Has(uint32 Index) const = 0;
        virtual void Remove(uint32 Index) = 0;
    };

    template<typename T>
    class Pool final : public IPool
    {
    public:
        bool Has(uint32 Index) const override;

        template<typename... Args>
        T& Add(uint32 Index, Args&&... InArgs);

        void Remove(uint32 Index) override;

        T& Get(uint32 Index);

        const std::vector<uint32>& Entities() const { return Packed; }
        std::size_t Size() const { return Components.size(); }

    private:
        std::vector<uint32> Sparse;
        std::vector<uint32> Packed;
        std::vector<T> Components;
    };
}

#include "Pool.inl"
