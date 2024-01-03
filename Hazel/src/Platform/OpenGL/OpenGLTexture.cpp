#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

//#include <iostream>
//#include <fstream>

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_TexturePath(path)								// 为啥读取不到这个 path 呢, 读取不到path是因为没有从项目根路径出发， 需要从项目的根路径出发，写出的相对路径才能够被访问到
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
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);						// 这里上传纹理出错道德原因是 通道的数量问题， 在上传的时候要注意这里到底是 ‘rgb’ or ‘rgba’ 否则通道数量对不上就会出现乱码问题

		// if you want upload rgba, you should set right channels.
		HAZEL_CORE_ASSERT(data, stbi_failure_reason());

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		HAZEL_CORE_ASSERT(internalFormat && dataFormat, "Formate not supported!");

		m_Width = width;
		m_Height = height;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
		
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