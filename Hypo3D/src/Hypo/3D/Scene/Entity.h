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
			:m_Scene(scene), m_Handle(handle)
		{}

		template<typename T, typename ...Args>
		T& AddComponent(Args &&... args)
		{
			return m_Scene->m_Registry.emplace<T>(m_Handle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			HYPO_CORE_ASSERT(HasComponent<T>(), "Entity dosn't have component");
			return m_Scene->m_Registry.get<T>(m_Handle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_Handle);
		}

		template<typename T>
		T& RemoveComponent()
		{
			HYPO_CORE_ASSERT(HasComponent<T>(), "Entity dosn't have component");
			return m_Scene->m_Registry.remove<T>(m_Handle);
		}
	private:
		Scene* m_Scene = nullptr;
		entt::entity m_Handle = entt::null;
	};
}
