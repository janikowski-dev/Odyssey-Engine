#pragma once

#include "FieldMeta.h"
#include "TypeInfo.h"

#include <string>
#include <vector>

namespace Source::Serialization
{
    template <typename TComponent>
    class TypeBuilder
    {
    public:
        explicit TypeBuilder(TypeInfo& InInfo) : Info(InInfo) {}

        TypeBuilder& Bind(ComponentResolver Resolve, ComponentEmplacer Emplace);

        template <typename TField>
        TypeBuilder& Field(TField TComponent::* Member, std::string Name, FieldMeta Meta = {});

        template <typename TEnum>
        TypeBuilder& EnumField(TEnum TComponent::* Member, std::string Name, std::vector<std::string> Options);

    private:
        TypeInfo& Info;
    };
}

#include "TypeBuilder.inl"
