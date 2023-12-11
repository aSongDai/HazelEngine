#include "OpenGLVertexArray.h"


#include <glad/glad.h>

namespace Hazel
{

	static GLenum BufferDataTypeToOpenGLBaseType(Hazel::BufferDataType Type)
	{
		switch (Type)
		{
		case Hazel::BufferDataType::None:		return GL_NONE;
		case Hazel::BufferDataType::Float:		return GL_FLOAT;
		case Hazel::BufferDataType::Float2:		return GL_FLOAT;
		case Hazel::BufferDataType::Float3:		return GL_FLOAT;
		case Hazel::BufferDataType::Float4:		return GL_FLOAT;
		case Hazel::BufferDataType::Mat3:		return GL_FLOAT;
		case Hazel::BufferDataType::Mat4:		return GL_FLOAT;
		case Hazel::BufferDataType::Int:		return GL_INT;
		case Hazel::BufferDataType::Int2:		return GL_INT;
		case Hazel::BufferDataType::Int3:		return GL_INT;
		case Hazel::BufferDataType::Int4:		return GL_INT;
		case Hazel::BufferDataType::Bool:		return GL_BOOL;
		}
		HAZEL_CORE_ASSERT(false, "Unknown DataType!");
		return GL_NONE;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
		glBindVertexArray(m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		HAZEL_CORE_ASSERT(vertexBuffer->GetBufferLayout().GetElements().size(), "The vertexBuffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		// Set VertexBufferLayout
		for (const auto& element : vertexBuffer->GetBufferLayout())
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				BufferDataTypeToOpenGLBaseType(element.Type),
				element.Normalization ? GL_TRUE : GL_FALSE,
				vertexBuffer->GetBufferLayout().GetStride(),
				(const void*)element.Offset);
			++index;
		}
		m_VertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		m_IndexBuffer = indexBuffer;
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();
	}

}