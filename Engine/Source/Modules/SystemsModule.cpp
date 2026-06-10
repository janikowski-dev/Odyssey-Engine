#include "SystemsModule.h"

#include "../Messaging/MessageBus.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Camera.h"
#include "../ECS/Registry.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/SpinSystem.h"

namespace Source::Modules
{
    void SystemsModule::Init(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        InitRendering();
        InitTime();
        InitSystems(Config, Context);
    }

    void SystemsModule::Tick(const Core::Context& Context)
    {
        HandleTime();
        UpdateSystems(Context);
    }

    void SystemsModule::InitRendering()
    {
        RendererBackend = MakeUnique<Rendering::Renderer>();
        RendererBackend->SetViewport(1280, 720);

        Rendering::Camera Camera;
        Camera.Position = { 4.0f, 3.0f, 6.0f };
        Camera.Target = { 0.0f, 0.0f, 0.0f };
        Camera.Up = { 0.0f, 1.0f, 0.0f };
        RendererBackend->SetCamera(Camera);
    }

    void SystemsModule::InitTime()
    {
        LastTime = Clock::now();
    }

    void SystemsModule::InitSystems(const Core::ApplicationConfig Config, Core::Context& Context)
    {
        Context.World = MakeUnique<ECS::Registry>();
        Context.SpinSystem = MakeUnique<Systems::SpinSystem>();
        Context.RenderSystem = MakeUnique<Systems::RenderSystem>(*RendererBackend);
    }

    void SystemsModule::HandleTime()
    {
        CurrentTime = Clock::now();
        DeltaTime = Duration(CurrentTime - LastTime).count();
        LastTime = CurrentTime;
    }

    void SystemsModule::UpdateSystems(const Core::Context& Context)
    {
        Context.SpinSystem->Update(*Context.World, DeltaTime);
        Context.RenderSystem->Update(*Context.World);
    }
}