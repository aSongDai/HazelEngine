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

		virtual void AddVertexBuffer(const Ref<VertexBuffer>&) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>&) override;

		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}
		virtual Ref<IndexBuffer> GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;

	};
}