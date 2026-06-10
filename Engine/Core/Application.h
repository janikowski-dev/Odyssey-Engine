#pragma once

#include "Config/ApplicationConfig.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpinSystem.h"
#include "Messaging/EventBus.h"
#include "Platform/Window.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"
#include "Types.h"

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
		UniquePtr<Systems::RenderSystem> RenderSystem;
		UniquePtr<Systems::SpinSystem> SpinSystem;
		UniquePtr<Messaging::EventBus> EventBus;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> AppWindow;
		UniquePtr<ECS::Registry> World;

		// It is here only temporarily
		UniquePtr<Rendering::Renderer> RendererBackend;
		SharedPtr<Rendering::Mesh> Cube;
	};
}
