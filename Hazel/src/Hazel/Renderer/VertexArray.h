#pragma once
#include "Hazel/Core.h"
#include "Hazel/Renderer/Buffer.h"	

#include <stdint.h>
#include <memory>
namespace Hazel
{
	class HAZEL_API VertexArray
	{
	public:
		virtual ~VertexArray() {};
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual bool AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual bool SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual std::shared_ptr<VertexBuffer> GetVertexBuffer() const = 0;
		virtual std::shared_ptr<IndexBuffer> GetIndexBuffer() const = 0;
	public:
		static VertexArray* Create();
	};
}