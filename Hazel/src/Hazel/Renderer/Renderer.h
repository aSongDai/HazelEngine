#pragma once

#include "Hazel/Core.h"
#include "VertexArray.h"
#include "OrthographicCamera.h"
#include "Shader.h"


namespace Hazel
{
	struct SceneData
	{
		glm::mat4		ViewProjectionMatrix;
	};

	class HAZEL_API Renderer
	{
	public:
		static void Init();

		static void OnWindowResize(uint32_t width, uint32_t height);

		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>&, const Ref<Shader>&, glm::mat4 transform = glm::mat4(1.0f));

	private:

		static SceneData* s_SceneData;
	};
}