#pragma once

#include "Hazel/Events/Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:									// �������ó��ܱ����Ĺ��죬ԭ��������಻�ܱ�������������֮����κζ��������������
												// ֻ�е��������뷢��ʱ�����ܱ�������ã����и���Ĵ��������������ֻ��һ��code��Ӧ��λһ����Ա����
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