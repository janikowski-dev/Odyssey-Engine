#include "Platform/Window.h"

#include "Core/ApplicationConfig.h"
#include "Events/GetViewport.h"
#include "Editor/Bridge.h"
#include "ECS/Registry.h"
#include "ECS/Entity.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace Source::Platform
{
	Window::Window(const Source::Core::WindowConfig& InConfig) : Config(&InConfig)
	{
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create(Editor::Bridge& InBridge)
	{
		Init();

		if (!TryCache(TryGet()))
		{
			return;
		}

		Attach(InBridge);
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

	void Window::Attach(Editor::Bridge& InBridge)
	{
		InBridge.On<Events::GetViewportRequest, Events::GetViewportResponse>(Events::GetViewportKey, [this](const Events::GetViewportRequest&)
    	{
    	    return Events::GetViewportResponse { (uint64)(uintptr_t)glfwGetWin32Window(Handle) };
    	});
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
