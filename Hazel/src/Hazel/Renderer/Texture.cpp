#include "Texture.h"

#include "Hazel/Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::OpenGLAPI: return std::make_shared<OpenGLTexture2D>(path);
		case RenderEnum::None:		HAZEL_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		default:
			break;
		}
		HAZEL_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}