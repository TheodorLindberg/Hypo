#pragma once
#include "Hypo/3D/Exports.h"
#include "Camera.h"
#include "Hypo/3D/Scene/Entity.h"

namespace  Hypo
{
	class Entity;

	class HYPO_3D_API ThridPersonKeyboardCamera : public PerspectiveCamera
	{
	public:
		virtual void Update(float dt);
	private:

	};

	class HYPO_3D_API FirstPersonCamera : public PerspectiveCamera
	{
	public:
		FirstPersonCamera();
		virtual void Update(float dt);
	private:

		Vec2F m_LastMousePos;
	};

	class HYPO_3D_API FollowCamera : public PerspectiveCamera
	{
	public:
		FollowCamera(Entity& target) : m_Target(target) {}
		virtual void Update(float dt);
		void SetFollowDistance(float distance) { followDistance = distance; }

		void UpdateMatricies() override;
	private:
		Entity& m_Target;
		float followDistance = 5;
		Vec2F m_LastMousePos;

		float pitch = 0;
		float yaw = 0;
		float angleAroundPlayer = 0;

	};
}