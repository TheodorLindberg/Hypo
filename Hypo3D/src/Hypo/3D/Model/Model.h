#pragma once
#include "Hypo/3D/Exports.h"
#include "Mesh.h"
#include "Material.h"
#include "Hypo/3D/Renderer/Transform.h"
#include "Hypo/3D/Renderer/Drawable.h"

namespace  Hypo
{
	class Model
	{
		
	};

	//A simple model render a set of vertices with basic material
	class HYPO_3D_API SimpleModel : public Transformable, public Drawable
	{
	public:
		SimpleModel(Mesh& mesh, Shader::Ptr& shader);
		SimpleModel(Mesh& mesh, Shader::Ptr& shader, Texture2D::Ptr& texture);
	private:
		void Submit() override;
		Shader::Ptr& GetShader() override { return m_Shader; }
	private:
		Mesh m_Mesh;
		Shader::Ptr m_Shader;
		SimpleMaterial m_Material;
	};
}
