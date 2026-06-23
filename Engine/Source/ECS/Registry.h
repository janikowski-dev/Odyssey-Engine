#pragma once

#include "Core/Minimal.h"
#include "ECS/Entity.h"
#include "ECS/Pool.h"

namespace Source::ECS
{
    class Registry
    {
    public:
        Entity Create();
        Entity Get(uint32 Index);
        void Destroy(Entity InEntity);
        void Clear();
        bool IsValid(Entity InEntity) const;

        template<typename TComponent, typename... TArgs>
        TComponent& Add(Entity InEntity, TArgs&&... InArgs);

        template<typename TComponent>
        void Remove(Entity InEntity);

        template<typename TComponent>
        bool Has(Entity InEntity);

        template<typename TComponent>
        TComponent& Get(Entity InEntity);

        template<typename TComponent>
        TComponent& GetOrAdd(Entity InEntity);

        template<typename TComponent>
        TComponent* TryGet(Entity InEntity);

        template<typename... TComponents, typename TFunction>
        void View(TFunction&& InFunction);

    private:
        template<typename TComponent>
        Pool<TComponent>& GetPool();
        
    public:
        Event<uint32> OnEntityAdded;

    private:
        std::unordered_map<std::type_index, UniquePtr<IPool>> Pools;
        std::vector<uint32> FreeList;
        std::vector<uint32> Versions;
    };
}

#include "Registry.inl"
