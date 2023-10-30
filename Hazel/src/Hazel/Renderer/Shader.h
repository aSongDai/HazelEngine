#pragma once
#include "Hazel/Core.h"	


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
	private:
		uint32_t m_RendererID;
	};
}