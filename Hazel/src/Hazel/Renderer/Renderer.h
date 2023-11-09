#pragma once
#include "RendererCommand.h"
#include "Hazel/Core.h"
#include "Hazel/Camera.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/RenderAPI.h"
#include "Hazel/Renderer/Shader.h"


#include <glm/glm.hpp>

namespace Hazel
{
	struct SceneData
	{
		glm::mat4				ViewProjectionMatrix;
	};

	class HAZEL_API Renderer
	{
	public:
		static void BeginScene(const Camera&);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>&, const std::shared_ptr<Shader>&);

	private:
		static SceneData* s_SceneData;
	};
}