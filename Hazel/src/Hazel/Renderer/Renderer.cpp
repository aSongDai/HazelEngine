#include "Renderer.h"

#include "RendererCommand.h"

namespace Hazel
{
	void Renderer::BeginScene()
	{
		// TODO:	
		// 设置相机、灯光、环境等等
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		RendererCommand::DrawIndexed(vertexArray);
	}
}