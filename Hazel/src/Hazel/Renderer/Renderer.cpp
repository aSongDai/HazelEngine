#include "Renderer.h"

#include "RendererCommand.h"

namespace Hazel
{
	void Renderer::BeginScene()
	{
		// TODO:	
		// ����������ƹ⡢�����ȵ�
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RendererCommand::DrawIndexed(vertexArray);
	}
}