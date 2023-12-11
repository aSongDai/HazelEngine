#pragma once

#include "Hazel/Core.h"
#include "VertexArray.h"
#include "OrthogonalCamera.h"
#include "Shader.h"


namespace Hazel
{
	class HAZEL_API Renderer
	{
	public:
		static void BeginScene(OrthogonalCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>&, const Ref<Shader>&, glm::mat4 transform = glm::mat4(1.0f));

	private:
		struct SceneData
		{
			glm::mat4		ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}