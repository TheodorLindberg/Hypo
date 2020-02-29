#include "hypo3dpch.h"
#include "Renderer.h"
#include "Drawable.h"
#include "Transform.h"
#include "Hypo/System/Util/Log.h"

#include "glad/glad.h"

namespace Hypo
{
	std::unique_ptr <Renderer::RendererSetupData> Renderer::m_SetupData;
	std::unique_ptr <Renderer::SceneData> Renderer::m_ActiveSceneData;

	void InitRenderer(void* ptr)
	{
		const int status = gladLoadGLLoader((GLADloadproc)ptr);
	}

	void Renderer::BeginScene(/*Camera* camera*/)
	{

		if(!m_SetupData )
		{

			/*auto& transformBinder = AssetManager::GetUniformBinder("Transform");
			if (!transformBinder)
			{
				HYPO_CORE_ASSERT(false, "Could not find uniform transform, scene setup invalid");

			}
			//m_SetupData = std::make_unique<RendererSetupData>(RendererSetupData());
			auto shader = Shader::Create(ResourceLoader::LoadShader("basicColor.glsl"));
			if(!shader)
			{
				HYPO_CORE_WARN("Failed to load basicColor shader for simple geometry");
			}
			m_SetupData->m_SimpleColorShader = shader;
			*/
			
			//m_SetupData->m_ColorBinder = AssetManager::GetUniformBinder("SingleColor");
//			m_SetupData->m_ColorBuffer = UniformBuffer::Create(m_SetupData->m_ColorBinder);
			//m_SetupData->m_ColorData = UniformData(m_SetupData->m_ColorBinder);


			//m_SetupData->m_TransformBinder = AssetManager::GetUniformBinder("Transform");
	//		m_SetupData->m_TransformBuffer = UniformBuffer::Create(m_SetupData->m_TransformBinder);
		//	m_SetupData->m_TransformData = UniformData(m_SetupData->m_TransformBinder);

		}

		m_ActiveSceneData.reset(new SceneData());

	//	m_ActiveSceneData->invViewMatrix = camera->GetInverseViewMatrix();
		//m_ActiveSceneData->viewMatrix = camera->GetViewMatrix();
		//m_ActiveSceneData->projectionViewMatrix = camera->GetViewProjectionMatrix();
										
//		m_ActiveSceneData->viewBounds = camera->GetViewBounds();
	//	m_ActiveSceneData->m_TransformUniforms = m_SetupData->m_TransformBuffer;
	//	m_ActiveSceneData->m_TransformData = m_SetupData->m_TransformData;

		//m_ActiveSceneData->m_TransformData.Set("u_ViewMatrix", m_ActiveSceneData->viewMatrix);
		//m_ActiveSceneData->m_TransformData.Set("u_ProjectionViewMatrix", m_ActiveSceneData->projectionViewMatrix);
		

		//m_ActiveSceneData->m_TransformUniforms->LoadStructure(m_ActiveSceneData->m_TransformData);

	}

	void Renderer::Submit(Drawable& drawable)
	{
		auto& shader = drawable.GetShader();
		shader->Bind();
		//shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		drawable.Submit();
	}

	void Renderer::Submit(Shader::Ptr& shader, VertexArray::Ptr& vertexArray)
	{
		shader->Bind();
		//shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		vertexArray->Unbind();
		shader->UnBind();
	}

	void Renderer::Submit(Shader::Ptr& shader, glm::mat4& transform, VertexArray::Ptr& vertexArray)
	{
		shader->Bind();
		//shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		vertexArray->Unbind();
		shader->UnBind();
	}
	/*
	void Renderer::Submit(Shader::Ptr& shader, Mesh& mesh)
	{
		shader->Bind();
		shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		mesh.Bind();
		RenderCommand::DrawIndexed(mesh.m_VertexArray, mesh.GetMeshType());
		mesh.UnBind();
		shader->UnBind();

	}*/

	/*
	void Renderer::Submit(Shader::Ptr& shader, glm::mat4& transform, Mesh& mesh)
	{
		mesh.Bind();
		m_ActiveSceneData->m_TransformData.Set("u_ModelMatrix", transform);
		m_ActiveSceneData->m_TransformUniforms->LoadStructure(m_ActiveSceneData->m_TransformData);
		shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		RenderCommand::DrawIndexed(mesh.m_VertexArray, mesh.GetMeshType());
		mesh.UnBind();
		shader->UnBind();
	}*/

	/*
	void Renderer::Submit(Shader::Ptr& shader, BatchRendererBuffer::Ptr& batchRendererBuffer)
	{
		shader->Bind();
		shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		RenderCommand::DrawInstanced(batchRendererBuffer);
		shader->UnBind();
	}*/

	/*
	void Renderer::RenderCube(Vec3F position, Vec3F size, Vec4F color,float rotX, float rotY, float rotZ)
	{	
		static Mesh& cubeMesh = MeshFactory::CreateCube(VertexPositions, 1.f);
		auto transform = Transform::CreateTransform(position, size, { rotX, rotY, rotZ }, { 0,0,0 });
		m_SetupData->m_ColorData.Set("u_Color", color);
		m_SetupData->m_ColorBuffer->LoadStructure(m_SetupData->m_ColorData);
		m_SetupData->m_SimpleColorShader->BindUniformBuffer(m_SetupData->m_ColorBuffer);
		Submit(m_SetupData->m_SimpleColorShader, transform, cubeMesh);
		
	}*/

	void Renderer::EndScene()
	{
		m_ActiveSceneData.release();
	}
}
