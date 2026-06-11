#pragma once

#include "../Core/IModule.h"
#include "../Core/Minimal.h"

namespace Source::Serialization { class ComponentRegistry; }

namespace Source::Modules
{
    class SerializationModule final : public Core::IModule
    {
    public:
        SerializationModule();

        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;

    private:
        Serialization::ComponentRegistry ComponentRegistry;
    };
}