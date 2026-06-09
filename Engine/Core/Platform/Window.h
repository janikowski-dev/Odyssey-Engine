#pragma once

#include "../Config/WindowConfig.h"
#include "../Editor/Bridge.h"

struct GLFWwindow;

namespace Core::Platform
{
	class Window
	{
	public:
		Window(const Config::WindowConfig& InConfig = Config::WindowConfig());
		~Window();

		void Create(Editor::Bridge& InBridge);
		void Destroy();

		void Tick() const;

    private:
        void Init() const;
	    GLFWwindow* TryGet() const;
	    bool TryCache(GLFWwindow* NewHandle);
		void Attach(Editor::Bridge& InBridge);
        void Setup();
		
	private:
		Config::WindowConfig Config;
		GLFWwindow* Handle = nullptr;
	};
}
