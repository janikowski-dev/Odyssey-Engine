#pragma once

#include "../IModule.h"
#include "../Messaging/MessageBus.h"
#include "../Rendering/Renderer.h"
#include "../Rendering/Camera.h"
#include "../ECS/Registry.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/SpinSystem.h"

namespace Core
{
    class SystemsModule final : public IModule
    {
    public:
        SystemsModule() = default;
        ~SystemsModule() override = default;

        void Init(const ApplicationConfig Config, Context& Context) override
        {
            RendererBackend = MakeUnique<Rendering::Renderer>();
    	    RendererBackend->SetViewport(1280, 720);
    	    Rendering::Camera Camera;
		    Camera.Position = { 4.0f, 3.0f, 6.0f };
		    Camera.Target = { 0.0f, 0.0f, 0.0f };
		    Camera.Up = { 0.0f, 1.0f, 0.0f };
		    RendererBackend->SetCamera(Camera);

            Context.World = MakeUnique<ECS::Registry>();
		    Context.SpinSystem = MakeUnique<Systems::SpinSystem>();
		    Context.RenderSystem = MakeUnique<Systems::RenderSystem>(*RendererBackend);
        }

        void Tick(const Context& Context) override
        {
			Context.SpinSystem->Update(*Context.World, 0);
			Context.RenderSystem->Update(*Context.World);
        }
    
    private:
		UniquePtr<Rendering::Renderer> RendererBackend;
    };
}