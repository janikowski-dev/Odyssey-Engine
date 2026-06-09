#include "Application.h"

#include "Editor/Bindings.h"
#include "ECS/Entity.h"
#include "Components/MeshRenderer.h"
#include "Components/Transform.h"

namespace Core
{
	void SetupScene(Core::ECS::Registry& World, std::shared_ptr<Rendering::Mesh>& OutCube)
	{
	    OutCube = std::make_shared<Rendering::Mesh>(Rendering::Mesh::Cube());

	    Core::ECS::Entity e1 = World.Create();
	    World.Add<Components::Transform>(e1, Components::Transform{ {0,0,0}, {0,0,0}, {1,1,1} });
	    World.Add<Components::MeshRenderer>(e1, Components::MeshRenderer{ OutCube, {0.8f, 0.3f, 0.2f} });
		World.Add<Components::Spin>(e1, Components::Spin{ {0.0f, 0.9f, 0.0f} }); 

	    Core::ECS::Entity e2 = World.Create();
	    Components::Transform t2; t2.Position = {2.0f, 0.0f, 0.0f};
	    World.Add<Components::Transform>(e2, t2);
	    World.Add<Components::MeshRenderer>(e2, Components::MeshRenderer{ OutCube, {0.2f, 0.6f, 0.9f} });
		World.Add<Components::Spin>(e2, Components::Spin{ {0.7f, 0.0f, 0.5f} });
	}

	Application::Application(const Config::ApplicationConfig& InConfig) 
	{
		EventBus = std::make_unique<Messaging::EventBus>();

		EditorBridge = std::make_unique<Editor::Bridge>(*EventBus);
		EditorBridge->RegisterOutbound(Editor::EditorOutbound{});
		EditorBridge->RegisterInbound(Editor::EditorInbound{});
		EditorBridge->On("ping", [](const nlohmann::json&) { 
			return nlohmann::json::object();
		});
		EditorBridge->Start(InConfig.EditorPort);

		World = std::make_unique<ECS::Registry>();

		AppWindow = std::make_unique<Platform::Window>(InConfig.WindowConfig);
		AppWindow->Create(*EditorBridge);

		RendererBackend = std::make_unique<Rendering::Renderer>();
    	RendererBackend->SetViewport(1920, 1080);
    	Rendering::Camera Camera;
		Camera.Position = {3, 3, 6};
    	RendererBackend->SetCamera(Camera);

		RenderSystem = std::make_unique<Systems::RenderSystem>(*RendererBackend);
		
    	SetupScene(*World, Cube);

		SpinSystem = std::make_unique<Systems::SpinSystem>();
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
}
