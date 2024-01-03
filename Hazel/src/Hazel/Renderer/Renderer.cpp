#include "Renderer.h"

#include "RendererCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		RendererCommand::Init();
	}

	void Renderer::BeginScene(OrthogonalCamera& camera)
	{
		// TODO:	
		// 设置相机、灯光、环境等等

		// 设置相机
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, glm::mat4 transform)
	{

		shader->Bind();
		// get the data(viewProjectionMatrix) from the 'Scene Data' and upload to the shader.
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("u_ViewProjectionMatrix", s_SceneData->ViewProjectionMatrix);
		// get the data(transform) from the main function and upload it to the shader.
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMatrix4("u_TransformMatrix", transform);

		RendererCommand::DrawIndexed(vertexArray);
	}
}