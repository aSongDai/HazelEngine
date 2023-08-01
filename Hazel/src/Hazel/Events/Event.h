#pragma once

#include "Hazel/Core.h"	

#include <string>
#include <sstream>
#include <functional>

namespace Hazel
{

	// Events in Hazel are currently blocking, 
	// meaning when an event occurs 
	// it immediately gets dispatched and must be deal with right then an there.


	enum class EventType
	{
		None = 0,																	// Get the Events' type
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,		// Windows Events
		AppTick, AppUpdate, AppRender,												// App Events.
		KeyPressed, KeyReleased, KeyTyped,											// Keyboard Event
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled			// Mouse Events.
	};

	enum EventCategory
	{
		None,
		EventCategoryApplication				= BIT(0),
		EventCategoryInput						= BIT(1),
		EventCategoryKeyboard					= BIT(2),
		EventCategoryMouse						= BIT(3),
		EventCategoryMouseButton				= BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}
								// ## ���ӷ�		# �ַ�����

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;}

	class HAZEL_API Event
	{
	public :
		virtual ~Event() = default;

		bool Handled = false;												// judge the event has been deal.

		virtual EventType GetEventType() const = 0;
		virtual const char* GetEventName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetEventName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class HAZEL_API EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event):m_Event(event)
		{
		}

		// F will be deduced by the compiler
		/*template<typename T, typename F>
		bool Disptcher(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled |= func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}*/

		template<typename T>
		bool Dispatch(EventFunction<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}