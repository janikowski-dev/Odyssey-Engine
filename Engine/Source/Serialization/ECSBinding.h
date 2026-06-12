#pragma once

namespace Source::ECS { class Registry; }

namespace Source::Serialization
{
    template <typename> class TypeBuilder;

    template <typename TComponent>
    void BindECS(TypeBuilder<TComponent>& Builder, ECS::Registry& Registry);
}

#include "ECSBinding.inl"
