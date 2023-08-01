#pragma once


#include "Hazel/Events/Event.h"

namespace Hazel
{
	class HAZEL_API MouseEvent:public Event
	{
	public:
		inline int GetMouseX() { return m_MouseX; }
		inline int GetMouseY() { return m_MouseY; }
	protected:
		MouseEvent(int x, int y) :m_MouseX(x), m_MouseY(y) {}

		int m_MouseX, m_MouseY;
	};

	class HAZEL_API MouseMoveEvent :public MouseEvent
	{
	public:
		MouseMoveEvent(int x, int y):MouseEvent(x, y){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoveEvent: " << m_MouseX << "," << m_MouseY;
			ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	};

	class HAZEL_API MouseScrolledEvent :public MouseEvent
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset):m_OffsetX(xOffset), m_OffsetY(yOffset) {}

		inline float GetXOffset() const { return m_OffsetX; }
		inline float GetYOffset() const { return m_OffsetY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_OffsetX << "," << m_OffsetY;
			ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_OffsetX, m_OffsetY;
	};

	class HAZEL_API MouseButtonEvent :public Event
	{
	public:
		inline int GetMouseButton() const { return m_MouseButton; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)
	protected:
		MouseButtonEvent(int mouseButton):m_MouseButton(mouseButton){}

		int m_MouseButton;
	};

	class MouseButtonPressedEvent :public MouseButtonEvent
	{
	public :
		MouseButtonPressedEvent(int mouseButton):MouseButtonEvent(mouseButton){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_MouseButton;
			ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button):MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_MouseButton;
			ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}