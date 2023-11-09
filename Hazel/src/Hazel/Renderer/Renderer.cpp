
#include "Renderer.h"	
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Hazel
{
	struct SceneData* Renderer::s_SceneData = new SceneData;

	void Renderer::BeginScene(const Camera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader)
	{
		shader->Bind();
		shader->UploadUniformMatrix("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);

		RendererCommand::DrawIndex(vertexArray);
	}
}