#pragma once
#include <Hypo/Hypo.h>
#include "Hypo/Graphics/BufferLayout.h"
#include <Hypo/Graphics/Texture/Texture.h>
#include "Hypo/3D/Model/Model.h"

class SolarSystem
{
public:
	struct Planet
	{
		Hypo::Vec3F position;
		Hypo::Vec3F momentum;
		float mass;
		Hypo::SimpleModel planet;
	};

	SolarSystem();
	~SolarSystem();



	void AddPlanet(Hypo::Vec3F position, Hypo::Vec3F momentum, float mass, float radius, Hypo::Texture2D::Ptr texture);

	void Update(float dt);

	void Render();

private:

	Hypo::Vec3F CalculateForce(Planet p1, Planet p2);

	static constexpr float G = 1.f;
	std::vector<Planet> m_Planets;
};
