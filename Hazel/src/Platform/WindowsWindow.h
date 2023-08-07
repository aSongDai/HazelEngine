#pragma once

#include "GLFW/glfw3.h"
#include "Hazel/Window.h"
#include "Hazel/HazelLog.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"


namespace Hazel
{

	class HAZEL_API WindowsWindow :public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFunction& callback) override
		{
			m_Data.EventCallback = callback;
		}
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();


	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFunction EventCallback;
		};
		WindowData m_Data;
	};
}