#pragma once

#include "Core/IModule.h"
#include "Core/Minimal.h"

namespace Source::Rendering { class Renderer; class Mesh; }

namespace Source::Modules
{
    class SystemsModule final : public Core::IModule
    {
    public:
        SystemsModule();
        ~SystemsModule() override;

        void Init(const Core::ApplicationConfig Config, Core::Context& Context) override;
        void Tick(const Core::Context& Context) override;

    private:
        void InitRendering();
        void InitTime();
        void InitSystems(const Core::ApplicationConfig Config, Core::Context& Context);

        void UpdateSystems(const Core::Context& Context);
        void HandleTime();

    private:
        UniquePtr<Rendering::Renderer> RendererBackend;
        float DeltaTime = 0.0f;
        Time CurrentTime {};
        Time LastTime {};
    };
}