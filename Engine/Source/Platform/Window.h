#pragma once

#include "../Core/ApplicationConfig.h"
#include "../Editor/Bridge.h"
#include "../Core/Types.h"

struct GLFWwindow;

namespace Source::Platform
{
	class Window
	{
	public:
		Window(const Source::Core::WindowConfig& InConfig = Source::Core::WindowConfig());
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
		Source::Core::WindowConfig Config;
		GLFWwindow* Handle = nullptr;
	};
}
