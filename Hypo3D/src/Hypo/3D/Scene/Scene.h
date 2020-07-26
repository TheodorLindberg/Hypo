#pragma once
#include <entt/entt.hpp>
#include "Components.h"
#include "Hypo/3D/Exports.h"

namespace Hypo
{

	class Entity;
	class HYPO_3D_API Scene
	{
	public:
		Scene();
		~Scene() = default;


		void Update(float dt);
		void Render();
		Entity CreateEntity(const std::string& name = std::string());
	public:
		entt::registry m_Registry;
		friend class Entity;
	};

}
