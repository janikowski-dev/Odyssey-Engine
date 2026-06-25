#include "Serialization/SceneSerializer.h"

#include "Serialization/ReflectionHandler.h"
#include "ECS/Registry.h"

namespace Source::Serialization
{
    bool SaveScene(ECS::Registry &World, const std::string& Path)
    {
        std::ofstream Stream(Path);

        if (!Stream)
        {
            return false;
        }

        Json J;
        SerializeScene(World, J);
        Stream << J.dump(4);
        return Stream.good();
    }

    bool LoadScene(ECS::Registry &World, const std::string& Path)
    {
        std::ifstream Stream(Path);

        if (!Stream)
        {
            return false;
        }

        Json Scene;

        try
        {
            Stream >> Scene;
        }
        catch (const Json::exception&)
        {
            return false;
        }

        DeserializeScene(World, Scene);
        return true;
    }

    void SerializeScene(ECS::Registry& World, Json& Scene)
    {
        Json Entities = Json::array();

        World.Each([&](ECS::Entity Entity)
        {
            Json Components = GetComponents(Entity);
            
            if (!Components.empty())
            {
                Entities.push_back({{ "Components", std::move(Components) }});
            }
        });

        Scene = { { "Entities", std::move(Entities) } };
    }

    void DeserializeScene(ECS::Registry& World, const Json& Scene)
    {
        if (!Scene.is_object() || !Scene.contains("Entities") || !Scene["Entities"].is_array())
        {
            return;
        }

        World.Clear();

        for (const auto& Node : Scene.at("Entities"))
        {
            ECS::Entity Entity = World.Create();

            for (const auto& Component : Node.at("Components"))
            {
                SetComponent(Entity, Component.at("Name"), Component.at("Fields"));
            }
        }
    }
}

