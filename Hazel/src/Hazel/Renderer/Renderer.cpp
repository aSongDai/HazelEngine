
#include "Renderer.h"	
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RendererCommand::DrawIndex(vertexArray);
	}
}