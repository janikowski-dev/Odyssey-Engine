#pragma once

#include "Core/IModule.h"

namespace Source::Rendering { class Backend; class Procedural; class IRenderPass; }

namespace Source::Modules
{
    class RenderingModule final : public Core::IModule
    {
    public:
        RenderingModule();
        ~RenderingModule() override;

        Core::TickPolicy GetTickPolicy() const override { return Core::TickPolicy::Always; }
        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;

    private:
        std::vector<UniquePtr<Rendering::IRenderPass>> Passes;
        UniquePtr<Rendering::Backend> Backend;
    };
}