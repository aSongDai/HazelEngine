#include "OpenGLShader.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace Hazel
{
	OpenGLShader::OpenGLShader(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
	{
		// 有 vertexShader 源码， 编译并查看日志
		uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexShaderRes = vertexShaderSource.c_str();
		glShaderSource(vertexShaderID, 1, &vertexShaderRes, 0);
		glCompileShader(vertexShaderID);

		int vertexShaderCompileStatus = 0;
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vertexShaderCompileStatus);
		if (vertexShaderCompileStatus == GL_FALSE)
		{
			// Compile failed
			int lengthInf = 0;
			glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &lengthInf);

			std::vector<char> infoLog(lengthInf);
			glGetShaderInfoLog(vertexShaderID, sizeof(infoLog), &lengthInf, &infoLog[0]);

			// 获取玩编译信息之后， 就可以把编译失败的着色器删除掉
			glDeleteShader(vertexShaderID);

			// show message of compiling
			HAZEL_CORE_ERROR("VertexShader Compiled Failed: ");
			HAZEL_CORE_ERROR(" {0}", infoLog.data());

			return;
		}
		

		// 有 fragmentShader 源码， 编译并查看日志
		uint32_t fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentShaderRes = fragmentShaderSource.c_str();
		glShaderSource(fragmentShaderID, 1, &fragmentShaderRes, 0);
		glCompileShader(fragmentShaderID);
		int fragmentShaderCompileStatus = 0;
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fragmentShaderCompileStatus);
		if (fragmentShaderCompileStatus == GL_FALSE)
		{
			// compile failed
			int lengthInf = 0;
			glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &lengthInf);

			std::vector<char> infoLog(lengthInf);
			glGetShaderInfoLog(fragmentShaderID, sizeof(infoLog), &lengthInf, &infoLog[0]);

			glDeleteShader(fragmentShaderID);

			HAZEL_CORE_ERROR("Fragment Shader Compile Failed: ");
			HAZEL_CORE_ERROR(" {0}", infoLog.data());

			return;
		}

		// 创建 shaderProgram 并添加 vertexShader 和 fragmentShader
		m_ShaderProgramID = glCreateProgram();
		glAttachShader(m_ShaderProgramID, vertexShaderID);
		glAttachShader(m_ShaderProgramID, fragmentShaderID);
		
		// check link status
		glLinkProgram(m_ShaderProgramID);
		GLint shaderProgramLinkStatus = 0;
		glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &shaderProgramLinkStatus);
		if (shaderProgramLinkStatus == GL_FALSE)
		{
			// link failed 
			GLint lengthInf = 0;
			glGetProgramiv(m_ShaderProgramID, GL_INFO_LOG_LENGTH, &lengthInf);

			std::vector<char> infoLog(lengthInf);
			glGetProgramInfoLog(m_ShaderProgramID, sizeof(infoLog), &lengthInf, &infoLog[0]);

			HAZEL_CORE_ERROR("Shader Program Link Failed: ");
			HAZEL_CORE_ERROR(" {0}", infoLog.data());
			return;
		}
		glDetachShader(m_ShaderProgramID, vertexShaderID);
		glDetachShader(m_ShaderProgramID, fragmentShaderID);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgramID);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(m_ShaderProgramID);
	}
	
	void OpenGLShader::UnBind() const
	{
		glDeleteProgram(0);
	}

	void OpenGLShader::UploadUniformMatrix4(const std::string& uniformName, const glm::mat4& matrix) const
	{
		const char* name = uniformName.c_str();
		GLint location = glGetUniformLocation(m_ShaderProgramID, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	// TODO:
	void OpenGLShader::UploadUniformInt(const std::string& uniformName, const int value)
	{
		const char* name = uniformName.c_str();
		GLint location = glGetUniformLocation(m_ShaderProgramID, name);
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& uniformName, const float value)
	{
		const char* name = uniformName.c_str();
		GLint location = glGetUniformLocation(m_ShaderProgramID, name);
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& uniformName, const glm::vec2& value)
	{
		const char* name = uniformName.c_str();
		GLint location = glGetUniformLocation(m_ShaderProgramID, name);
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& uniformName, const glm::vec3& value)
	{
		const char* name = uniformName.c_str();
		GLint location = glGetUniformLocation(m_ShaderProgramID, name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& uniformName, const glm::vec4& value)
	{
		const char* name = uniformName.c_str();
		GLint location = glGetUniformLocation(m_ShaderProgramID, name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
}