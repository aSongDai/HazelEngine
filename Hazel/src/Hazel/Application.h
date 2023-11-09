#pragma once

#include "Core.h"
#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Input.h"
#include "Camera.h"
#include "ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"
#include "Hazel/Renderer/Buffer.h"
#include "Hazel/Renderer/VertexArray.h"

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

		// 事件	-> 主要是 dispatcher
		void OnEvent(Event& e);
		
		inline static Application& Get() { return *m_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		// Graphic						可以在初始化结束后将 buffer 指针销毁
		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		Camera* m_Camera;

	private :
		static Application* m_Instance;
	};

	Application* CreateApplication();
}