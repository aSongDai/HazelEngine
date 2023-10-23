#include "Shader.h"	
#include "Hazel/HazelLog.h"

#include "glad/glad.h"

#include <vector>

namespace Hazel
{
	Shader::Shader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{

		// create a vertex shader
		GLint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		// shader resource 
		const char* vertexSource = vertexShaderSource.c_str();
		glShaderSource(vertexShader, 1, &vertexSource, 0);
		// compile shader
		glCompileShader(vertexShader);

		// judge compile true or false
		GLint is_Compiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &is_Compiled);

		if (is_Compiled == GL_FALSE)
		{
			// 显示编译失败的原因
			GLint infoLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLength);

			std::vector<GLchar> infoLog(infoLength);
			glGetShaderInfoLog(vertexShader, sizeof(infoLog), &infoLength, &infoLog[0]);

			// delete the vertex shader
			glDeleteShader(vertexShader);

			// compiled failure info.
			HAZEL_CORE_ERROR("Vertex shader compilation failure!");
			HAZEL_CORE_ERROR("{0}", infoLog.data());

			return;
		}


		GLint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentSource = fragmentShaderSource.c_str();
		glShaderSource(fragmentShader, 1, &fragmentSource, 0);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &is_Compiled);
		if (is_Compiled == GL_FALSE)
		{
			GLint infoLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLength);
			std::vector<GLchar> infoLog(infoLength);
			glGetShaderInfoLog(fragmentShader, infoLength, &infoLength, &infoLog[0]);
			glDeleteShader(fragmentShader);
			HAZEL_CORE_ASSERT(false, "Fragment shader compilation failure!");
			HAZEL_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		// 到这里顶点和片元着色器都编译成功了， 需要创建一个程序绑定这两个着色器
		m_RendererID = glCreateProgram();
		//GLint program = glCreateProgram();
		GLint program = m_RendererID;
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);

		GLint isLink = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLink);
		if (isLink == GL_FALSE)
		{
			GLint infoLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
			std::vector<GLchar> infoLog(infoLength);
			glGetProgramInfoLog(program, infoLength, &infoLength, &infoLog[0]);
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HAZEL_CORE_ASSERT(false, "Program link failure!");
			HAZEL_CORE_ERROR("{0}", infoLog.data());
			return;
		}

		// 链接完成之后就不需要顶点和片元着色器了
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);

	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::UnBind() const 
	{
		glUseProgram(0);
	}
}