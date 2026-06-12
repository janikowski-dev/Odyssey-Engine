#pragma once

#include "ECS/Registry.h"

namespace Source::ECS
{
    template<typename TComponent, typename... TArgs>
    TComponent& Registry::Add(Entity InEntity, TArgs&&... InArgs)
    {
        return GetPool<TComponent>().Add(InEntity.Index, std::forward<TArgs>(InArgs)...);
    }

    template<typename TComponent>
    void Registry::Remove(Entity InEntity)
    {
        GetPool<TComponent>().Remove(InEntity.Index);
    }

    template<typename TComponent>
    bool Registry::Has(Entity InEntity)
    {
        return GetPool<TComponent>().Has(InEntity.Index);
    }

    template<typename TComponent>
    TComponent& Registry::Get(Entity InEntity)
    {
        return GetPool<TComponent>().Get(InEntity.Index);
    }

    template<typename... TComponents, typename TFunction>
    void Registry::View(TFunction&& InFunction)
    {
        using First = std::tuple_element_t<0, std::tuple<TComponents...>>;
        Pool<First>& Primary = GetPool<First>();

        const std::vector<uint32> EntityList = Primary.Entities();

        for (uint32 Index : EntityList)
        {
            if ((GetPool<TComponents>().Has(Index) && ...))
            {
                InFunction(Entity{ Index, Versions[Index] }, GetPool<TComponents>().Get(Index)...);
            }
        }
    }

    template<typename TComponent>
    Pool<TComponent>& Registry::GetPool()
    {
        const std::type_index Key(typeid(TComponent));
        auto It = Pools.find(Key);
        
        if (It == Pools.end())
        {
            It = Pools.emplace(Key, MakeUnique<Pool<TComponent>>()).first;
        }

        return *static_cast<Pool<TComponent>*>(It->second.get());
    }
}