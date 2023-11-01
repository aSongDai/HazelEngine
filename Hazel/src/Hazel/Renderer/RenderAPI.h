#pragma once

#include "Hazel/Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Hazel
{
	enum class RenderEnum
	{
		None		=	0,
		OpenGLAPI	=	1,
		// DirectX	=	2,						// 后期可以根据需要相加
	};

	class RendererAPI
	{
	public:
		inline static RenderEnum GetAPI() { return s_RendererAPI; }

		virtual void Clear() = 0;
		virtual void ClearColor(const glm::vec4&) = 0;
		
		virtual void DrawElements(const std::shared_ptr<VertexArray>&) = 0;
	private:
		static RenderEnum s_RendererAPI;
	};
}