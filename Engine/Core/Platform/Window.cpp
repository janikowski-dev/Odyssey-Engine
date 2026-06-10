#include "Window.h"

#include "../Events/Viewport.h"

#define GLFW_EXPOSE_NATIVE_WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3native.h>

#include <iostream>
#include <assert.h>

namespace Core::Platform
{
	Window::Window(const Config::WindowConfig& InConfig) : Config(InConfig)
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

	void Window::Tick() const
	{
    	glfwSwapBuffers(Handle);
    	glfwPollEvents();
	}

	void Window::Init() const
	{
        glfwInit();
		glfwWindowHint(GLFW_VISIBLE, Config.RenderWindow ? GL_TRUE : GL_FALSE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	}

	void Window::Setup()
	{
		glfwMakeContextCurrent(Handle);
		gladLoadGL(glfwGetProcAddress);
		glfwSwapInterval(Config.UseVSync ? 1 : 0);
		glfwSetWindowUserPointer(Handle, this);
	}

	GLFWwindow* Window::TryGet() const
	{
		return glfwCreateWindow(Config.Width, Config.Height, "Window", nullptr, nullptr);
	}

	void Window::Attach(Editor::Bridge& InBridge)
	{
		InBridge.On<Events::ViewportRequest, Events::ViewportResponse>(Events::ViewportKey, [this](const Events::ViewportRequest&)
    	{
    	    return Events::ViewportResponse { (uint64_t)(uintptr_t)glfwGetWin32Window(Handle) };
    	});
	}

	bool Window::TryCache(GLFWwindow* NewHandle)
	{
		Handle = NewHandle;

		if (Handle)
		{
			return true;
		}

		std::cerr << "Failed window creation!\n";
		return false;
	}
}
