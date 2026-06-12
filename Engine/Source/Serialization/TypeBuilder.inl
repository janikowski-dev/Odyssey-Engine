#pragma once

#include "Serialization/TypeBuilder.h"
#include "Serialization/FieldTraits.h"

#include <algorithm>
#include <type_traits>

namespace Source::Serialization
{
    template <typename TComponent>
    TypeBuilder<TComponent>& TypeBuilder<TComponent>::Bind(ComponentResolver Resolve, ComponentEmplacer Emplace)
    {
        Info.Resolve = std::move(Resolve);
        Info.Emplace = std::move(Emplace);
        return *this;
    }

    template <typename TComponent>
    template <typename TField>
    TypeBuilder<TComponent>& TypeBuilder<TComponent>::Field(TField TComponent::* Member, std::string Name, FieldMeta Meta)
    {
        FieldInfo Field;
        Field.Name = std::move(Name);
        Field.Type = FieldTraits<TField>::TypeName;
        Field.Meta = std::move(Meta);

        Field.Get = [Member](const void* Component) -> Json
        {
            return FieldTraits<TField>::ToJson(static_cast<const TComponent*>(Component)->*Member);
        };

        FieldMeta Captured = Field.Meta;

        Field.Set = [Member, Captured](void* Component, const Json& J)
        {
            TField Value = FieldTraits<TField>::FromJson(J);

            if constexpr (std::is_arithmetic_v<TField>)
            {
                if (Captured.Min)
                {
                    Value = std::max(Value, static_cast<TField>(*Captured.Min));
                }
                
                if (Captured.Max)
                {
                    Value = std::min(Value, static_cast<TField>(*Captured.Max));
                }
            }

            static_cast<TComponent*>(Component)->*Member = Value;
        };

        Info.Fields.push_back(std::move(Field));
        return *this;
    }

    template <typename TComponent>
    template <typename TEnum>
    TypeBuilder<TComponent>& TypeBuilder<TComponent>::EnumField(TEnum TComponent::* Member, std::string Name, std::vector<std::string> Options)
    {
        using TUnderlying = std::underlying_type_t<TEnum>;

        FieldInfo Field;
        Field.Name = std::move(Name);
        Field.Type = "Enum";
        Field.Meta.Options = std::move(Options);

        Field.Get = [Member](const void* Component) -> Json
        {
            return static_cast<TUnderlying>(static_cast<const TComponent*>(Component)->*Member);
        };

        const std::size_t Count = Field.Meta.Options.size();

        Field.Set = [Member, Count](void* Component, const Json& J)
        {
            TUnderlying Idx = J.get<TUnderlying>();

            if (Idx >= 0 && static_cast<std::size_t>(Idx) < Count)
            {
                static_cast<TComponent*>(Component)->*Member = static_cast<TEnum>(Idx);
            }
        };

        Info.Fields.push_back(std::move(Field));
        return *this;
    }
}