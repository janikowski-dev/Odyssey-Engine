#include "Application.h"

#include "Components/MeshRenderer.h"
#include "Components/Transform.h"
#include "Components/Spin.h"

#include "Events/CreateEntity.h"
#include "Events/SaveScene.h"
#include "Events/LoadScene.h"
#include "Events/Ping.h"

#include "ECS/Entity.h"

#include <random>

namespace Core
{
	Application::Application(const Config::ApplicationConfig& InConfig) 
	{
		InitMessaging();
		InitBridge(InConfig);
		InitEcs();
		InitPlatform(InConfig);
		InitRendering();
    	InitSerialization();
		InitSpinning();
	}

	Application::~Application()
	{
		Window->Destroy();
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
			Window->Tick();
			MessageBus->Flush();
    	}
	}

	void Application::InitMessaging()
	{
		MessageBus = MakeUnique<Messaging::MessageBus>();
	}

	void Application::InitBridge(const Config::ApplicationConfig& InConfig)
	{
        static std::mt19937 rng{ std::random_device{}() };
        static std::uniform_real_distribution<float> dist(-2.0f, 2.0f);

		EditorBridge = MakeUnique<Editor::Bridge>();

		EditorBridge->On<Events::PingRequest, Events::PingResponse>(Events::PingKey, [](const Events::PingRequest&)
    	{
    	    return Events::PingResponse();
    	});
		
		EditorBridge->On<Events::CreateEntiryRequest, Events::CreateEntityResponse>(Events::CreateEntityKey, [this](const Events::CreateEntiryRequest&)
    	{
	    	Core::ECS::Entity E = World->Create();
	    	World->Add<Components::Transform>(E, Components::Transform{ {dist(rng), 0, 0}, {0, 0, 0}, {1, 1, 1} });
	    	World->Add<Components::MeshRenderer>(E, Components::MeshRenderer{ {0.85f, 0.30f, 0.22f} });
	    	World->Add<Components::Spin>(E, Components::Spin{ {0.0f, 0.8f, 0.0f} });
    	    return Events::CreateEntityResponse();
    	});
		
		EditorBridge->On<Events::SaveSceneRequest, Events::SaveSceneResponse>(Events::SaveSceneKey, [this](const Events::SaveSceneRequest& Request)
    	{
			SceneSerializer->SaveToFile(*World, Request.Path);
    	    return Events::SaveSceneResponse();
    	});
		
		EditorBridge->On<Events::LoadSceneRequest, Events::LoadSceneResponse>(Events::LoadSceneKey, [this](const Events::LoadSceneRequest& Request)
    	{
			SceneSerializer->LoadFromFile(Request.Path, *World);
    	    return Events::LoadSceneResponse();
    	});

		EditorBridge->Start(InConfig.EditorPort);
	}

	void Application::InitPlatform(const Config::ApplicationConfig& InConfig)
	{
		Window = MakeUnique<Platform::Window>(InConfig.WindowConfig);
		Window->Create(*EditorBridge);
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

	void Application::InitSerialization()
	{
		ComponentRegistry = MakeUnique<Serialization::ComponentRegistry>();

		ComponentRegistry->Register<Components::Transform>("Transform");
		ComponentRegistry->Register<Components::MeshRenderer>("Mesh");
		ComponentRegistry->Register<Components::Spin>("Spin");

		SceneSerializer = MakeUnique<Serialization::SceneSerializer>(*ComponentRegistry);
	}

	void Application::InitSpinning()
	{
		SpinSystem = MakeUnique<Systems::SpinSystem>();
	}

}
