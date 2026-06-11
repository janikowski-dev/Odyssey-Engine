#pragma once

#include "../Core/Minimal.h"

namespace Source::Core { struct WindowConfig; }
namespace Source::Editor { class Bridge; }

struct GLFWwindow;

namespace Source::Platform
{
	class Window
	{
	public:
		Window(const Core::WindowConfig& InConfig);
		~Window();

		void Create(Editor::Bridge& InBridge);
		void Destroy();
		void Refresh() const;

    private:
        void Init() const;
	    GLFWwindow* TryGet() const;
	    bool TryCache(GLFWwindow* NewHandle);
		void Attach(Editor::Bridge& InBridge);
        void Setup();
		
	private:
		const Core::WindowConfig* Config = nullptr;
		GLFWwindow* Handle = nullptr;
	};
}
