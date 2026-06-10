#include "SceneSerializer.h"

#include <fstream>

namespace Source::Serialization
{
    bool SceneSerializer::SaveToFile(ECS::Registry& World, const std::string& Path) const
    {
        std::ofstream Out(Path);

        if (!Out)
        {
            return false;
        }

        Json Scene;
        Scene["entities"] = Json::array();

        for (ECS::Entity E : Registry.CollectEntities(World))
        {
            Json Components = Json::object();
            Registry.Save(World, E, Components);

            if (!Components.empty())
            {
                Scene["entities"].push_back({ { "components", Components } });
            }
        }

        Out << Scene.dump(2);
        return true;
    }

    bool SceneSerializer::LoadFromFile(const std::string& Path, ECS::Registry& World) const
    {
        std::ifstream In(Path);

        if (!In)
        {
            return false;
        }
        
        Json Scene;
        In >> Scene;
        
        if (!Scene.contains("entities"))
        {
            return false;
        }

        World.Clear();

        for (const auto& Entry : Scene.at("entities"))
        {
            ECS::Entity E = World.Create();

            if (Entry.contains("components"))
            {
                Registry.Load(World, E, Entry.at("components"));
            }
        }

        return true;
    }
}
