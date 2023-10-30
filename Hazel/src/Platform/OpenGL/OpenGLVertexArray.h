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
		std::shared_ptr<VertexBuffer> m_VertexBuffer;						// 基本上一个vertexarray，绑定一个vertexbuffer， 然后绑定多个layout， 我觉着应该不需要vector
		std::shared_ptr<IndexBuffer> m_IndexBuffer;							// 渲染的点按什么顺序来渲染s
	};
}