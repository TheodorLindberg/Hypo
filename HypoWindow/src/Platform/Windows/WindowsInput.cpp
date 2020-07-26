#include "windowpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Hypo/Window/Window.h"

namespace Hypo {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Window::GetActiveWindow()->GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Window::GetActiveWindow()->GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	Vec2F WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Window::GetActiveWindow()->GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float WindowsInput::GetMouseXImpl()
	{
		return GetMousePositionImpl().x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		return GetMousePositionImpl().y;
	}

}
