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

		virtual void OnBeginPlay(const Core::Context& Context);
		virtual void OnEndPlay(const Core::Context& Context);

        void Tick(const Core::Context& Context) override;

    private:
        std::vector<UniquePtr<Rendering::IRenderPass>> ProjectPasses;
        std::vector<UniquePtr<Rendering::IRenderPass>> EditorPasses;
        UniquePtr<Rendering::Backend> Backend;
        bool IsInEditor = false;
        bool IsInPlay = false;
    };
}