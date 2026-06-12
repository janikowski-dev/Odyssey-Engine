#pragma once

#include "TypeRegistry.h"

namespace Source::Serialization
{
    template <typename TComponent>
    TypeBuilder<TComponent> TypeRegistry::Register(std::string Name)
    {
        TypeInfo& Info = Types[Name];
        Info.Name = Name;
        return TypeBuilder<TComponent>(Info);
    }
}
