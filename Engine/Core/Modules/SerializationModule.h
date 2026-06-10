#pragma once

#include "../IModule.h"
#include "../Types.h"

namespace Core::Serialization { class ComponentRegistry; }

namespace Core::Modules
{
    class SerializationModule final : public IModule
    {
    public:
        SerializationModule();

        void Init(const ApplicationConfig Config, Context& Context) override;

    private:
        UniquePtr<Serialization::ComponentRegistry> ComponentRegistry;
    };
}