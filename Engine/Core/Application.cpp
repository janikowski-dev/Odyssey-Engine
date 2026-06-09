#include "Application.h"

#include "Editor/Bindings.h"

namespace Engine
{
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

		AppWindow = std::make_unique<Platform::Window>(InConfig.WindowConfig);
		AppWindow->Create(*EditorBridge);
	}

	Application::~Application()
	{
		AppWindow->Destroy();
	}

	void Application::Run()
	{
    	IsRunning = true;

    	while (IsRunning)
    	{
    	    if (AppWindow->ShouldClose())
			{
				IsRunning = false;
			}

			EditorBridge->Tick();
			AppWindow->Tick();
			EventBus->Flush();
    	}
	}
}