#pragma once
#include "Hazel/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <unordered_map>

namespace Hazel
{
	class HAZEL_API OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		void UploadUniformMatrix4(const std::string&, const glm::mat4&) const;

		// TODO:
		// Consider these functions will be used to do things.
		void UploadUniformInt(const std::string&, const int);
		void UploadUniformFloat(const std::string&, const float);
		void UploadUniformFloat2(const std::string&, const glm::vec2&);
		void UploadUniformFloat3(const std::string&, const glm::vec3&);
		void UploadUniformFloat4(const std::string&, const glm::vec4&);

	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> const SplitShaderSource(const std::string&);
		std::vector<GLint> const CompileShader(const std::unordered_map<GLenum, std::string>& shaderSources);
		void LinkShaderProgram(const std::vector<GLint>&);

	private:
		int m_ShaderProgramID;
	};
}