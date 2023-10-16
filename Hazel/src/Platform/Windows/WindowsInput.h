#pragma once

#include "Hazel/Input.h"	


namespace Hazel
{
	class HAZEL_API WindowsInput :public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int) override;
		virtual bool IsMouseButtonPressedImpl(int) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}