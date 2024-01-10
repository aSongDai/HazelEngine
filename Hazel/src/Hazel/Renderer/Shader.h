#pragma once
#include "Hazel/Core.h"	

#include <string>
#include <unordered_map>

namespace Hazel
{


	class HAZEL_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual const std::string& GetName() const = 0;
		
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		static Ref<Shader> Create(const std::string& filepath);
	};



	/*
		ShaderLibrary
	*/
	class HAZEL_API ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> GetShader(const std::string&);
		Ref<Shader> LoadShader(const std::string& filepath);						// auto name
		Ref<Shader> LoadShader(const std::string& name, const std::string&);		// setting name

		bool Exist(const std::string&) const;

	private:
		std::unordered_map<std::string, Ref<Shader>> m_ShaderLibrary;
	};
}