#pragma once

#include "Hazel/Renderer/Texture.h"

#include <string>

namespace Hazel
{
	class HAZEL_API OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override;
		virtual uint32_t GetHeight() const override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_TexturePath;
		uint32_t m_TextureID;
		uint32_t m_Width;
		uint32_t m_Height;
		
	};
}