//#include "Hazelpch.h"
//#include "Events/ApplicationEvent.h"
#include "Application.h"
#include "HazelLog.h"
#include "Hazel/Renderer/RendererCommand.h"
#include "Hazel/Renderer/Renderer.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

Hazel::Application* Hazel::Application::m_Instance = nullptr;


Hazel::Application::Application()
{
	HAZEL_CORE_ASSERT(!m_Instance, "Application already exists!");
	m_Instance = this;
	m_Window =std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(HAZEL_BIND_EVENT_FUNCTION(Hazel::Application::OnEvent));
	m_Window->SetVSync(false);

	Renderer::Init();

	m_ImGuiLayer = new ImGuiLayer();
	PushOverlay(m_ImGuiLayer);

}

void Hazel::Application::OnEvent(Event& e)
{
	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(HAZEL_BIND_EVENT_FUNCTION(Hazel::Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(HAZEL_BIND_EVENT_FUNCTION(Hazel::Application::OnWindowResize));

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
		float time = (float)glfwGetTime();						// Platform::GetTime();
		TimeStep timeStep(time - m_LastFrameTime);
		m_LastFrameTime = time;
		
		if (!m_Minimize) {
			for (auto layer : m_LayerStack)
			{
				layer->OnUpdate(timeStep);
			}
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

bool Hazel::Application::OnWindowResize(Hazel::WindowResizeEvent& event)
{

	if (event.GetWidth() == 0 || event.GetHeight() == 0)
	{
		m_Minimize = true;
		return false;
	}

	m_Minimize = false;

	Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

	return false;
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