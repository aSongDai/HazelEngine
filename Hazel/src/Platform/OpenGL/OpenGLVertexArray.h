#pragma once

#include "Hazel/Renderer/VertexArray.h"	


namespace Hazel
{
	class HAZEL_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>&) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>&) override;

		virtual std::vector<std::shared_ptr<VertexBuffer>> GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}

	private:
		uint32_t m_RendererID;
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;

	};
}