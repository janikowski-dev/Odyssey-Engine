#include "Platform/Window.h"

#include "Core/ApplicationConfig.h"
#include "Platform/Context.h"
#include "Platform/Input.h"
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

	void Window::Create()
	{
		Init();

		if (!TryCache(TryCreate()))
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

	void Window::Focus() const
	{
	    glfwFocusWindow(Handle);
	}

    bool Window::ShouldClose() const
    {
		return glfwWindowShouldClose(Handle);
	}

    uint64 Window::GetWindowHandle() const
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

	    glfwSetWindowFocusCallback(Handle, [](GLFWwindow* W, int Focused)
	    {
			static_cast<Context*>(glfwGetWindowUserPointer(W))->WindowPtr->OnFocusChanged(Focused == GLFW_TRUE);
	    });
	}

	GLFWwindow* Window::TryCreate() const
	{
		return glfwCreateWindow(Config->Width, Config->Height, "Window", nullptr, nullptr);
	}

	void* Window::GetHandle() const
	{
		return Handle;
	}
	
	bool Window::TryCache(GLFWwindow* NewHandle)
	{
		Handle = NewHandle;

		if (Handle)
		{
			return true;
		}

		return false;
	}
}
