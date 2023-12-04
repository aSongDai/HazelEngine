#include "Renderer.h"

#include "RendererCommand.h"

namespace Hazel
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthogonalCamera& camera)
	{
		// TODO:	
		// ����������ƹ⡢�����ȵ�

		// �������
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, glm::mat4 transform)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
		shader->UploadUniformMat4("u_TransformMatrix", transform);

		RendererCommand::DrawIndexed(vertexArray);
	}
}