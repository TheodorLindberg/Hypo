#include "hypo3dpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>

namespace Hypo
{
	void OrthographicCamera::SetViewRect(float top, float bottom, float left, float right)
	{
		m_ViewBounds = { left,right,top,bottom };
		m_ProjectionNeedUpdate = true;
	}

	void OrthographicCamera::SetViewRect(RectF rect)
	{
		m_ViewBounds = rect;
		m_ProjectionNeedUpdate = true;
	}

	const glm::mat4& OrthographicCamera::GetViewMatrix()
	{
		UpdateMatricies();
		return m_ViewMatrix;
	}

	const glm::mat4& OrthographicCamera::GetInverseViewMatrix()
	{
		UpdateMatricies();
		return m_InverseViewMatrix;
	}

	const glm::mat4& OrthographicCamera::GetProjectionMatrix()
	{
		UpdateMatricies();
		return m_ProjectionMatrix;
	}

	const glm::mat4& OrthographicCamera::GetViewProjectionMatrix()
	{
		UpdateMatricies();
		return m_ProjectionViewMatrix;
	}
	const RectF& OrthographicCamera::GetViewBounds()
	{
		return m_ViewBounds;
	}

	void OrthographicCamera::UpdateMatricies()
	{
		if(m_ProjectionNeedUpdate)
		{
			m_ProjectionMatrix = glm::ortho(m_ViewBounds.left, m_ViewBounds.right, m_ViewBounds.bottom, m_ViewBounds.top, m_NearPlane, m_FarPlane);
		}
		if(m_ViewNeedUpdate)
		{
			m_InverseViewMatrix = glm::mat4(1);
			m_InverseViewMatrix = glm::translate(m_InverseViewMatrix, glm::vec3{ m_Position.x,m_Position.y,m_Position.z });
			m_InverseViewMatrix = glm::rotate(m_InverseViewMatrix, glm::radians(m_Orientation.x), { 1,0,0 });
			m_InverseViewMatrix = glm::rotate(m_InverseViewMatrix, glm::radians(m_Orientation.y), { 0,1,0 });
			m_InverseViewMatrix = glm::rotate(m_InverseViewMatrix, glm::radians(m_Orientation.z), { 0,0,1 });
			
			m_ViewMatrix = glm::inverse(m_InverseViewMatrix);
		}
		if(m_ViewNeedUpdate | m_ProjectionNeedUpdate)
		{
			m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
			m_ViewNeedUpdate = false;
			m_ProjectionNeedUpdate = false;
		}
	}

	void OrthographicCamera::SetPosition(Vec3F position)
	{
		m_Position = position;
		m_ViewNeedUpdate = true;
	}

	void OrthographicCamera::Move(Vec3F movement)
	{
		m_Position += movement;
		m_ViewNeedUpdate = true;
	}

	void OrthographicCamera::SetOrientation(Vec3F orientation)
	{
		m_Orientation = orientation;
		m_ViewNeedUpdate = true;
	}

	void OrthographicCamera::Orientate(Vec3F orientation)
	{
		m_Orientation += orientation;
		m_ViewNeedUpdate = true;
	}

	void OrthographicCamera::Orientate(float pitch, float yaw, float roll)
	{
		m_ViewNeedUpdate = true;
		m_Orientation += {pitch, yaw, roll};
	}

	Vec3F& OrthographicCamera::GetPosition()
	{
		return m_Position;
	}

	Vec3F& OrthographicCamera::GetOrientation()
	{
		return m_Orientation;
	}

	/////////////////////////////////////
	//Perspective Camera
	/////////////////////////////////////


	PerspectiveCamera::PerspectiveCamera(Vec3F position, Vec3F orientation, RectF viewBounds, float fov,
		float nearPlane, float farPlane)
		: m_Position(position), m_Orientation(orientation), m_ViewBounds(viewBounds),m_Fov(fov),m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
	}

	void PerspectiveCamera::SetViewRect(float top, float bottom, float left, float right)
	{
		m_ViewBounds = { left,right,top,bottom };
		m_ProjectionNeedUpdate = true;
	}

	void PerspectiveCamera::SetViewRect(RectF rect)
	{
		m_ViewBounds = rect;
		m_ProjectionNeedUpdate = true;
	}

	const glm::mat4& PerspectiveCamera::GetViewMatrix()
	{
		UpdateMatricies();
		return m_ViewMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetInverseViewMatrix()
	{
		UpdateMatricies();
		return m_InverseViewMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetProjectionMatrix()
	{
		UpdateMatricies();
		return m_ProjectionMatrix;
	}

	const glm::mat4& PerspectiveCamera::GetViewProjectionMatrix()
	{
		UpdateMatricies();
		return m_ProjectionViewMatrix;
	}
	const RectF& PerspectiveCamera::GetViewBounds()
	{
		return m_ViewBounds;
	}

	const glm::vec3 PerspectiveCamera::GetLeftVector() const
	{
		auto right = glm::row(m_ViewMatrix, 0);
		return glm::vec3{ right.x,right.y,right.z };
	//	return right;
	}

	const glm::vec3 PerspectiveCamera::GetUpVector() const
	{
		auto up = glm::row(m_ViewMatrix, 1);
		return glm::vec3{ 0,1,0 };
	//	return up;
	}	

	const glm::vec3 PerspectiveCamera::GetForwardVector() 
	{
		auto forward = glm::row(m_ViewMatrix, 2);
		return glm::vec3{ forward.x,forward.y,forward.z };
	}

	void PerspectiveCamera::UpdateMatricies()
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

			glm::vec3 front;
		front.x = cos(glm::radians(m_Orientation.y)) * cos(glm::radians(m_Orientation.x));
			front.y = sin(glm::radians(m_Orientation.x));
			front.z = sin(glm::radians(m_Orientation.y)) * cos(glm::radians(m_Orientation.x));
			front = glm::normalize(front);
			m_ViewMatrix = glm::lookAt(glm::vec3(m_Position.x, m_Position.y,m_Position.z), glm::vec3(m_Position.x, m_Position.y, m_Position.z)+ front, { 0,1,0 });
		}
		if (m_ViewNeedUpdate | m_ProjectionNeedUpdate)
		{
			m_ProjectionViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
			m_ViewNeedUpdate = false;
			m_ProjectionNeedUpdate = false;
		}
	}


	void PerspectiveCamera::SetPosition(Vec3F position)
	{
		m_Position = position;
		m_ViewNeedUpdate = true;
	}

	void PerspectiveCamera::Move(Vec3F movement)
	{
		m_Position += movement;
		m_ViewNeedUpdate = true;
	}

	void PerspectiveCamera::SetOrientation(Vec3F orientation)
	{
		m_Orientation = orientation;
		m_ViewNeedUpdate = true;
	}

	void PerspectiveCamera::Orientate(Vec3F orientation)
	{
		m_Orientation += orientation;
		m_ViewNeedUpdate = true;
	}

	void PerspectiveCamera::Orientate(float pitch, float yaw, float roll)
	{
		m_ViewNeedUpdate = true;
		m_Orientation += {pitch, yaw, roll};
	}

	Vec3F& PerspectiveCamera::GetPosition()
	{
		return m_Position;
	}

	Vec3F& PerspectiveCamera::GetOrientation()
	{
		return m_Orientation;
	}
}
