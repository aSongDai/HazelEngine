#pragma once
#include "Hazel/Core.h"	

#include <glm/glm.hpp>
#include <string>

namespace Hazel
{

	class HAZEL_API Shader
	{
	public:
		Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource);
		~Shader();

		void Bind() const;
		void UnBind() const;

		void UploadUniformMatrix(const std::string&, const glm::mat4&);
	private:
		uint32_t m_RendererID;
	};
}