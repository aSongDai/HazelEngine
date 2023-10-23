#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Input.h"
#include "ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"

#include <memory>


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

		// �¼�	-> ��Ҫ��dispatcher
		void OnEvent(Event& e);
		
		inline static Application& Get() { return *m_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;
		unsigned int m_VertexBuffer;
		unsigned int m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		//unsigned int m_Shader;							// ��ɫ�����ṩ�Ļ����Կ�������Ĭ���ṩһ��

	private :
		static Application* m_Instance;
	};

	Application* CreateApplication();
}