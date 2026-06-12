#pragma once

#include "Serialization/TypeBuilder.h"
#include "Serialization/TypeInfo.h"
#include "Core/Minimal.h"

#include <unordered_map>

namespace Source::Serialization
{
    class TypeRegistry
    {
    public:
        static TypeRegistry& Get();

        template <typename TComponent>
        TypeBuilder<TComponent> Register(std::string Name);

        const TypeInfo* Find(const std::string& Name) const;

        const std::unordered_map<std::string, TypeInfo>& GetTypes() const { return Types; }

        Json Schema() const;

    private:
        static Json MetaToJson(const FieldMeta& Meta);

    private:
        std::unordered_map<std::string, TypeInfo> Types;
    };
}

#include "TypeRegistry.inl"
