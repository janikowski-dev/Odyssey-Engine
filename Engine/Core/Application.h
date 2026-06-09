#pragma once

#include "Config/ApplicationConfig.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpinSystem.h"
#include "Messaging/EventBus.h"
#include "Platform/Window.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"

#include <memory>

namespace Core
{
	class Application
	{
	public:
		Application(const Config::ApplicationConfig& InConfig = Config::ApplicationConfig());
		~Application();

		void Run();

	private:
		void InitRendering();
		void InitScene();
		void InitMessaging();
		void InitBridge(const Config::ApplicationConfig& InConfig);
		void InitPlatform(const Config::ApplicationConfig& InConfig);
		void InitEcs();
		void InitSpinning();

	private:
    	using Duration = std::chrono::duration<float>;
    	using Clock = std::chrono::steady_clock;

		std::unique_ptr<Systems::RenderSystem> RenderSystem;
		std::unique_ptr<Systems::SpinSystem> SpinSystem;
		std::unique_ptr<Messaging::EventBus> EventBus;
		std::unique_ptr<Editor::Bridge> EditorBridge;
		std::unique_ptr<Platform::Window> AppWindow;
		std::unique_ptr<ECS::Registry> World;

		// It is here only temporarily
		std::unique_ptr<Rendering::Renderer> RendererBackend;
		std::shared_ptr<Rendering::Mesh> Cube;
	};
}
