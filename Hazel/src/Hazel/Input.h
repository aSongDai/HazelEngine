#pragma once

#include "Hazel/Core.h"

#include <utility>

namespace Hazel
{
	
	class HAZEL_API Input
	{
	public:
		// key
		inline static bool IsKeyPressed(int keycode) { return single_Instance->IsKeyPressedImpl(keycode); }
		// Mouse
		inline static bool IsMouseButtonPressed(int button) { return single_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return single_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return single_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return single_Instance->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float>	GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* single_Instance;
	};
}