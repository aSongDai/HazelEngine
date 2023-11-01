#pragma once

#include "Hazel/Renderer/RenderAPI.h"	

namespace Hazel
{
	class HAZEL_API OpenGLRendererAPI :public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void ClearColor(const glm::vec4&) override;
		virtual void DrawElements(const std::shared_ptr<VertexArray>&) override;

	};
}