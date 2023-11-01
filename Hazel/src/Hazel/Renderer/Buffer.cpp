#include "Buffer.h"
#include "RenderAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Hazel/Core.h"

namespace Hazel
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::None:
			HAZEL_CORE_ASSERT(false, "RendererAPI: None is not supported current.");
			return nullptr;
		case RenderEnum::OpenGLAPI:
			return new OpenGLVertexBuffer(vertices, size);
		}
		HAZEL_CORE_ASSERT(false, "RendererAPI: Unknown.");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::None:
			HAZEL_CORE_ASSERT(false, "RenderAPI: None is not supported current.");
			return nullptr;
		case RenderEnum::OpenGLAPI:
			return new OpenGLIndexBuffer(indices, count);
		default:
			break;
		}
		HAZEL_CORE_ASSERT(false, "RenderAPI: Unknown!");
		return nullptr;
	}
}