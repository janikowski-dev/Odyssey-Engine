#include "Registry.h"

namespace Core::ECS
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

        return Entity{ Index, Versions[Index] };
    }

    void Registry::Destroy(Entity InEntity)
    {
        if (!IsValid(InEntity))
        {
            return;
        }

        for (auto& [Type, PoolPtr] : Pools)
        {
            PoolPtr->Remove(InEntity.Index);
        }

        ++Versions[InEntity.Index];
        FreeList.push_back(InEntity.Index);
    }

    bool Registry::IsValid(Entity InEntity) const
    {
        return InEntity.Index < Versions.size() && Versions[InEntity.Index] == InEntity.Version;
    }
}