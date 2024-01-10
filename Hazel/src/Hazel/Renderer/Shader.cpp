#include "Shader.h"
#include "Hazel/Renderer/RenderAPI.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexShaderRes, const std::string& fragmentShaderRes)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::OpenGLAPI:
			return std::make_shared<OpenGLShader>(name, vertexShaderRes, fragmentShaderRes);
		case RenderEnum::None:
			return nullptr;
		}
		HAZEL_CORE_TRACE("Unknown Renderer API!");
		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (RendererAPI::GetAPI())
		{
		case RenderEnum::None:			HAZEL_CORE_ASSERT(false, "Unknown RendererAPI!") return nullptr;
		case RenderEnum::OpenGLAPI:		return std::make_shared<OpenGLShader>(filepath);
		}
	}


	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		HAZEL_CORE_ASSERT(!Exist(name), "This shader has exist!");
		m_ShaderLibrary[name] = shader;
	}

	Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
	{
		HAZEL_CORE_ASSERT(Exist(name), "This shader do not exist!");
		
		return m_ShaderLibrary[name];
	}

	Ref<Shader> ShaderLibrary::LoadShader(const std::string& filepath)
	{
		Ref<Shader>& shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::LoadShader(const std::string& name, const std::string& filepath)
	{
		Ref<Shader>& shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	bool ShaderLibrary::Exist(const std::string& name) const
	{
		if (m_ShaderLibrary.find(name) != m_ShaderLibrary.end())
			return true;
		return false;
	}
}