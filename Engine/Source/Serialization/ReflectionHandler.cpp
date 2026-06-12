#include "ReflectionHandler.h"
#include "TypeRegistry.h"

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
            if (!Info.Resolve)
            {
                continue;
            }

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

            Out.push_back({ { "Type", Name }, { "Fields", std::move(Fields) } });
        }

        return Out;
    }

    void SetComponent(ECS::Entity entity, const std::string& type, const Json& fields)
    {
        const TypeInfo* Info = TypeRegistry::Get().Find(type);

        if (!Info || !Info->Resolve)
        {
            return;
        }

        void* Component = Info->Resolve(entity);
        
        if (!Component)
        {
            return;
        }

        for (const auto& Field : Info->Fields)
        {
            auto It = fields.find(Field.Name);

            if (It != fields.end())
            {
                Field.Set(Component, *It);
            }
        }
    }
}
