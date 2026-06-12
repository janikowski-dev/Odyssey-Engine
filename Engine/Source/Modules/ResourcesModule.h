#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Modules
{
    class ResourcesModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
    };
}