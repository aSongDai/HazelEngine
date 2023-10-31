#pragma once
#include "VertexArray.h"

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
		virtual void Clear() = 0;
		virtual void SetClearColor(const glm::vec4&) = 0;

		virtual void DrawElements(const std::shared_ptr<VertexArray>&) = 0;

		inline static RenderEnum GetAPI() { return s_RendererAPI; }
	private:
		static RenderEnum s_RendererAPI;
	};
}