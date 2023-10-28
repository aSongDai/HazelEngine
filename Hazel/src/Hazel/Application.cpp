//#include "Hazelpch.h"
//#include "Events/ApplicationEvent.h"
#include "Application.h"
#include "HazelLog.h"

#include <glad/glad.h>

Hazel::Application* Hazel::Application::m_Instance = nullptr;

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
	HAZEL_CORE_ASSERT(false & "Unknown DataType!");
	return GL_NONE;
}

Hazel::Application::Application()
{
	HAZEL_CORE_ASSERT(!m_Instance, "Application already exists!");
	m_Instance = this;
	m_Window =std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
	


	// VertexArray
	glCreateVertexArrays(1, &m_VertexArray);
	glBindVertexArray(m_VertexArray);

	float vertices[3 * 3] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	

	/*{
		BufferLayout layout = {
			{"a_Position", BufferDataType::Float3}
		};
		m_VertexBuffer->SetBufferLayout(layout);
	}*/
	// Set VertexBufferLayout	
	// 布局需要的信息：
	/*
		1. Name
		2. 数据类型	----> 从数据类型需要知道类型的长度
		3. 给的数据需要包含几个点
		4. 每个点中包含几个数据
		5. 两个数据点中间的偏移		可以通过数据类型来计算，要考虑到一个缓冲区的所有数据类型（比如Position和Color）
		6. 
	*/
	
	{
		BufferDataLayout layout = {
			{"a_Position", BufferDataType::Float3}
		};
		m_VertexBuffer->SetBufferDataLayout(layout);
	}

	uint32_t index = 0;
	for (const auto& element : m_VertexBuffer->GetBufferDataLayout())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 
			element.GetComponentCount(),
			BufferDataTypeToOpenGLBaseType(element.Type),
			element.Normalized?GL_TRUE:GL_FALSE,
			m_VertexBuffer->GetBufferDataLayout().GetStride(),
			(const void*)element.Offset);
		++index;
	}



	/*uint32_t index = 0;
	for (const auto& element : m_VertexBuffer->GetBufferLayout())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, 
			element.GetComponentCount(), 
			BufferDataTypeToOpenGLBaseType(element.Type), 
			element.Normalization ? GL_TRUE:GL_FALSE, 
			m_VertexBuffer->GetBufferLayout().GetStride(),
			(const void*)element.Offset);
		++index;
	}*/

	uint32_t indices[3] = {0,1,2};
	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));

	const std::string vertexShaderResource = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;
		out vec3 v_Position;
		void main()
		{
			v_Position  = a_Position;
			gl_Position = vec4(a_Position, 1.0);
		}
	)";
	const std::string fragmentShaderResource = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
		in vec3 v_Position;
		void main(){
			color = vec4(v_Position + 0.5, 1.0);
		}
	)";

	// Shader
	m_Shader.reset(new Shader(vertexShaderResource, fragmentShaderResource));
}

void Hazel::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

	//HAZEL_CORE_TRACE("{0}", e);s

	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.GetHandled())
			break;
	}
}


Hazel::Application::~Application()
{
}

void Hazel::Application::Run()
{
	while (m_Running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.45f, 0.55f, 0.60f, 1.00f);

		m_Shader->Bind();
		glBindVertexArray(m_VertexArray);
		glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

		for (auto layer : m_LayerStack)
		{
			layer->OnUpdate();
		}
		m_ImGuiLayer->Begin();
		for (auto layer : m_LayerStack)
			layer->OnImGuiRender();
		m_ImGuiLayer->End();

		m_Window->OnUpdate();

	}
}

bool Hazel::Application::OnWindowClose(Hazel::WindowCloseEvent& event)
{
	m_Running = false;
	return true;
}


void Hazel::Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
	layer->OnAttach();
}

void Hazel::Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
	overlay->OnAttach();
}