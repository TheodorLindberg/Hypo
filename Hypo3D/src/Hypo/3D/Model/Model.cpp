#include "hypo3dpch.h"
#include <glad/glad.h>
#include "Model.h"
#include "Hypo/3D/Renderer/Renderer.h"

namespace Hypo
{
	SimpleModel::SimpleModel(Mesh& mesh, Shader::Ptr& shader)
		: m_Mesh(mesh), m_Shader(shader)
	{
	}

	SimpleModel::SimpleModel(Mesh& mesh, Shader::Ptr& shader, Texture2D::Ptr& texture)
		: m_Mesh(mesh), m_Shader(shader), m_Material(texture)
	{
	}

	void SimpleModel::Submit()
	{
		m_Material.texture->Bind();
		Renderer::Submit(m_Shader, GetTransform(), m_Mesh);
	}
}
