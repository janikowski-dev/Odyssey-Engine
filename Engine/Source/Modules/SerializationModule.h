#pragma once

#include "../Core/IModule.h"
#include "../Core/Minimal.h"

namespace Source::Modules
{
    class SerializationModule final : public Core::IModule
    {
    public:
        SerializationModule();

        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
    };
}