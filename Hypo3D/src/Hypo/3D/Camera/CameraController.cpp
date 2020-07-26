#include "hypo3dpch.h"
#include "CameraController.h"
#include "Hypo/Window/Input.h"
#include <glm/ext/scalar_constants.inl>
#include <glm/ext/matrix_clip_space.inl>
#include <glm/ext/matrix_transform.inl>
#include <Hypo/3D/ECS/Entity.h>
#include "Hypo/3D/ECS/Components.h"

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

	FirstPersonCamera::FirstPersonCamera()
	{
		m_LastMousePos = { Input::GetMousePosition() };
	}

	void FirstPersonCamera::Update(float dt)
	{
		float cameraSpeed = 10 * dt;
		if (Input::IsKeyPressed(HYPO_KEY_W))
			Move((-cameraSpeed * GetForwardVector()));
		if (Input::IsKeyPressed(HYPO_KEY_S))
			Move((cameraSpeed * GetForwardVector()));
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
			Orientate(80 * dt, 0, 0);
		if (Input::IsKeyPressed(HYPO_KEY_DOWN))
			Orientate(-80 * dt, 0, 0);


		Vec2I mouseDelta = m_LastMousePos - Vec2I{Input::GetMousePosition()};
		m_LastMousePos = { Input::GetMousePosition() };

		float sensitivity = 10;

		Orientate(mouseDelta.y * dt * sensitivity, -mouseDelta.x * dt * sensitivity, 0);
		
	}






	void FollowCamera::Update(float dt)
	{
		auto mouseDelta = m_LastMousePos - Vec2I{Input::GetMousePosition()};
		m_LastMousePos = Vec2I{ Input::GetMousePosition() };

		if (Hypo::Input::IsMouseButtonPressed(HYPO_MOUSE_BUTTON_RIGHT)) {
			float pitchChange = mouseDelta.y * 0.1f;
			pitch -= pitchChange;
		}
		if (Hypo::Input::IsMouseButtonPressed(HYPO_MOUSE_BUTTON_RIGHT)) {
			float angleChange = mouseDelta.x * 0.3f;
			angleAroundPlayer += angleChange;
		}
		auto& targetTransform = m_Target->GetComponent<TransformComponent>()->transform;

		float theta = targetTransform.GetRotation().y * 180 / glm::pi<float>() + angleAroundPlayer;
		yaw = 180 - theta;

		float horizontalDistance = followDistance * cos(glm::radians(pitch));
		float verticalDistance = followDistance * sin(glm::radians(pitch));

		float offsetX = horizontalDistance * sin(glm::radians(theta));
		float offsetZ = horizontalDistance * cos(glm::radians(theta));

		m_Position.x = targetTransform.GetPosition().x - offsetX;
		m_Position.z = targetTransform.GetPosition().z - offsetZ;
		m_Position.y = targetTransform.GetPosition().y + verticalDistance;
	}

	void FollowCamera::UpdateMatricies()
	{
		if (m_ProjectionNeedUpdate)
		{
			float aspect = m_ViewBounds.GetWidth() / m_ViewBounds.GetHeight();
			m_ProjectionMatrix = glm::perspective(glm::radians(m_Fov), aspect, m_NearPlane, m_FarPlane);
		}
		if (m_ViewNeedUpdate)
		{
			/*m_InverseViewMatrix = glm::mat4(1);
			m_InverseViewMatrix = glm::translate(m_InverseViewMatrix, glm::vec3{ m_Position.x,m_Position.y,m_Position.z });
			m_InverseViewMatrix = glm::rotate(m_InverseViewMatrix, glm::radians(m_Orientation.x), { 1,0,0 });
			m_InverseViewMatrix = glm::rotate(m_InverseViewMatrix, glm::radians(m_Orientation.y), { 0,1,0 });
			m_InverseViewMatrix = glm::rotate(m_InverseViewMatrix, glm::radians(m_Orientation.z), { 0,0,1 });

			m_ViewMatrix = glm::inverse(m_InverseViewMatrix);
			*/
			
		}
		glm::mat4 viewMatrix = glm::mat4(1);
		viewMatrix = glm::rotate(viewMatrix, glm::radians(pitch), glm::vec3(1, 0, 0));

		viewMatrix = glm::rotate(viewMatrix, glm::radians(yaw), glm::vec3(0, 1, 0));
		glm::vec3 negativeCameraPos = glm::vec3(-m_Position.x, -m_Position.y, -m_Position.z);
		viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

		m_ViewMatrix = viewMatrix;
		if (m_ViewNeedUpdate | m_ProjectionNeedUpdate)
		{
			m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
			m_ViewNeedUpdate = false;
			m_ProjectionNeedUpdate = false;
		}

	}
}
