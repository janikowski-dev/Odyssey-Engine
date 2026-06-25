#pragma once

#include "Core/IModule.h"

namespace Source::Modules
{
    class WorldModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
    };
}