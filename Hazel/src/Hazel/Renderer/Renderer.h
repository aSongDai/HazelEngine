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

		static void Submit(const std::shared_ptr<VertexArray>&, const std::shared_ptr<Shader>&);

	private:
		struct SceneData
		{
			glm::mat4		ViewProjectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}