#pragma once

#include "Hazel/Core.h"	
#include "Hazel/Layer.h"
#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"

namespace Hazel
{
	class HAZEL_API ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& event);

	private:
		// mouse
		bool OnMouseButtenPressedEvent(MouseButtonPressEvent& e);
		bool OnMouseReleasedEvent(MouseButtonReleaseEvent& e);
		bool OnMouseMoveEvent(MouseMoveEvent& e);
		bool OnMouseScrollEvent(MouseScrollEvent& e);
		
		// key
		bool OnKeyPressedEvent(KeyPressEvent& e);
		bool OnKeyReleaseEvent(KeyReleaseEvent& e);
		bool OnKeyTypedEvent(KeyTypeEvent& e);
		
		// application
		bool OnWindowResize(WindowResizeEvent& e);
	private:

		float m_Time=0.0f;
	};
}