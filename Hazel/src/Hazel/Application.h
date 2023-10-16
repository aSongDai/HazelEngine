#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Input.h"

namespace Hazel
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Hazel::Application::x, this, std::placeholders::_1)


	class HAZEL_API Application
	{
	public :
		Application();
		virtual ~Application();

		void Run();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		// 事件	-> 主要是dispatcher
		void OnEvent(Event& e);
		
		inline static Application& Get() { return *m_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private :
		static Application* m_Instance;
	};

	Application* CreateApplication();
}