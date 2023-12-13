#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

//#include <iostream>
//#include <fstream>

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_TexturePath(path)								// 为啥读取不到这个 path 呢
	{

		// Test 
		//std::ifstream input(path, std::ios::binary);
		//HAZEL_CORE_ASSERT(input, "Could not open file.");

		//int widthInf, heightInf, channelsInf;
		//stbi_info(path.c_str(), &widthInf, &heightInf, &channelsInf);

		//HAZEL_CORE_INFO("Image Width: {0}", widthInf);
		//HAZEL_CORE_INFO("Image Height: {0}", heightInf);
		//HAZEL_CORE_INFO("Image channels: {0}", channelsInf);
		
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HAZEL_CORE_ASSERT(data, stbi_failure_reason());

		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, GL_RGB8, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);
		
		// free data
		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	uint32_t OpenGLTexture2D::GetWidth() const
	{
		return m_Width;
	}

	uint32_t OpenGLTexture2D::GetHeight() const
	{
		return m_Height;
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		//glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glBindTextureUnit(slot, m_TextureID);
	}
}