#pragma once
#include "Hypo/3D/Exports.h"

namespace Hypo
{
	class PointLight
	{
	public:
		Vec3F Position = {0,0,0};

		float Constant = 1.f;
		float Linear = 0.09;
		float Quadratic = 0.032;

		Vec3F Ambient = {0.05f, 0.05f,0.05f};
		Vec3F Diffuse = {0.8f,0.8f,0.8f};
		Vec3F Specular = {1,1,1};
	};

	class DirectionalLight
	{
	public:
		Vec3F Direction = { 0,0,0 };

		Vec3F Ambient = { 0.05f, 0.05f,0.05f };
		Vec3F Diffuse = { 0.4f,0.4f,0.4f };
		Vec3F Specular = { 0.5f,0.5f,0.5f };
	};

	class SpotLight
	{
		Vec3F Position = { 0,0,0 };
		Vec3F Direction = { 0,0,0 };
		Vec3F Ambient = { 0.f,0.f,0.f };
		Vec3F Diffuse = { 1.f,1.f,1.f };
		Vec3F Specular = { 1.f,1.f,1.f };

		float Constant = 1.f;
		float Linear = 0.09f;
		float Quadratic = 0.032;
		float CutOff = glm::cos(glm::radians(12.5f));
		float OuterCutOff = glm::cos(glm::radians(15.f));

	};
}