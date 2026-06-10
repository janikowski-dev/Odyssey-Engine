#pragma once

#include "Serialization/SceneSerializer.h"
#include "Config/ApplicationConfig.h"
#include "Systems/RenderSystem.h"
#include "Systems/SpinSystem.h"
#include "Messaging/MessageBus.h"
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
		void InitSerialization();
		void InitMessaging();
		void InitBridge(const Config::ApplicationConfig& InConfig);
		void InitPlatform(const Config::ApplicationConfig& InConfig);
		void InitEcs();
		void InitSpinning();

	private:
		// Crucial
		UniquePtr<Serialization::SceneSerializer> SceneSerializer;
		UniquePtr<Systems::RenderSystem> RenderSystem;
		UniquePtr<Systems::SpinSystem> SpinSystem;
		UniquePtr<Messaging::MessageBus> MessageBus;
		UniquePtr<Editor::Bridge> EditorBridge;
		UniquePtr<Platform::Window> Window;
		UniquePtr<ECS::Registry> World;

		// Dependencies
		UniquePtr<Serialization::ComponentRegistry> ComponentRegistry;
		UniquePtr<Rendering::Renderer> RendererBackend;
	};
}
