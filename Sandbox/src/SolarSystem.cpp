#include "SolarSystem.h"
#include "Hypo/3D/Renderer/Renderer.h"
#include "Hypo/3D/Asset/AssetManager.h"

SolarSystem::SolarSystem()
{
}

SolarSystem::~SolarSystem()
{
}

void SolarSystem::AddPlanet(Hypo::Vec3F position, Hypo::Vec3F momentum, float mass, float radius,  Hypo::Texture2D::Ptr texture)
{
	auto& planetShader = Hypo::AssetManager::RetrieveShaderAsset("MeshShader", "res\\shaders\\lightShader.glsl");
	static Hypo::Mesh& planetMesh = Hypo::MeshFactory::CreateUVSphere(Hypo::VertexPosTexNorm, 20, 20, 1);

	Planet planet = Planet{ position, momentum, mass, Hypo::SimpleModel(planetMesh, planetShader, texture) };
	planet.planet.SetScaling(radius);

	m_Planets.push_back(planet);

}

void SolarSystem::Update(float dt)
{
	float calc_per_second = 1000;

	float calc_this_frame = calc_per_second * dt;

	float dt_calc = dt / calc_this_frame * 0.03;

	for(auto& planet : m_Planets)
	{
		for (int i = 0; i < calc_this_frame; i++)
		{
			Hypo::Vec3F force;

			for(auto& other : m_Planets)
			{
				if(&planet != &other)
				{
					force += CalculateForce(planet, other);
				}
			}


				planet.momentum += force * dt_calc;
				planet.position = planet.position + planet.momentum / planet.mass * dt_calc;
		}
		planet.planet.SetPosition(planet.position);
	}
}

void SolarSystem::Render()
{
	for(auto& planet : m_Planets)
	{
		Hypo::Renderer::Submit(planet.planet);
	}
}

Hypo::Vec3F SolarSystem::CalculateForce(Planet p1, Planet p2)
{

	const auto r_vec = p1.position - p2.position;

	const float r_mag = r_vec.Len();

	const auto r_hat = r_vec.GetNormalized();

	const float force_mag = (G * p1.mass * p2.mass) / (std::pow(r_mag, 2));

	Hypo::Vec3F force_vec = r_hat * -force_mag;
	return force_vec;
}
