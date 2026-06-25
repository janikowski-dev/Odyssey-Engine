#pragma once

#include "Core/IModule.h"

namespace Source::Modules
{
    class RuntimeModule final : public Core::IModule
    {
    public:
        Core::TickPolicy GetTickPolicy() const override { return Core::TickPolicy::Always; }
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;
    };
}