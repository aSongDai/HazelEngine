#pragma once

#include "Hazel/Renderer/RenderAPI.h"

namespace Hazel
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void Clear() override;

		virtual void SetViewPort(uint32_t, uint32_t, uint32_t, uint32_t) override;
		virtual void SetClearColor(const glm::vec4&) override;
		virtual void DrawElements(const Ref<VertexArray>&) override;
	};
}