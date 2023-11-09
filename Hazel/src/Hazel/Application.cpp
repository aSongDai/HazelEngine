//#include "Hazelpch.h"
//#include "Events/ApplicationEvent.h"
#include "Application.h"
#include "HazelLog.h"
#include "Hazel/Renderer/RendererCommand.h"
#include "Hazel/Renderer/Renderer.h"

#include <glm/glm.hpp>

Hazel::Application* Hazel::Application::m_Instance = nullptr;


Hazel::Application::Application()
	:m_Camera(-1.6f, 1.6f, 0.9f, -0.9f)
{
	HAZEL_CORE_ASSERT(!m_Instance, "Application already exists!");
	m_Instance = this;
	m_Window =std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
	

	m_VertexArray.reset(VertexArray::Create());

	float vertices[] = {
		-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
	};
	m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

	BufferLayout layout = {
		{"a_Position", BufferDataType::Float3},
		{"a_Color", BufferDataType::Float4}
	};
	m_VertexBuffer->SetBufferLayout(layout);
	m_VertexArray->AddVertexBuffer(m_VertexBuffer);
	

	uint32_t indices[3] = {0,1,2};
	m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
	m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	const std::string vertexShaderResource = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;
		layout (location = 1) in vec4 a_Color;

		uniform mat4 u_ViewProjectionMatrix;		

		out vec3 v_Position;
		out vec4 v_Color;
		void main()
		{
			v_Position  = a_Position;
			v_Color = a_Color;
			gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
		}
	)";
	const std::string fragmentShaderResource = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
		in vec4 v_Color;
		in vec3 v_Position;
		void main(){
			color = vec4(v_Position + 0.5, 1.0);
			color = v_Color;
		}
	)";
	// Shader
	m_Shader.reset(new Shader(vertexShaderResource, fragmentShaderResource));

	// Square Render
	m_SquareVertexArray.reset(VertexArray::Create());
	m_SquareVertexArray->Bind();
	float square_vertices[] = {
		-0.6f, -0.6f, 0.0f, 
		 0.6f, -0.6f, 0.0f, 
		 0.6f,  0.6f, 0.0f,
		-0.6f,  0.6f, 0.0f
	};
	BufferLayout square_layout =
	{
		{"a_Position", BufferDataType::Float3}
	};
	std::shared_ptr<VertexBuffer> m_SquareVertexBuffer;
	m_SquareVertexBuffer.reset(VertexBuffer::Create(square_vertices, sizeof(square_vertices)));
	m_SquareVertexBuffer->SetBufferLayout(square_layout);
	m_SquareVertexArray->AddVertexBuffer(m_SquareVertexBuffer);
	uint32_t square_indices[] = {
		0,1,2, 2,3,0
	};
	std::shared_ptr<IndexBuffer> m_SquareIndexBuffer;
	m_SquareIndexBuffer.reset(IndexBuffer::Create(square_indices, sizeof(square_indices)/sizeof(uint32_t)));
	m_SquareVertexArray->SetIndexBuffer(m_SquareIndexBuffer);

	std::string squareVertexShaderSrc = R"(
		#version 330 core
		layout (location = 0) in vec3 a_Position;

		uniform mat4 u_ViewProjectionMatrix;
		void main()
		{
			gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
		}
	)";
	std::string squareFragmentShaderSrc = R"(
		#version 330 core
		layout (location = 0) out vec4 color;
		void main()
		{
			color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
		} 
	)";

	m_SquareShader.reset(new Shader(squareVertexShaderSrc, squareFragmentShaderSrc));


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

		RendererCommand::Clear();
		RendererCommand::ClearColor({ 0.45f, 0.55f, 0.60f, 1.00f });

		m_Camera.SetPosition({ 1.0f, 0.5f, 0.0f });
		m_Camera.SetRotation(45.0f);
		Renderer::BeginScene(m_Camera);

		Renderer::Submit(m_SquareVertexArray, m_SquareShader); 
		Renderer::Submit(m_VertexArray, m_Shader);

		Renderer::EndScene();
		

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