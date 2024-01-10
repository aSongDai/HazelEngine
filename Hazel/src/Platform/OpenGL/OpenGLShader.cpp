#include "OpenGLShader.h"


#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <fstream>

namespace Hazel
{
	static GLenum GLTypeFromString(const std::string& type)
	{
		if (type == "vertex")
		{
			return GL_VERTEX_SHADER;
		}
		else if (type == "fragment")
		{
			return GL_FRAGMENT_SHADER;
		}
		HAZEL_CORE_ASSERT(false, "Unknown Shader type!");
	}

	/*
		Constructor: 
			Using a filepath to initialize Shader.

		Args:
			Path of shader file.
	*/
	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		std::string shaderSource = ReadFile(filepath);
		const auto shaderSources = SplitShaderSource(shaderSource);
		const auto shaderIDs = CompileShader(shaderSources);
		LinkShaderProgram(shaderIDs);

		// set m_Name.			asserts/shaders/Texture.glsl	lastslash 15 lastdot 23
		auto lastSlash = filepath.find_last_of("/\\");
		auto beginName = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filepath.find_last_of('.');
		auto lengthName = lastDot == std::string::npos ? filepath.size() - beginName : lastDot - beginName;
		m_Name = filepath.substr(beginName, lengthName);
	}


	/*
		Constructor:
			Using two strings, which are the sources of shaders.
	*/
	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
		:m_Name (name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GLTypeFromString("vertex")] = vertexShaderSource;
		shaderSources[GLTypeFromString("fragment")] = fragmentShaderSource;
		const auto& shaderIDs = CompileShader(shaderSources);
		LinkShaderProgram(shaderIDs);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_ShaderProgramID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		std::string shaderSource;
		std::ifstream fin(filepath, std::ios::in | std::ios::binary);

		if (!fin.is_open())
		{
			std::cerr << "Unable to open shader file!\n" << std::endl;
			HAZEL_CORE_ASSERT(false, "Unable to open shader file, please check you file!");
		}

		// read file 
		fin.seekg(0, std::ios::end);
		shaderSource.resize(fin.tellg());
		fin.seekg(0, std::ios::beg);
		fin.read(&shaderSource[0], shaderSource.size());
		fin.close();															// close file stream.

		return shaderSource;
		
	}



	std::vector<GLint> const OpenGLShader::CompileShader(const std::unordered_map<GLenum, std::string>& shaderSources)		// 感觉可以让它返回一个 unordered_map<uint32_t>, 存放 vertexShaderID 和 fragmentShaderID, 完事儿改造一下这里
	{
		std::vector<GLint> shaderIDs;											// 可以在栈上优化这点内存
		for (const auto& [shaderType, shaderSource] : shaderSources)
		{
			GLint shaderID = glCreateShader(shaderType);
			const char* source = shaderSource.c_str();
			glShaderSource(shaderID, 1, &source, 0);
			glCompileShader(shaderID);

			int status = 0;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE)
			{
				GLint errorLength = 0;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &errorLength);

				std::vector<char> info(errorLength);
				glGetShaderInfoLog(shaderID, info.size(), &errorLength, &info[0]);

				glDeleteShader(shaderID);

				HAZEL_CORE_ERROR(info.data());
				HAZEL_CORE_ASSERT(false, "Shader compilation failure!");
				return shaderIDs;
			}

			// 编译完事儿之后需要挂载到程序上
			shaderIDs.push_back(shaderID);
		}
		return shaderIDs;
	}

	const std::unordered_map<GLenum, std::string> OpenGLShader::SplitShaderSource(const std::string& shaderSource)
	{
		std::unordered_map<GLenum, std::string> shaders;
		
		// split  --  Cherno
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = shaderSource.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = shaderSource.find_first_of("\r\n", pos);				// find #type shaderType
			HAZEL_CORE_ASSERT(eol != std::string::npos, "Unknown shader type!");
			size_t shaderTypeBegin = pos + typeTokenLength + 1;
			std::string type = shaderSource.substr(shaderTypeBegin, eol - shaderTypeBegin);
			HAZEL_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel", "Invalid shader type specified!");

			size_t nextLinePos = shaderSource.find_first_not_of("\r\n", eol);
			pos = shaderSource.find(typeToken, nextLinePos);
			shaders[GLTypeFromString(type)] = shaderSource.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? shaderSource.size() - 1 : nextLinePos));
		}
		return shaders;
	}

	void OpenGLShader::LinkShaderProgram(const std::vector<GLint>& shaderIDs)
	{
		m_ShaderProgramID = glCreateProgram();

		for (const auto id : shaderIDs)
		{
			glAttachShader(m_ShaderProgramID, id);
		}
		glLinkProgram(m_ShaderProgramID);
		int status = 0;
		glGetProgramiv(m_ShaderProgramID, GL_LINK_STATUS, &status);
		if (status == GL_FALSE)
		{
			GLint infoLength = 0;
			glGetProgramiv(m_ShaderProgramID, GL_INFO_LOG_LENGTH, &infoLength);
			
			std::vector<char> infoLog(infoLength);
			glGetProgramInfoLog(m_ShaderProgramID, infoLog.size(), &infoLength, &infoLog[0]);

			HAZEL_CORE_ERROR("Some error on Shader Program Linking!");
			HAZEL_CORE_ASSERT(false, "Linking Error!");
			return;
		}

		for (const auto id : shaderIDs)
		{
			glAttachShader(m_ShaderProgramID, id);
			glDeleteShader(id);
		}
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