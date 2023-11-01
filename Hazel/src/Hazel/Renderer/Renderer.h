#pragma once
#include "Hazel/Core.h"
#include "RendererCommand.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/RenderAPI.h"

namespace Hazel
{
	class HAZEL_API Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>&);

	};
}