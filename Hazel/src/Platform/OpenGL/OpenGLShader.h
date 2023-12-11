#pragma once
#include "Hazel/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Hazel
{
	class HAZEL_API OpenGLShader : public Shader
	{
	public:
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
		uint32_t m_ShaderProgramID;
	};
}