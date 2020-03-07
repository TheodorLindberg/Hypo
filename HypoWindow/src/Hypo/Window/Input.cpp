#include "windowpch.h"
#include "Hypo/Window/Input.h"

namespace Hypo
{

	bool Input::IsKeyPressed(int keycode)
	{
		return s_Instance->IsKeyPressedImpl(keycode);
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		return s_Instance->IsMouseButtonPressedImpl(button);
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		return s_Instance->GetMousePositionImpl();
	}

	float Input::GetMouseX()
	{
		return s_Instance->GetMouseXImpl();
	}

	float Input::GetMouseY()
	{
		return s_Instance->GetMouseYImpl();
	}
}
