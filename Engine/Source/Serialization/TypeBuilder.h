#pragma once

#include "Serialization/FieldMeta.h"
#include "Serialization/TypeInfo.h"
#include "Core/Minimal.h"

namespace Source::Serialization
{
    template <typename TComponent>
    class TypeBuilder
    {
    public:
        explicit TypeBuilder(TypeInfo& InInfo) : Info(InInfo) {}

        TypeBuilder& Bind(ComponentResolver Resolve, ComponentEmplacer Emplace, ComponentRemover Remove);

        template <typename TField>
        TypeBuilder& Field(TField TComponent::* Member, std::string Name, FieldMeta Meta = {});

        template <typename TEnum>
        TypeBuilder& EnumField(TEnum TComponent::* Member, std::string Name, std::vector<std::string> Options);

    private:
        TypeInfo& Info;
    };
}

#include "TypeBuilder.inl"
