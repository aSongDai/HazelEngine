#pragma once
#include "Hazel/Core.h"	

#include <string>

namespace Hazel
{


	class HAZEL_API Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		static Shader* Create(const std::string&, const std::string&);
	};
}