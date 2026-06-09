#pragma once

#include "Registry.h"

namespace Engine::ECS
{
    template<typename T, typename... Args>
    T& Registry::Add(Entity InEntity, Args&&... InArgs)
    {
        return GetPool<T>().Add(InEntity.Index, std::forward<Args>(InArgs)...);
    }

    template<typename T>
    void Registry::Remove(Entity InEntity)
    {
        GetPool<T>().Remove(InEntity.Index);
    }

    template<typename T>
    bool Registry::Has(Entity InEntity)
    {
        return GetPool<T>().Has(InEntity.Index);
    }

    template<typename T>
    T& Registry::Get(Entity InEntity)
    {
        return GetPool<T>().Get(InEntity.Index);
    }

    template<typename... Ts, typename Fn>
    void Registry::View(Fn&& InFunc)
    {
        using First = std::tuple_element_t<0, std::tuple<Ts...>>;
        Pool<First>& Primary = GetPool<First>();

        const std::vector<std::uint32_t> EntityList = Primary.Entities();

        for (std::uint32_t Index : EntityList)
        {
            if ((GetPool<Ts>().Has(Index) && ...))
            {
                InFunc(Entity{ Index, Versions[Index] }, GetPool<Ts>().Get(Index)...);
            }
        }
    }

    template<typename T>
    Pool<T>& Registry::GetPool()
    {
        const std::type_index Key(typeid(T));
        auto It = Pools.find(Key);
        
        if (It == Pools.end())
        {
            It = Pools.emplace(Key, std::make_unique<Pool<T>>()).first;
        }

        return *static_cast<Pool<T>*>(It->second.get());
    }
}