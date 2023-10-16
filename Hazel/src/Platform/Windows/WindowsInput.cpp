#include "WindowsInput.h"
#include "Hazel/Application.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	Input* Input::single_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto glfwwindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetKey(glfwwindow, keycode);
		return status == GLFW_PRESS || status == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto glfwwindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto status = glfwGetMouseButton(glfwwindow, button);
		return status == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto glfwwindow = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(glfwwindow, &xpos, &ypos);
		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}