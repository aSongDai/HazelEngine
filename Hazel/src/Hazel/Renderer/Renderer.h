#pragma once

#include "Hazel/Core.h"
#include "VertexArray.h"

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