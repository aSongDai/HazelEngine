#pragma once


// 		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
// 		AppTick, AppUpdate, AppRender,

#include "Event.h"

namespace Hazel
{
	class HAZEL_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width,int height):m_width(width),m_height(height){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: Width: " << m_width << ", Height: " << m_height;
			return ss.str();
		}

		inline unsigned GetWidth() { return m_width; }
		inline unsigned GetHeight() { return m_height; }

		EVENT_TYPE(WindowResize)
		EVENT_CATEGORY(EventCategoryApplication)



	private:
		int m_width, m_height;
	};

	class HAZEL_API WindowCloseEvent:public Event
	{
	public:
		WindowCloseEvent(){}

		EVENT_TYPE(WindowClose)
		EVENT_CATEGORY(EventCategoryApplication)

	};

	class HAZEL_API WindowFocusEvent :public Event
	{
	public:
		WindowFocusEvent(){}

		EVENT_TYPE(WindowFocus)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API WindowLostFocusEvent :public Event
	{
	public :
		WindowLostFocusEvent() = default;

		EVENT_TYPE(WindowLostFocus)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API WindowMoveEvent :public Event
	{
	public:
		WindowMoveEvent() = default;

		EVENT_TYPE(WindowMoved)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppTickEvent :public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_TYPE(AppTick)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppUpdateEvent :public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_TYPE(AppUpdate)
		EVENT_CATEGORY(EventCategoryApplication)

	};

	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_TYPE(AppRender)
		EVENT_CATEGORY(EventCategoryApplication)
	};
}