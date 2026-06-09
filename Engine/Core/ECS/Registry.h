#pragma once

#include "Entity.h"
#include "Pool.h"

#include <memory>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Engine::ECS
{
    class Registry
    {
    public:
        Entity Create();
        void Destroy(Entity InEntity);
        bool IsValid(Entity InEntity) const;

        template<typename T, typename... Args>
        T& Add(Entity InEntity, Args&&... InArgs);

        template<typename T>
        void Remove(Entity InEntity);

        template<typename T>
        bool Has(Entity InEntity);

        template<typename T>
        T& Get(Entity InEntity);

        template<typename... Ts, typename Fn>
        void View(Fn&& InFunc);

    private:
        template<typename T>
        Pool<T>& GetPool();

        std::unordered_map<std::type_index, std::unique_ptr<IPool>> Pools;
        std::vector<std::uint32_t> FreeList;
        std::vector<std::uint32_t> Versions;
    };
}

#include "Registry.inl"
