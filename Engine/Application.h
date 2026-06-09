#pragma once

#include "Config/ApplicationConfig.h"
#include "Messaging/EventBus.h"
#include "Platform/Window.h"
#include "Editor/Bridge.h"

#include <memory>

namespace Engine
{
	class Application
	{
	public:
		Application(const Config::ApplicationConfig& InConfig = Config::ApplicationConfig());
		~Application();

		void Run();

	private:
		std::unique_ptr<Messaging::EventBus> EventBus;
		std::unique_ptr<Editor::Bridge> EditorBridge;
		std::unique_ptr<Platform::Window> AppWindow;
		bool IsRunning = false;
	};
}