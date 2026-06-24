#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Rendering { class Renderer; class Mesh; }

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
        UniquePtr<Rendering::Renderer> RendererBackend;
    };
}