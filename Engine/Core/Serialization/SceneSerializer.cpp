#include "SceneSerializer.h"

#include <fstream>

namespace Core::Scene
{
    Json SceneSerializer::Save(ECS::Registry& World) const
    {
        Json Scene;
        Scene["version"] = Version;
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
        return Scene;
    }

    void SceneSerializer::Load(const Json& Scene, ECS::Registry& World) const
    {
        if (!Scene.contains("entities"))
        {
            return;
        }

        for (const auto& Entry : Scene.at("entities"))
        {
            ECS::Entity E = World.Create();

            if (Entry.contains("components"))
            {
                Registry.Load(World, E, Entry.at("components"));
            }
        }
    }

    bool SceneSerializer::SaveToFile(ECS::Registry& World, const std::string& Path) const
    {
        std::ofstream Out(Path);

        if (!Out)
        {
            return false;
        }

        Out << Save(World).dump(2);
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
        Load(Scene, World);
        return true;
    }
}