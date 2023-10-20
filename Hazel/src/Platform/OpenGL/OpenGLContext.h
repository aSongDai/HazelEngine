#pragma once
#include "Hazel/Core.h"
#include "Hazel/Renderer/GraphicContext.h"

struct GLFWwindow;
namespace Hazel
{

	class HAZEL_API OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffer() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}