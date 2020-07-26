#pragma once
#include <entt/entt.hpp>
#include "Hypo/3D/Scene/Scene.h"
#include "Hypo/Core.h"
#include "Hypo/System/Util/Log.h"

namespace Hypo
{
	class Entity
	{
	public:
		Entity() = default;
		Entity(Scene* scene, entt::entity handle)
			:m_Scene(scene), m_EntityHandle(handle)
		{}
		Entity(const Entity & other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			HYPO_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			HYPO_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HYPO_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
	private:
		Scene* m_Scene = nullptr;
		entt::entity m_EntityHandle = entt::null;
	};
}
