#pragma once
#include "Hazel/Core.h"

namespace Hazel
{
	class HAZEL_API TimeStep
	{
	public:
		TimeStep(float time = 0.0f)
			:m_Time(time)
		{
		}

		operator float() { return m_Time; }

		float GetTime() const { return m_Time; }
		float GetMilliSecond() const { return m_Time * 1000.f; }
	private:
		float m_Time;
	};
}