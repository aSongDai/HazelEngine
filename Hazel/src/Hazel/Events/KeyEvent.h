#pragma once

#include "Hazel/Events/Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:									// 这里设置成受保护的构造，原因是这个类不能被出了它的子类之外的任何对象所构造出来，
												// 只有当键盘输入发生时，才能被子类调用，进行该类的创建，所以这个类只有一个code对应键位一个成员变量
		KeyEvent(int keyCode):
			m_KeyCode(keyCode){}

		int m_KeyCode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount):
			KeyEvent(keycode), m_RepeatCount(repeatCount){}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << "(" << m_RepeatCount << " repeats)";
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_RepeatCount;
	};

	class HAZEL_API KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode):KeyEvent(keycode){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}