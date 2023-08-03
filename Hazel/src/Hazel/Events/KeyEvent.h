#pragma once

#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent:public Event
	{
	public:
		inline unsigned int GetKeyCode() { return m_keyCode; }

		EVENT_CATEGORY(EventCategoryKeyBoard)

	protected:
		KeyEvent(unsigned int  keycode):m_keyCode(keycode){}

		unsigned m_keyCode;
	};

	class HAZEL_API KeyPressEvent :public KeyEvent
	{
	public:
		KeyPressEvent(unsigned keycode, unsigned repeat):KeyEvent(keycode), m_repeatCount(repeat){}

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "KeyPressEvent: " << m_keyCode << ", count:	" << m_repeatCount;
			return ss.str();
		}

		EVENT_TYPE(KeyPress)
	private:
		unsigned m_repeatCount;
	};

	class HAZEL_API KeyReleaseEvent :public KeyEvent
	{
	public:

		KeyReleaseEvent(unsigned keycode):KeyEvent(keycode){}
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleaseEvent: " << m_keyCode;
			return ss.str();
		}

		EVENT_TYPE(KeyRelease)

	};

	class HAZEL_API KeyTypeEvent : public KeyEvent
	{
	public:
		EVENT_TYPE(KeyType)

		KeyTypeEvent(unsigned keycode ):KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypeEvent: " << m_keyCode;
			return ss.str();
		}
	};
		
}