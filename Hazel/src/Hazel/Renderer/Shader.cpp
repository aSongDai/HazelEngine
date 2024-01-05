#include "Shader.h"
#include "Hazel/Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& vertexShaderRes, const std::string& fragmentShaderRes)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::OpenGLAPI:
			return new OpenGLShader(vertexShaderRes, fragmentShaderRes);
		case RenderEnum::None:
			return nullptr;
		}
		HAZEL_CORE_TRACE("Unknown Renderer API!");
		return nullptr;
	}

	Shader* Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::None:			HAZEL_CORE_ASSERT(false, "Unknown RendererAPI!") return nullptr;
		case RenderEnum::OpenGLAPI:		return new OpenGLShader(filepath);
		}
	}
}