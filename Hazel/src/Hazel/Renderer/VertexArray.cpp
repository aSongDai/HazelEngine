#include "VertexArray.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderEnum::None:			HAZEL_CORE_ASSERT(false, "Please Set a RenderAPI!"); return nullptr;
		case RenderEnum::OpenGLAPI:		return new OpenGLVertexArray();
		}
		HAZEL_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}