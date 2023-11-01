#pragma once

#include "Hazel/Core.h"
#include "VertexArray.h"
#include "Hazel/Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"


#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Hazel
{
	class HAZEL_API RendererCommand
	{
	public:
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		
		inline static void ClearColor(const glm::vec4& color)
		{
			s_RendererAPI->ClearColor(color);
		}

		inline static void DrawIndex(const std::shared_ptr<VertexArray>& vertexArray)
		{
			vertexArray->Bind();
			s_RendererAPI->DrawElements(vertexArray);
		}

	private:
		inline static RendererAPI* Create()
		{
			switch (RendererAPI::GetAPI())
			{
			case RenderEnum::None: return nullptr;
			case RenderEnum::OpenGLAPI: return new OpenGLRendererAPI;
			}
			return nullptr;
		}
	private:
		static RendererAPI* s_RendererAPI;
	};
}