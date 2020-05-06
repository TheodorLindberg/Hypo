#pragma once
#include "Hypo/3D/Exports.h"
#include "glm/glm.hpp"

namespace Hypo
{
	class Camera
	{
	public:
		Camera() = default;
		virtual ~Camera() = default;
		virtual const glm::mat4& GetViewMatrix() = 0;
		virtual const glm::mat4& GetInverseViewMatrix() = 0;
		virtual const glm::mat4& GetProjectionMatrix() = 0;
		virtual const glm::mat4& GetViewProjectionMatrix() = 0;
		virtual const Vec3F& GetViewPosition() = 0;
		virtual const RectF& GetViewBounds() = 0;
	};

	class HYPO_3D_API OrthographicCamera : public Camera
	{
	public:
		OrthographicCamera() = default;
		//OrthographicCamera(Vec3F position, Vec3F orientation, RectF viewBounds, float nearPlane = -1, float farPlane = 1);

		void SetPosition(Vec3F position);;
		void Move(Vec3F movement);

		void SetOrientation(Vec3F orientation);
		void Orientate(Vec3F orientation);
		void Orientate(float pitch, float yaw, float roll);

		Vec3F& GetPosition();
		Vec3F& GetOrientation();

		void SetViewRect(float top, float bottom, float left, float right);
		void SetViewRect(RectF rect);

		void SetPlane(float near, float far);

		const glm::mat4& GetViewMatrix() override;
		const glm::mat4& GetInverseViewMatrix() override;
		const glm::mat4& GetProjectionMatrix() override;
		const glm::mat4& GetViewProjectionMatrix() override;
		const Vec3F& GetViewPosition() override { return m_Position; }
		const RectF& GetViewBounds() override;

	private:
		void UpdateMatricies();
	private:
		Vec3F m_Position = {0,0,0};
		Vec3F m_Orientation = { 0,0,0 };
		bool m_ViewNeedUpdate = true;
		bool m_ProjectionNeedUpdate = true;

		RectF m_ViewBounds = {-1,1,-1,1};
		float m_NearPlane = 1;
		float m_FarPlane = -1;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_InverseViewMatrix;
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ProjectionViewMatrix;
	};
	class HYPO_3D_API PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera() = default;
		PerspectiveCamera(Vec3F position, Vec3F orientation, RectF viewBounds, float fov = 45, float nearPlane = 0.1, float farPlane = 1000);

		void SetPosition(Vec3F position);;
		void Move(Vec3F movement);

		void SetOrientation(Vec3F orientation);
		void Orientate(Vec3F orientation);
		void Orientate(float pitch, float yaw, float roll);

		Vec3F& GetPosition();
		Vec3F& GetOrientation();

		void SetViewRect(float top, float bottom, float left, float right);
		void SetViewRect(RectF rect);

		void SetPlane(float near, float far);
		void SetFov(float fov);

		const glm::mat4& GetViewMatrix() override;
		const glm::mat4& GetInverseViewMatrix() override;
		const glm::mat4& GetProjectionMatrix() override;
		const glm::mat4& GetViewProjectionMatrix() override;
		const Vec3F& GetViewPosition() override { return m_Position; }
		const RectF& GetViewBounds() override;

		const glm::vec3 GetLeftVector() const;
		const glm::vec3 GetUpVector() const;
		const glm::vec3 GetForwardVector();

	private:
		void UpdateMatricies();
	private:
		Vec3F m_Position = { 0,0,0 };
		Vec3F m_Orientation = { 0,0,0 };
		bool m_ViewNeedUpdate = true;
		bool m_ProjectionNeedUpdate = true;

		RectF m_ViewBounds = { -1,1,-1,1 };
		float m_NearPlane = 0.1f;
		float m_FarPlane = 1000.f;
		float m_Fov = 45.f;

		glm::mat4 m_ViewMatrix = glm::mat4(1);
		glm::mat4 m_InverseViewMatrix = glm::mat4(1);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1);
		glm::mat4 m_ProjectionViewMatrix = glm::mat4(1);
	};
	
}
