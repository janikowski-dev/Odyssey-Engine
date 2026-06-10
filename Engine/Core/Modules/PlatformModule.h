#pragma once

#include "../IModule.h"

namespace Core::Platfom { class Window; }

namespace Core::Modules
{
    class PlatformModule final : public IModule
    {
    public:
        void Init(const ApplicationConfig Config, Context& Context) override;
        void Tick(const Context& Context) override;
    };
}