#include "hypo3dpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Hypo/3D/Asset/AssetManager.h"
#include "Hypo/3D/Renderer/Renderer.h"

namespace Hypo
{
	Scene::Scene()
	{
	}

	void Scene::Update(float dt)
	{
	}

	void Scene::Render()
	{
		SceneLights lights;

		auto camera = m_Registry.view<CameraComponent>().front();
		HYPO_CORE_ASSERT(camera != entt::null, "Scene needs to have atleast one entity with CameraComponent");

		Renderer::BeginScene(m_Registry.get<CameraComponent>(camera).Camera, lights);

		auto meshShader = Hypo::AssetManager::RetrieveShaderAsset("MeshShader", "res\\shaders\\lightShader.glsl");

		auto group = m_Registry.group<TransformComponent>(entt::get<MeshComponent>);

		for(auto entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, MeshComponent>(entity);
			
		}
		Renderer::EndScene();

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		const auto entity = m_Registry.create();
		m_Registry.emplace<TagComponent>(entity, name.empty() ? "Unnamed" : name);

		m_Registry.emplace<TransformComponent>(entity);

		return Entity{ this, entity };
		
	}
}
