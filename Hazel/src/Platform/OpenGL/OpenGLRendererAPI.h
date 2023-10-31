#pragma once

#include "Hazel/Renderer/RenderAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4&) override;
		virtual void DrawElements(const std::shared_ptr<VertexArray>&) override;
	};
}