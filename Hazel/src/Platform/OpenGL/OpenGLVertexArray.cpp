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

	bool OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		// ÏÈÅÐ¶Ï layout
		BufferDataLayout layout = vertexBuffer->GetBufferDataLayout();
		if (!layout.GetStride())
		{
			HAZEL_CORE_ASSERT(false, "There is no any layouts!");
			return false;
		}
	
		uint32_t index = 0;
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentCount(),
				BufferDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)element.Offset);
			++index;
		}
		m_VertexBuffer = vertexBuffer;
		return m_VertexBuffer == nullptr ? false : true;
	}

	bool OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		indexBuffer->Bind();
		m_IndexBuffer = indexBuffer;
		return indexBuffer == nullptr ? false : true;
	}
}