#include "Serialization/ReflectionHandler.h"

#include "Serialization/TypeRegistry.h"
#include "ECS/Entity.h"

namespace Source::Serialization
{
    Json GetComponentTypes()
    {
        return TypeRegistry::Get().Schema();
    }

    Json GetComponents(ECS::Entity Entity)
    {
        Json Out = Json::array();

        for (const auto& [Name, Info] : TypeRegistry::Get().GetTypes())
        {
            void* Component = Info.Resolve(Entity);
            
            if (!Component)
            {
                continue;
            }

            Json Fields = Json::object();

            for (const auto& Field : Info.Fields)
            {
                Fields[Field.Name] = Field.Get(Component);
            }

            Out.push_back({ { "Name", Name }, { "Fields", std::move(Fields) } });
        }

        return Out;
    }

    void SetComponent(ECS::Entity Entity, const std::string& Type, const Json& Fields)
    {
        const TypeInfo* Info = TypeRegistry::Get().Find(Type);

        if (!Info)
        {
            return;
        }

        void* Component = Info->Emplace(Entity);

        if (!Component)
        {
            return;
        }

        for (const auto& Field : Info->Fields)
        {
            auto It = Fields.find(Field.Name);

            if (It != Fields.end())
            {
                Field.Set(Component, *It);
            }
        }
    }

    void RemoveComponent(ECS::Entity Entity, const std::string &Type)
    {
        const TypeInfo* Info = TypeRegistry::Get().Find(Type);

        if (!Info)
        {
            return;
        }

        Info->Remove(Entity);
    }
}