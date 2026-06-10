#pragma once

#include "../IModule.h"
#include "../Types.h"

namespace Core::Rendering { class Renderer; }

namespace Core::Modules
{
    class SystemsModule final : public IModule
    {
    public:
        SystemsModule();
        ~SystemsModule() override;

        void Init(const ApplicationConfig Config, Context& Context) override;
        void Tick(const Context& Context) override;

    private:
        void InitRendering();
        void InitTime();
        void InitSystems(const ApplicationConfig Config, Context& Context);

        void UpdateSystems(const Context& Context);
        void HandleTime();

    private:
        UniquePtr<Rendering::Renderer> RendererBackend;
        float DeltaTime = 0.0f;
        Time LastTime{};
        Time CurrentTime{};
    };
}