#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Hazel
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Hazel::Application::x, this, std::placeholders::_1)


	class HAZEL_API Application
	{
	public :
		Application();
		virtual ~Application();

		void Run();

		// 事件	-> 主要是dispatcher
		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	Application* CreateApplication();
}