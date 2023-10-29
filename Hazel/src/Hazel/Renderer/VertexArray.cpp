#include "VertexArray.h"	
#include "Hazel/Renderer/RenderAPI.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderEnum::None:				return nullptr;
		case RenderEnum::OpenGLAPI:			return new OpenGLVertexArray();
		}
		HAZEL_CORE_ASSERT(false & "Unknown RendererAPI!");
		return nullptr;
	}
}