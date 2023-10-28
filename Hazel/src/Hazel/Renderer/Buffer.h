#pragma once
#include "Hazel/Core.h"

#include <cstdint>
#include <string>
#include <vector>

namespace Hazel
{

	enum class BufferDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t GetBufferDataTypeSize(BufferDataType type)
	{
		switch (type)
		{
		case Hazel::BufferDataType::None:			return 0;
		case Hazel::BufferDataType::Float:			return 4;
		case Hazel::BufferDataType::Float2:			return 4 * 2;
		case Hazel::BufferDataType::Float3:			return 4 * 3;
		case Hazel::BufferDataType::Float4:			return 4 * 4;
		case Hazel::BufferDataType::Mat3:			return 4 * 3 * 3;
		case Hazel::BufferDataType::Mat4:			return 4 * 4 * 4;
		case Hazel::BufferDataType::Int:			return 4;
		case Hazel::BufferDataType::Int2:			return 4 * 2;
		case Hazel::BufferDataType::Int3:			return 4 * 3;
		case Hazel::BufferDataType::Int4:			return 4 * 4;
		case Hazel::BufferDataType::Bool:			return 1;
		}
		HAZEL_CORE_ASSERT(false & "Unknown Data Type!");
		return 0;
	}

	struct ElementAttrib
	{
		std::string			Name;					// Name of element.
		BufferDataType		Type;					// The type of data in each element.
		uint32_t			Size;					// The number of components of each element.
		uint32_t			Offset;					// Offset of each element;
		bool				Normalized;

		ElementAttrib(const std::string& name,const BufferDataType& type,bool normalized=false)
			:Name(name), Type(type), Offset(0), Size(0), Normalized(normalized)
		{

		}

		inline uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Hazel::BufferDataType::None:				return 0;
			case Hazel::BufferDataType::Float:				return 1;
			case Hazel::BufferDataType::Float2:				return 2;
			case Hazel::BufferDataType::Float3:				return 3;
			case Hazel::BufferDataType::Float4:				return 4;
			case Hazel::BufferDataType::Mat3:				return 3 * 3;
			case Hazel::BufferDataType::Mat4:				return 4 * 4;
			case Hazel::BufferDataType::Int:				return 1;
			case Hazel::BufferDataType::Int2:				return 2;
			case Hazel::BufferDataType::Int3:				return 3;
			case Hazel::BufferDataType::Int4:				return 4;
			case Hazel::BufferDataType::Bool:				return 1;
			}
			HAZEL_CORE_ASSERT(false & "Unknown DataType!");
			return 0;
		}
	};

	class HAZEL_API BufferDataLayout
	{
	public:
		BufferDataLayout(){}

		// ��������
		BufferDataLayout(const std::initializer_list<ElementAttrib>& elementAttrib)
			:m_Elements(elementAttrib)
		{
			CalculateEachElementStride();
		}

		~BufferDataLayout()
		{

		}

		inline uint32_t GetStride() const { return m_ElementStride; }

		std::vector<ElementAttrib>::iterator begin() { return m_Elements.begin(); }
		std::vector<ElementAttrib>::iterator end() { return m_Elements.end(); }	
		std::vector<ElementAttrib>::const_iterator begin() const { return m_Elements.begin(); }	
		std::vector<ElementAttrib>::const_iterator end()	const { return m_Elements.end(); }
	private:
		inline void CalculateEachElementStride()
		{
			uint32_t offset = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				element.Size = GetBufferDataTypeSize(element.Type);
				offset += element.Size;
				m_ElementStride = offset;
			}
		}

	private:
		std::vector<ElementAttrib> m_Elements;
		uint32_t m_ElementStride = 0;
	};

	/*static uint32_t BufferDataTypeSize(BufferDataType type)
	{
		switch (type)
		{
		case Hazel::BufferDataType::None:			return 0;
		case Hazel::BufferDataType::Float:			return 4;
		case Hazel::BufferDataType::Float2:			return 4 * 2;
		case Hazel::BufferDataType::Float3:			return 4 * 3;
		case Hazel::BufferDataType::Float4:			return 4 * 4;
		case Hazel::BufferDataType::Mat3:			return 4 * 3 * 3;
		case Hazel::BufferDataType::Mat4:			return 4 * 4 * 4;
		case Hazel::BufferDataType::Int:			return 4;
		case Hazel::BufferDataType::Int2:			return 4 * 2;
		case Hazel::BufferDataType::Int3:			return 4 * 3;
		case Hazel::BufferDataType::Int4:			return 4 * 4;
		case Hazel::BufferDataType::Bool:			return 1;
		}
		HAZEL_CORE_ASSERT(false & "Unknown buffer data type!");
		return 0;
	}*/

	/*struct BufferElements
	{
		std::string				Name;
		BufferDataType			Type;
		uint32_t				Offset;
		uint32_t				Size;
		bool					Normalization;

		BufferElements(const std::string& name, BufferDataType type, bool normalization = false)
			:Name(name), Type(type), Offset(0), Size(BufferDataTypeSize(type)), Normalization(normalization)
		{

		}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
			case Hazel::BufferDataType::None:			return 0;
			case Hazel::BufferDataType::Float:			return 1;
			case Hazel::BufferDataType::Float2:			return 2;
			case Hazel::BufferDataType::Float3:			return 3;
			case Hazel::BufferDataType::Float4:			return 4;
			case Hazel::BufferDataType::Mat3:			return 3 * 3;
			case Hazel::BufferDataType::Mat4:			return 4 * 4;
			case Hazel::BufferDataType::Int:			return 1;
			case Hazel::BufferDataType::Int2:			return 2;
			case Hazel::BufferDataType::Int3:			return 3;
			case Hazel::BufferDataType::Int4:			return 4;
			case Hazel::BufferDataType::Bool:			return 1;
			}
			HAZEL_CORE_ASSERT(false & "Unknown DataType!");
			return 0;
		}
	};*/

	/*class BufferLayout
	{
	public:

		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElements>& elements):m_Elements(elements)
		{ 
			CalculateStrideAndOffset();
		}

		inline uint32_t GetStride() const { return m_Stride; }
		inline const std::vector<BufferElements> GetElements() const { return m_Elements; }

	public:
		std::vector<BufferElements>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElements>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElements>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElements>::const_iterator end() const { return m_Elements.end(); }
	private:
		void CalculateStrideAndOffset()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = offset;
				offset += element.Size;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElements> m_Elements;
		uint32_t m_Stride = 0;
	};*/

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetBufferDataLayout(const BufferDataLayout& layout) = 0;
		virtual BufferDataLayout GetBufferDataLayout() const = 0;


	public:
		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {};
		
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual uint32_t GetCount() const = 0;
	public:
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};
}