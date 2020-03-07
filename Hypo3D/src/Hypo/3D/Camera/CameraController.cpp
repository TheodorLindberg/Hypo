#include "hypo3dpch.h"
#include "CameraController.h"
#include "Hypo/Window/Input.h"

namespace Hypo
{
	void ThridPersonKeyboardCamera::Update(float dt)
	{

		float cameraSpeed = 2.5 * dt;
		if (Input::IsKeyPressed(HYPO_KEY_W))
			Move((-cameraSpeed * GetForwardVector()));
		if (Input::IsKeyPressed(HYPO_KEY_S))
			Move((cameraSpeed * GetForwardVector())	);
		if (Input::IsKeyPressed(HYPO_KEY_A))
			Move(glm::normalize(glm::cross(GetForwardVector(), GetUpVector())) * cameraSpeed);
		if (Input::IsKeyPressed(HYPO_KEY_D))
			Move(glm::normalize(glm::cross(GetForwardVector(), GetUpVector())) * -cameraSpeed);
		if (Input::IsKeyPressed(HYPO_KEY_SPACE))
			Move((cameraSpeed * GetUpVector()));
		if (Input::IsKeyPressed(HYPO_KEY_LEFT_SHIFT))
			Move(-(cameraSpeed * GetUpVector()));

		if (Input::IsKeyPressed(HYPO_KEY_LEFT))
			Orientate(0, -80 * dt, 0);
		if (Input::IsKeyPressed(HYPO_KEY_RIGHT))
			Orientate(0, 80 * dt, 0);
		if (Input::IsKeyPressed(HYPO_KEY_UP))
			Orientate( 80 * dt, 0,0);
		if (Input::IsKeyPressed(HYPO_KEY_DOWN))
			Orientate(-80 * dt,0, 0);
	}
}
