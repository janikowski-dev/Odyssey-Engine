#include "ComponentRegistry.h"

#include <unordered_map>

namespace Core::Scene
{
    void ComponentRegistry::Save(ECS::Registry& World, ECS::Entity E, Json& Out) const
    {
        for (const auto& [Name, Ops] : Types)
        {
            Ops.Save(World, E, Out);
        }
    }

    void ComponentRegistry::Load(ECS::Registry& World, ECS::Entity E, const Json& Data) const
    {
        for (auto It = Data.begin(); It != Data.end(); ++It)
        {
            auto Found = Types.find(It.key());

            if (Found != Types.end())
            {
                Found->second.Load(World, E, It.value());
            }
        }
    }

    std::vector<ECS::Entity> ComponentRegistry::CollectEntities(ECS::Registry& World) const
    {
        std::unordered_map<uint32, ECS::Entity> Seen;

        for (const auto& [Name, Ops] : Types)
        {
            std::vector<ECS::Entity> Found;
            Ops.Collect(World, Found);

            for (ECS::Entity E : Found)
            {
                Seen[E.Index] = E;
            }
        }

        std::vector<ECS::Entity> Result;
        Result.reserve(Seen.size());

        for (const auto& [Index, E] : Seen)
        {
            Result.push_back(E);
        }

        return Result;
    }
}