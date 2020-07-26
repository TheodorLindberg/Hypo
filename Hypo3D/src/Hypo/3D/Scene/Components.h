#pragma once
#include <string>
#include "Hypo/3D/Renderer/Transform.h"
#include "Hypo/3D/Model/mesh.h"
#include "Hypo/3D/Camera/Camera.h"
#include "Hypo/3D/Asset/Light.h"

namespace Hypo
{
	//Name component for every entity
	class TagComponent
	{
	public:
		TagComponent() = default;
		TagComponent(const std::string& tag)
			: Tag(tag)
		{}
		TagComponent(std::string&& tag)
			: Tag(std::move(tag))
		{}
		std::string Tag;
	};

	class TransformComponent : public Transformable
	{
	public:
		TransformComponent() = default;
		TransformComponent(Vec3F position, Vec3F scaling = { 1,1,1 }, Vec3F rotation = { 0,0,0 }, Vec3F origin = { 0,0,0 })
			: Transformable(position, scaling, rotation, origin)
		{}
	};

	class MeshComponent
	{
	public:
		MeshComponent() = default;
		MeshComponent(Mesh::Ptr mesh)
			: Mesh(mesh)
		{}
		
		Mesh::Ptr Mesh;
	};	
	struct CameraComponent
	{
		CameraComponent() = default;
		CameraComponent(Camera* camera)
			: Camera(camera)
		{}

		Camera* Camera;
	};
	struct MaterialComponent
	{
		MaterialComponent() = default;
		MaterialComponent(Texture2D::Ptr texture)
			: Texture(texture)
		{}

		Texture2D::Ptr Texture;
	};
	struct PointLightComponent
	{
		PointLightComponent() = default;
		PointLightComponent(const PointLight& light)
			: Light(light)
		{}

		PointLight Light;
	};

	struct Render3DComponent
	{
		Render3DComponent() = default;
		Render3DComponent(Shader::Ptr shader) 
		: Shader(shader) 
		{}
		Shader::Ptr Shader = nullptr;
	};

	struct DebugRenderComponent
	{
		DebugRenderComponent() = default;
		bool Enabled = true;
		Vec4F Color;
	};
}
