#pragma once
#include <string>
#include <functional>
#include <sstream>


#include "Hazel/Core.h"

namespace Hazel
{
	enum class EventType
	{
		None = 0,
		// Application Event
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// 
		AppTick, AppUpdate, AppRender,
		// Keyboard
		KeyPress, KeyRelease, KeyType,
		// Mouse， MouseButton
		MouseButtonPress, MouseButtonRelease, MouseMove, MouseScroll
	};

	enum EventCategory
	{
		None=0,
		EventCategoryApplication		= BIT(0),
		EventCategoryInput				= BIT(1),
		EventCategoryKeyBoard			= BIT(2),
		EventCategoryMouse				= BIT(3),
		EventCategoryMouseButton		= BIT(4),
	};

#define EVENT_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
							virtual EventType GetEventType() const override {return GetStaticType();}\
							virtual const char* GetEventName() const override {return #type;}
#define EVENT_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}




	class HAZEL_API Event
	{
		friend class EventDispatcher;
		friend std::ostream& operator<<(std::ostream&, const Event&);
	public:
		virtual ~Event() = default;

		virtual const char* GetEventName() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetEventName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;								// 判断该事件是否被处理，如果没有需要转发，如果处理过了就跳过

	};

	class HAZEL_API EventDispatcher
	{
		template<typename T>
		using EventFunction = std::is_function<bool(T&)>;
	public:
		EventDispatcher(Event& event) :m_Event(event) {}

		// 转发
		template<typename T>
		bool Dispatch(EventFunction<T> function)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = function(*(T*)&m_Event);
				return true;
			}
			return false;
		}


	private:
		Event& m_Event;
	};

	std::ostream& operator<<(std::ostream& os,const Event& e)
	{
		return os << e.ToString();
	}
}