#include "hypo3dpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Hypo/3D/Asset/AssetManager.h"
#include "Hypo/3D/Renderer/Renderer.h"

namespace Hypo
{
	Scene::Scene()
	{
		auto entity = CreateEntity("Constructor");

	}

	void Scene::Update(float dt)
	{
	}

	void Scene::Render()
	{
		SceneLights lights;

		auto pointLights = m_Registry.view<PointLightComponent>();
		for(auto entity : pointLights)
		{
			lights.PointLights.push_back(pointLights.get<PointLightComponent>(entity).Light);
		}


		auto camera = m_Registry.view<CameraComponent>().front();
		HYPO_CORE_ASSERT(camera != entt::null, "Scene needs to have atleast one entity with CameraComponent");

		Renderer::BeginScene(m_Registry.get<CameraComponent>(camera).Camera, lights);

		auto meshShader = Hypo::AssetManager::RetrieveShaderAsset("MeshShader", "res\\shaders\\lightShader.glsl");
		auto debugShader = Hypo::AssetManager::RetrieveShaderAsset("DebugShader", "res\\shaders\\basicColor.glsl");
		{
			auto group = m_Registry.group<MeshComponent, TransformComponent, Render3DComponent>();

			for(auto entity : group)
			{
				if (!m_Registry.has<MaterialComponent>(entity))
				{
  					auto& [transform, mesh, renderer] = group.get<TransformComponent, MeshComponent, Render3DComponent>(entity);
					Renderer::Submit(renderer.Shader.IsNull() ? meshShader : renderer.Shader, transform.GetTransform(), mesh.Mesh.GetRef());
				}
			}
			auto group2 = m_Registry.group<MeshComponent, TransformComponent, MaterialComponent, Render3DComponent>();
			for (auto entity : group2)
			{
				auto& [transform, mesh, material, renderer] = group2.get<TransformComponent, MeshComponent, MaterialComponent, Render3DComponent>(entity);
				Renderer::Submit(renderer.Shader.IsNull() ? meshShader : renderer.Shader, transform.GetTransform(), mesh.Mesh.GetRef(), material.Texture, "texture1");

			}
		}
		{
			auto debugRenderGroup = m_Registry.group<>(entt::get<MeshComponent, TransformComponent, DebugRenderComponent>);

			for (auto entity : debugRenderGroup)
			{
				if (!m_Registry.has<MaterialComponent>(entity))
				{
					auto& [transform, mesh, renderer] = debugRenderGroup.get<TransformComponent, MeshComponent, DebugRenderComponent>(entity);
					if(renderer.Enabled)
						Renderer::DebugSubmit(debugShader, transform.GetTransform(), mesh.Mesh, renderer.Color);
				}
			}
		}
		Renderer::EndScene();

	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity(this, m_Registry.create());
		
		entity.AddComponent<TagComponent>().Tag = name.empty() ? "Unnamed" : name;

		entity.AddComponent<TransformComponent>();
		return entity;
		
	}
}
