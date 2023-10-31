#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;

	void RendererCommand::Clear()
	{
		s_RendererAPI->Clear();
	}

	void RendererCommand::ClearColor(const glm::vec4& color)
	{
		s_RendererAPI->SetClearColor(color);
	}

	void RendererCommand::DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		s_RendererAPI->DrawElements(vertexArray);
	}
}