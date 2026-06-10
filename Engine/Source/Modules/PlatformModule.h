#pragma once

#include "../Core/IModule.h"

namespace Source::Platfom { class Window; }

namespace Source::Modules
{
    class PlatformModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;
    };
}