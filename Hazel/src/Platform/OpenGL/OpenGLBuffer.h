#pragma once
#include "Hazel/Renderer/Buffer.h"	

namespace Hazel
{

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float*, uint32_t);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual BufferLayout GetBufferLayout() const override
		{
			return m_BufferLayout;
		}
		virtual void SetBufferLayout(const BufferLayout& layout) override
		{
			m_BufferLayout = layout;
		}
	private:
		uint32_t m_RendererID;
		BufferLayout m_BufferLayout;
	};


	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t*, uint32_t);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual uint32_t GetCount() const override;

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}