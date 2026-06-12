#pragma once

#include "Core/Minimal.h"
#include "ECS/Entity.h"
#include "ECS/Pool.h"

#include <memory>
#include <tuple>
#include <typeindex>
#include <unordered_map>
#include <utility>

namespace Source::ECS
{
    class Registry
    {
    public:
        Entity Create();
        void Destroy(Entity InEntity);
        void Clear();
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

        std::unordered_map<std::type_index, UniquePtr<IPool>> Pools;
        std::vector<uint32> FreeList;
        std::vector<uint32> Versions;
    };
}

#include "Registry.inl"
