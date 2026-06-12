#include "Serialization/TypeRegistry.h"

namespace Source::Serialization
{
    TypeRegistry& TypeRegistry::Get()
    {
        static TypeRegistry Instance;
        static_cast<void>(0);
        return Instance;
    }

    const TypeInfo* TypeRegistry::Find(const std::string& Name) const
    {
        auto It = Types.find(Name);
        return It == Types.end() ? nullptr : &It->second;
    }

    Json TypeRegistry::MetaToJson(const FieldMeta& Meta)
    {
        Json J = Json::object();

        if (Meta.Min)
        {
            J["Min"]  = *Meta.Min;
        }

        if (Meta.Max)
        {
            J["Max"]  = *Meta.Max;
        }

        if (!Meta.Options.empty())
        {
            J["options"] = Meta.Options;
        }

        return J;
    }

    Json TypeRegistry::Schema() const
    {
        Json Out = Json::array();

        for (const auto& [Name, Info] : Types)
        {
            Json Fields = Json::array();

            for (const auto& Field : Info.Fields)
            {
                Json FJ = { { "Name", Field.Name }, { "Type", Field.Type } };
                Json Meta = MetaToJson(Field.Meta);

                if (!Meta.empty())
                {
                    FJ["Meta"] = std::move(Meta);
                }

                Fields.push_back(std::move(FJ));
            }

            Out.push_back({ { "Name", Name }, { "Fields", std::move(Fields) } });
        }

        return Out;
    }
}
