#pragma once

#include "Hazel/Core.h"
#include "Hazel/Renderer/Buffer.h"

#include <memory>

namespace Hazel
{

	class HAZEL_API VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;
		
		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;


		virtual std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
		virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;
		static VertexArray* Create();
	};
}