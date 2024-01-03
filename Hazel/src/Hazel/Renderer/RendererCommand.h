#pragma once

#include "Hazel/Core.h"
#include "Hazel/Renderer/RenderAPI.h"
#include "Hazel/Renderer/VertexArray.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Hazel
{
	class RendererCommand
	{
	public:
		// ����ļ�������������д����������

		static void Init();
		static void Clear();
		static void ClearColor(const glm::vec4&);

		static void DrawIndexed(const Ref<VertexArray>&);
	private:
		static RendererAPI* s_RendererAPI;
	};
}