#pragma once

#include "../Core/Minimal.h"

#include "TypeBuilder.h"
#include "TypeInfo.h"

#include <string>
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
