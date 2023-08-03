#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API MouseMoveEvent :public Event
	{

	public:
		MouseMoveEvent(const float locx, const float locy):m_locX(locx),m_locY(locy){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_locX << ", " << m_locY;
			return ss.str();
		}

		inline float GetX() const { return m_locX; }
		inline float GetY() const { return m_locY; }

		EVENT_TYPE(MouseMove)
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_locX, m_locY;
	};

	class HAZEL_API MouseScrollEvent :public Event
	{
	public:
		MouseScrollEvent(const float xOffset, const float yOffset):m_xoffset(xOffset), m_yoffset(yOffset){}

		inline float GetXoffset() const { return m_xoffset; }
		inline float GetYoffset() const { return m_yoffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrollEvent: " << GetXoffset() << ", " << GetYoffset();
			return ss.str();
		}

		EVENT_TYPE(MouseScroll)
		EVENT_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_xoffset, m_yoffset;
	};

	class HAZEL_API MouseButtonEvent : public Event
	{
	public:
		inline unsigned GetMouseButton() { return m_button; }
		EVENT_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

	protected:
		MouseButtonEvent(const unsigned button):m_button(button){}

		unsigned m_button;
	};

	class HAZEL_API MouseButtonPressEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(unsigned button):MouseButtonEvent(button){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressEvent: " << m_button;
			return ss.str();
		}

		EVENT_TYPE(MouseButtonPress)
	};

	class MouseButtonReleaseEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(unsigned button):MouseButtonEvent(button){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleaseEvent: " << m_button;
			return ss.str();
		}
		EVENT_TYPE(MouseButtonRelease)
	};
}