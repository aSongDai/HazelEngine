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

		virtual BufferDataLayout GetBufferDataLayout() const override
		{
			return m_Layout;
		}
		virtual void SetBufferDataLayout(const BufferDataLayout& layout) override
		{
			m_Layout = layout;
		}
	private:
		uint32_t m_RendererID;
		BufferDataLayout m_Layout;
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