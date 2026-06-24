#include "ECS/Registry.h"

namespace Source::ECS
{
    Entity Registry::Create()
    {
        uint32 Index;

        if (FreeList.empty())
        {
            Index = static_cast<uint32>(Versions.size());
            Versions.push_back(0);
        }
        else
        {
            Index = FreeList.back();
            FreeList.pop_back();
        }

        OnEntityCreated(Index);
        return Entity{ Index, Versions[Index] };
    }

    Entity Registry::Get(uint32 Index)
    {
        if (Index >= Versions.size())
        {
            return NULL_ENTITY;
        }

        return Entity{ Index, Versions[Index] };
    }

    void Registry::Destroy(Entity InEntity)
    {
        if (!IsValid(InEntity))
        {
            return;
        }

        for (auto& [Type, Pool] : Pools)
        {
            Pool->Remove(InEntity.Index);
        }

        OnEntityDestroyed(InEntity.Index);
        ++Versions[InEntity.Index];
        FreeList.push_back(InEntity.Index);
    }

    void Registry::Clear()    
    {
        for (auto& [Type, Pool] : Pools)
        {
            Pool->Clear();
        }
    
        FreeList.clear();
        Versions.clear();
    }

    bool Registry::IsValid(Entity InEntity) const
    {
        return InEntity.Index < Versions.size() && Versions[InEntity.Index] == InEntity.Version;
    }
}