#pragma once

#include "Core/IModule.h"

namespace Source::Modules
{
    class ResourcesModule final : public Core::IModule
    {
    public:
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;

    private:
        void InitCache(Core::Context& Context);
        void LoadResources(const Core::ApplicationConfig Config, Core::Context& Context);
    };
}