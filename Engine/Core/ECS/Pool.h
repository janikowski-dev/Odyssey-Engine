#pragma once

#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

namespace Engine::ECS
{
    inline constexpr std::uint32_t INVALID_SLOT = ~0u;

    class IPool
    {
    public:
        virtual ~IPool() = default;
        virtual bool Has(std::uint32_t Index) const = 0;
        virtual void Remove(std::uint32_t Index) = 0;
    };

    template<typename T>
    class Pool final : public IPool
    {
    public:
        bool Has(std::uint32_t Index) const override;

        template<typename... Args>
        T& Add(std::uint32_t Index, Args&&... InArgs);

        void Remove(std::uint32_t Index) override;

        T& Get(std::uint32_t Index);

        const std::vector<std::uint32_t>& Entities() const { return Packed; }
        std::size_t Size() const { return Components.size(); }

    private:
        std::vector<std::uint32_t> Sparse;
        std::vector<std::uint32_t> Packed;
        std::vector<T> Components;
    };
}

#include "Pool.inl"
