//#include "Hazelpch.h"
//#include "Events/ApplicationEvent.h"
#include "Application.h"
#include "HazelLog.h"
#include "GLFW/glfw3.h"

// Bind the callback function macro.


Hazel::Application::Application()
{
	m_Window =std::unique_ptr<Window>(Window::Create());
	m_Window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));
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
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (auto layer : m_LayerStack)
		{
			layer->OnUpdate();
		}

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
}

void Hazel::Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
}