//#include "Hazelpch.h"
//#include "Events/ApplicationEvent.h"
#include "Application.h"
#include "HazelLog.h"
#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/OrthoGraphicCamera.h"


#include <glad/glad.h>

Hazel::Application* Hazel::Application::m_Instance = nullptr;


Hazel::Application::Application()
	:m_Camera(new OrthoGraphicCamera(-3.2f, 3.2f, -1.8f, 1.8f))					// 这里可以使用判断来选择不同类型的相机， 比如透视相机， 这些相机都是继承自Camera类
{
	HAZEL_CORE_ASSERT(!m_Instance, "Application already exists!");
	m_Instance = this;
	m_Window =std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);
	


	m_VertexArray.reset(VertexArray::Create());
	m_VertexArray->Bind();


	float vertices[] = {
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		 0.0f,  0.5f, 0.0f,	0.0f, 0.0f, 1.0f, 1.0f
	};

	std::shared_ptr<VertexBuffer> vertexBuffer;
	vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
	
	BufferDataLayout layout = {
		{"a_Position", BufferDataType::Float3},
		{"a_Color", BufferDataType::Float4}
	};
	vertexBuffer->SetBufferDataLayout(layout);
	HAZEL_CORE_ASSERT(m_VertexArray->AddVertexBuffer(vertexBuffer), "Some Error in function AddVertexBuffer!");

	

	uint32_t indices[3] = {0,1,2};
	std::shared_ptr<IndexBuffer> indexBuffer;
	indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices)/sizeof(uint32_t)));
	HAZEL_CORE_ASSERT(m_VertexArray->SetIndexBuffer(indexBuffer), "Some Error in function SetIndexBuffer!");

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
		in vec3 v_Position;
		in vec4 v_Color;
		void main(){
			color = vec4(v_Position + 0.5, 1.0);
			color = v_Color;
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
		RendererCommand::Clear();
		RendererCommand::ClearColor({ 0.45f, 0.55f, 0.60f, 1.00f });
		
		// Renderer
		Renderer::BeginScene(*m_Camera);

		m_Camera->SetPosition({ 1.0f, 0.5f, 0.0f });
		m_Camera->SetRotation(30.f);
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