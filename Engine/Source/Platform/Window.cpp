#include "Platform/Window.h"

#include "Core/ApplicationConfig.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"
#include "ECS/Entity.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include "Window.h"

namespace Source::Platform
{
	Window::Window(const Source::Core::WindowConfig& InConfig) : Config(&InConfig)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		Init();

		if (!TryCache(TryGet()))
		{
			return;
		}

		Setup();
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(Handle);
        glfwTerminate();
	}

	void Window::Refresh() const
	{
    	glfwSwapBuffers(Handle);
    	glfwPollEvents();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(Handle);
	}

    uint64 Window::GetHandle() const
    {
		return (uint64)(uintptr_t)glfwGetWin32Window(Handle);
    }
	
    void Window::Init() const
    {
        glfwInit();
		glfwWindowHint(GLFW_VISIBLE, Config->RenderWindow ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	}

	void Window::Setup()
	{
		glfwMakeContextCurrent(Handle);
		gladLoadGL(glfwGetProcAddress);
		glfwSwapInterval(Config->UseVSync ? 1 : 0);
		glfwSetWindowUserPointer(Handle, this);
	}

	GLFWwindow* Window::TryGet() const
	{
		return glfwCreateWindow(Config->Width, Config->Height, "Window", nullptr, nullptr);
	}

	bool Window::TryCache(GLFWwindow* NewHandle)
	{
		Handle = NewHandle;

		if (Handle)
		{
			return true;
		}

		DebugError << "Failed window creation!\n";
		return false;
	}
}
