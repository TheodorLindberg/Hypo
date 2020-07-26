#pragma once
#include <string>
#include "Hypo/3D/Renderer/Transform.h"
#include "Hypo/3D/Model/mesh.h"
#include "Hypo/3D/Camera/Camera.h"

namespace Hypo
{
	//Name component for every entity
	struct TagComponent
	{
		TagComponent(const std::string& tag)
			: Tag(tag)
		{}
		TagComponent(std::string&& tag)
			: Tag(std::move(tag))
		{}
		std::string Tag;
	};

	struct TransformComponent : public Transformable
	{
		TransformComponent() = default;
		TransformComponent(Vec3F position, Vec3F scaling = { 1,1,1 }, Vec3F rotation = { 0,0,0 }, Vec3F origin = { 0,0,0 })
			: Transformable(position, scaling, rotation, origin)
		{}
	};

	struct MeshComponent
	{
		MeshComponent(Mesh& mesh)
			: Mesh(mesh)
		{}
		
		Mesh Mesh;
	};	
	struct CameraComponent
	{
		CameraComponent(Camera* camera)
			: Camera(camera)
		{}

		Camera* Camera;
	};
}
