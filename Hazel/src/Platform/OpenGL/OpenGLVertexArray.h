#pragma once
#include "Hazel/Renderer/VertexArray.h"

namespace Hazel
{
	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual bool AddVertexBuffer(const std::shared_ptr<VertexBuffer>&) override;
		virtual bool SetIndexBuffer(const std::shared_ptr<IndexBuffer>&) override;

		virtual std::shared_ptr<VertexBuffer> GetVertexBuffer() const override { return m_VertexBuffer; }
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override { return m_IndexBuffer; }	
	private:
		uint32_t m_RendererID;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;						// ������һ��vertexarray����һ��vertexbuffer�� Ȼ��󶨶��layout�� �Ҿ���Ӧ�ò���Ҫvector
		std::shared_ptr<IndexBuffer> m_IndexBuffer;							// ��Ⱦ�ĵ㰴ʲô˳������Ⱦs
	};
}