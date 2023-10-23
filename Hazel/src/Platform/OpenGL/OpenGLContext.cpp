#include "OpenGLContext.h"
#include "Hazel/HazelLog.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		HAZEL_CORE_ASSERT(m_WindowHandle != nullptr, "WindowsHandle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HAZEL_CORE_ASSERT(status, "Failed to initialize Glad!");

		HAZEL_CORE_INFO("OpenGL Info: {0}", (const char*)glGetString(GL_VENDOR));
		HAZEL_CORE_INFO("  OpenGL vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HAZEL_CORE_INFO("  OpenGL Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HAZEL_CORE_INFO("  OpenGL Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffer()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}