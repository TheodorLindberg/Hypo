#include "hypo3dpch.h"
#include "Renderer.h"
#include "Drawable.h"
#include "Transform.h"
#include "Hypo/System/Util/Log.h"

#include "glad/glad.h"
#include "Hypo/3D/Camera/Camera.h"
#include "Hypo/3D/Asset/AssetLoader.h"

namespace Hypo
{
	std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData;
	std::unique_ptr<Renderer::SceneRendererData> Renderer::s_SceneRendererData;

	void InitRenderer(void* ptr)
	{
		const int status = gladLoadGLLoader((GLADloadproc)ptr);
	}


	void Renderer::BeginScene(Camera* camera, SceneLights& lights)
	{
 		auto& sceneData = GetSceneData();
		auto& sceneRendererData = GetSceneRendererData();


		auto meshShader = AssetManager::RetrieveShaderAsset("MeshShader", "res\\shaders\\lightShader.glsl");
		auto basicColorShader = AssetManager::RetrieveShaderAsset("ColorShader", "res\\shaders\\basicColor.glsl");

			
		if (!meshShader)
		{
			HYPO_CORE_WARN("Failed to load basicColor shader for simple geometry");
		}

		sceneRendererData->m_MeshShader = meshShader;
		sceneRendererData->m_IntermediateColorShader = basicColorShader;


		auto& transformBinder = UniformBinderManager::GetUniformBinder("Transform");
		if (!transformBinder)
		{ 
			HYPO_CORE_ASSERT(false, "Could not find uniform transform, scene setup invalid");
		}

		sceneRendererData->m_TransformBuffer = UniformBuffer::Create(transformBinder);
			

		auto& colorBuffer = UniformBinderManager::GetUniformBinder("SingleColor");
		if (!colorBuffer)
		{
			HYPO_CORE_ASSERT(false, "Could not find uniform color, scene setup invalid");
		}

		sceneRendererData->m_IntermediateColorBuffer = UniformBuffer::Create(colorBuffer);

		sceneData->m_ProjectionMatrix = camera->GetProjectionMatrix();
		sceneData->m_ViewMatrix = camera->GetViewMatrix();
		sceneRendererData->m_TransformBuffer->Set("u_ProjectionViewMatrix", sceneData->m_ProjectionMatrix * sceneData->m_ViewMatrix);
		sceneRendererData->m_TransformBuffer->Set("u_ViewMatrix", sceneData->m_ProjectionMatrix);

		sceneRendererData->m_TransformBuffer->Set("u_ViewPos", camera->GetViewPosition());


		//Lights
		auto& pointLightBinder = UniformBinderManager::GetUniformBinder("PointLightsBlock");
		if (!pointLightBinder)
		{
			HYPO_CORE_ASSERT(false, "Could not find uniform point light, scene setup invalid");
		}
		//sceneRendererData->m_IntermediateColorBuffer = ;

		sceneRendererData->m_PointLightsBuffer = UniformBuffer::Create(pointLightBinder);
		auto& buffer = sceneRendererData->m_PointLightsBuffer;
		for(int i = 0; i < lights.PointLights.size(); i++)
		{
			PointLight& light = lights.PointLights[i];
			std::string s = "lights[" +std::to_string(i) +"].";
			buffer->Set((s + "position").c_str(), light.Position);
			buffer->Set((s + "constant").c_str(), light.Constant);
			buffer->Set((s + "linear").c_str(), light.Linear);
			buffer->Set((s + "quadratic").c_str(), light.Quadratic);
			buffer->Set((s + "ambient").c_str(), light.Ambient);
			buffer->Set((s + "diffuse").c_str(), light.Diffuse);
			buffer->Set((s + "specular").c_str(), light.Specular);
		}
	}

	void Renderer::Submit(Drawable& drawable)
	{
		drawable.Submit();
	}

	void Renderer::Submit(Shader::Ptr& shader, VertexArray::Ptr& vertexArray)
	{
		shader->Bind();
		//shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray, vertexArray->GetMeshType());
		vertexArray->Unbind();
		shader->UnBind();
	}

	void Renderer::Submit(Shader::Ptr& shader, glm::mat4& transform, VertexArray::Ptr& vertexArray)
	{
		shader->Bind();
		shader->BindUniformBuffer(GetSceneRendererData()->m_TransformBuffer);
		shader->BindUniformBuffer(GetSceneRendererData()->m_PointLightsBuffer);
		GetSceneRendererData()->m_TransformBuffer->Set("u_ModelMatrix", transform);
		
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
		vertexArray->Unbind();
		shader->UnBind();
	}
	
	void Renderer::Submit(Shader::Ptr& shader, Mesh& mesh)
	{
		shader->Bind();
		shader->BindUniformBuffer(GetSceneRendererData()->m_TransformBuffer);
		shader->BindUniformBuffer(GetSceneRendererData()->m_PointLightsBuffer);
		mesh.Bind();
		RenderCommand::DrawIndexed(mesh.m_VertexArray, mesh.GetMeshType());
		mesh.UnBind();
		shader->UnBind();

	}

	
	void Renderer::Submit(Shader::Ptr& shader, glm::mat4& transform, Mesh& mesh)
	{
		shader->Bind();
		mesh.Bind();
		GetSceneRendererData()->m_TransformBuffer->Set("u_ModelMatrix", transform);
		
		shader->BindUniformBuffer(GetSceneRendererData()->m_TransformBuffer);
		shader->BindUniformBuffer(GetSceneRendererData()->m_PointLightsBuffer);
		RenderCommand::DrawIndexed(mesh.m_VertexArray, mesh.GetMeshType());
		mesh.m_VertexArray->Unbind();
		mesh.UnBind();
		shader->UnBind();
	}

	void Renderer::Submit(Shader::Ptr& shader, glm::mat4& transform, Mesh& mesh, Texture2D::Ptr& texture, const std::string& textureName)
	{
		shader->Bind();
		mesh.Bind();
		GetSceneRendererData()->m_TransformBuffer->Set("u_ModelMatrix", transform);
		shader->BindTexture(texture, textureName);
		shader->BindUniformBuffer(GetSceneRendererData()->m_TransformBuffer);
		shader->BindUniformBuffer(GetSceneRendererData()->m_PointLightsBuffer);
		RenderCommand::DrawIndexed(mesh.m_VertexArray, mesh.GetMeshType());
		mesh.UnBind();
		shader->UnBind();
	}

	/*
	void Renderer::Submit(Shader::Ptr& shader, BatchRendererBuffer::Ptr& batchRendererBuffer)
	{
		shader->Bind();
		shader->BindUniformBuffer(m_ActiveSceneData->m_TransformUniforms);
		RenderCommand::DrawInstanced(batchRendererBuffer);
		shader->UnBind();
	}*/

	
	void Renderer::RenderCube(Vec3F position, Vec3F size, Vec4F color,float rotX, float rotY, float rotZ)
	{	
		static const Mesh& cubeMesh = MeshFactory::CreateCube(VertexPositions, 1.f);
		auto transform = Transform::CreateTransform(position, size, { rotX, rotY, rotZ }, { 0,0,0 });
		GetSceneRendererData()->m_IntermediateColorBuffer->Set("u_Color", color);
		GetSceneRendererData()->m_IntermediateColorShader->BindUniformBuffer(GetSceneRendererData()->m_IntermediateColorBuffer);
		
		auto shader = GetSceneRendererData()->m_IntermediateColorShader;
		shader->Bind();
		shader->BindUniformBuffer(GetSceneRendererData()->m_TransformBuffer);
		GetSceneRendererData()->m_TransformBuffer->Set("u_ModelMatrix", transform);
		cubeMesh.m_VertexArray->Bind();
		RenderCommand::DrawIndexed(cubeMesh.m_VertexArray);
		cubeMesh.m_VertexArray->Unbind();
		shader->UnBind();
	}

	std::unique_ptr<Renderer::SceneData>& Renderer::GetSceneData()
	{
		if(!s_SceneData)
		{
			s_SceneData = std::make_unique<SceneData>();
		}
		return s_SceneData;
	}

	std::unique_ptr<Renderer::SceneRendererData>& Renderer::GetSceneRendererData()
	{
		if (!s_SceneRendererData)
		{
			s_SceneRendererData = std::make_unique<SceneRendererData>();
		}
		return s_SceneRendererData;
	}


	void Renderer::EndScene()
	{
	}
}
