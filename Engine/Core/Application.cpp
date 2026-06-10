#include "Application.h"

#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
#include "Events/Ping.h"
#include "ECS/Entity.h"

namespace Core
{
	Application::Application(const Config::ApplicationConfig& InConfig) 
	{
		InitMessaging();
		InitBridge(InConfig);
		InitEcs();
		InitPlatform(InConfig);
		InitRendering();
    	InitScene();
		InitSpinning();
	}

	Application::~Application()
	{
		AppWindow->Destroy();
	}

	void Application::Run()
	{
    	auto LastTime = Clock::now();

    	while (true)
    	{
        	auto Time = Clock::now();
			auto DeltaTime = Duration(Time - LastTime).count();
			LastTime = Time;

			SpinSystem->Update(*World, DeltaTime);
			RenderSystem->Update(*World);
			
			EditorBridge->Tick();
			AppWindow->Tick();
			EventBus->Flush();
    	}
	}

	void Application::InitMessaging()
	{
		EventBus = MakeUnique<Messaging::EventBus>();
	}

	void Application::InitBridge(const Config::ApplicationConfig& InConfig)
	{
		EditorBridge = MakeUnique<Editor::Bridge>();
		EditorBridge->On<Events::PingRequest, Events::PingResponse>("ping", [](const Events::PingRequest&)
    	{
    	    return Events::PingResponse();
    	});
		EditorBridge->Start(InConfig.EditorPort);
	}

	void Application::InitPlatform(const Config::ApplicationConfig& InConfig)
	{
		AppWindow = MakeUnique<Platform::Window>(InConfig.WindowConfig);
		AppWindow->Create(*EditorBridge);
	}

	void Application::InitEcs()
	{
		World = MakeUnique<ECS::Registry>();
	}

	void Application::InitRendering()
	{
		RendererBackend = MakeUnique<Rendering::Renderer>();
    	RendererBackend->SetViewport(1280, 720);
    	Rendering::Camera Camera;
		Camera.Position = { 4.0f, 3.0f, 6.0f };
		Camera.Target = { 0.0f, 0.0f, 0.0f };
		Camera.Up = { 0.0f, 1.0f, 0.0f };
		RendererBackend->SetCamera(Camera);

		RenderSystem = MakeUnique<Systems::RenderSystem>(*RendererBackend);
	}

	void Application::InitScene()
	{
	    Cube = MakeShared<Rendering::Mesh>(Rendering::Mesh::Cube());

	    Core::ECS::Entity e1 = World->Create();
	    World->Add<Components::Transform>(e1, Components::Transform{ {-1.6f, 0, 0}, {0, 0, 0}, {1, 1, 1} });
	    World->Add<Components::MeshRenderer>(e1, Components::MeshRenderer{ Cube, {0.85f, 0.30f, 0.22f} });
	    World->Add<Components::Spin>(e1, Components::Spin{ {0.0f, 0.8f, 0.0f} });

	    Core::ECS::Entity e2 = World->Create();
	    World->Add<Components::Transform>(e2, Components::Transform{ {1.6f, 0, 0}, {0, 0, 0}, {0.8f, 0.8f, 0.8f} });
	    World->Add<Components::MeshRenderer>(e2, Components::MeshRenderer{ Cube, {0.25f, 0.55f, 0.90f} });
	    World->Add<Components::Spin>(e2, Components::Spin{ {0.5f, 0.0f, 0.6f} });
	}

	void Application::InitSpinning()
	{
		SpinSystem = MakeUnique<Systems::SpinSystem>();
	}

}
