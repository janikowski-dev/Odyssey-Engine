#pragma once

#include "../Core/IModule.h"
#include "../Core/Types.h"

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
        // This method is here temporarily
        Rendering::Mesh MakeCube();

    private:
        UniquePtr<Rendering::Renderer> RendererBackend;
        // This variable is here temporarily
		UniquePtr<Rendering::Mesh> Cube;
        float DeltaTime = 0.0f;
        Time LastTime{};
        Time CurrentTime{};
    };
}