#pragma once

#include "Core/Minimal.h"

namespace Source::Core { struct WindowConfig; }

struct GLFWwindow;

namespace Source::Platform
{
	class Window
	{
	public:
		Window(const Core::WindowConfig& InConfig);
		~Window();
		
		void Create();
		void Destroy();
		void Refresh() const;
		bool ShouldClose() const;
		uint64 GetWindowHandle() const;
		void* GetHandle() const;
		void Focus() const;

    private:
        void Init() const;
	    GLFWwindow* TryCreate() const;
	    bool TryCache(GLFWwindow* NewHandle);
        void Setup();
		
	public:
		Event<bool> OnFocusChanged;

	private:
		const Core::WindowConfig* Config = nullptr;
		GLFWwindow* Handle = nullptr;
	};
}
