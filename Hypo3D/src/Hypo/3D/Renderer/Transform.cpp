#include "hypo3dpch.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Hypo
{
	glm::mat4 Transform::CreateTransform(Vec3F position, Vec3F scale, Vec3F rotation, Vec3F origin)
	{
		glm::mat4 transform = glm::mat4(1);
		transform = glm::translate(transform, glm::vec3{ position.x,position.y, position.z });
		transform = glm::translate(transform, glm::vec3{ -origin.x,-origin.y, -origin.z });

		transform = glm::scale(transform, glm::vec3{ scale.x,scale.y, scale.z });


		transform = glm::rotate(transform, rotation.x, glm::vec3{ 1,0,0 });
		transform = glm::rotate(transform, rotation.y, glm::vec3{ 0,1,0 });
		transform = glm::rotate(transform, rotation.z, glm::vec3{ 0,0,1 });

		transform = glm::translate(transform, glm::vec3{ origin.x,origin.y, origin.z });
		return transform;
	}

	Transformable::Transformable()
		: m_Position(0, 0, 0), m_Scaling(1, 1, 1), 
		  m_Rotation(0, 0, 0), m_Origin(0, 0, 0), 
	      m_Update(true), m_Transform()
	{
	}

	Transformable::Transformable(Vec3F position, Vec3F scaling, Vec3F rotation, Vec3F origin)
		: m_Position(position), m_Scaling(scaling),
	      m_Rotation(rotation), m_Origin(origin),
		  m_Update(true), m_Transform()
	{
	}

	glm::mat4& Transformable::GetTransform()
	{
		if(m_Update)
		{
			m_Transform = glm::mat4(1);
			m_Transform = glm::translate(m_Transform, glm::vec3{ m_Position.x,m_Position.y, m_Position.z});
			m_Transform = glm::translate(m_Transform, glm::vec3{ -m_Origin.x,-m_Origin.y, -m_Origin.z });

			m_Transform = glm::scale(m_Transform, glm::vec3{  m_Scaling.x,m_Scaling.y, m_Scaling.z });


			m_Transform = glm::rotate(m_Transform, m_Rotation.x, glm::vec3{1,0,0});
			m_Transform = glm::rotate(m_Transform, m_Rotation.y,glm::vec3{ 0,1,0 });
			m_Transform = glm::rotate(m_Transform, m_Rotation.z, glm::vec3{ 0,0,1 });

			m_Transform = glm::translate(m_Transform, glm::vec3{ m_Origin.x,m_Origin.y, m_Origin.z });
		}
		return m_Transform;
	}
}
