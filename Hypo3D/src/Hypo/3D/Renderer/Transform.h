#pragma once
#include "Hypo/3D/Exports.h"
#include "glm/glm.hpp"

namespace Hypo
{
	
	class HYPO_3D_API Transform
	{
	public:
		Transform(float m00, float m01, float m02, float m03,
				  float m10, float m11, float m12, float m13,
				  float m20, float m21, float m22, float m23,
				  float m30, float m31, float m32, float m33);
		Transform(Vec4F r0, Vec4F r1, Vec4F r2, Vec4F r3);
		Transform(float* data);
		Transform();

		static glm::mat4 CreateTransform(Vec3F position, Vec3F scale, Vec3F rotation, Vec3F origin);
	private:
		glm::mat4 m_Transform;
	};


	class HYPO_3D_API Transformable
	{
	public:
		Transformable();
		Transformable(Vec3F position, Vec3F scaling, Vec3F rotation, Vec3F origin);

		inline void SetPosition(const Vec3F& position) { m_Position = position; };
		inline void SetScaling(const Vec3F& scaling) { m_Scaling = scaling; };
		inline void SetRotation(const Vec3F& rotation) { m_Rotation = rotation; };
		inline void SetOrigin(const Vec3F& origin) { m_Origin = origin; };

		inline Vec3F& GetPosition() { return m_Position; };
		inline Vec3F& GetScaling() { return m_Scaling; };
		inline Vec3F& GetRotation() { return m_Rotation; };
		inline Vec3F& GetOrigin() { return m_Origin; };

		inline void Move(const Vec3F& movement) { m_Position += movement; };
		inline void Scale(const Vec3F& scaling) { m_Scaling += scaling; };
		inline void Rotate(const Vec3F& rotation) { m_Rotation += rotation; };
		inline void MoveOrigin(const Vec3F& movement) { m_Origin += movement; };

		glm::mat4& GetTransform();

	private:
		Vec3F m_Position;
		Vec3F m_Scaling;
		Vec3F m_Rotation;
		Vec3F m_Origin;

		bool m_Update;
		glm::mat4 m_Transform;
	};
}