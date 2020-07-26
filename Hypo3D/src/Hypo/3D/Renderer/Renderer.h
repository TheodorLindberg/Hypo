#pragma once
#include "RenderCommand.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"

#include "Hypo/Graphics/Shader/UniformBuffer.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hypo/3D/Renderer/Scene.h"

namespace Hypo
{
	class Camera;

	void HYPO_3D_API InitRenderer(void*);
	class Drawable;
	class HYPO_3D_API Renderer
	{
	public:
		static void BeginScene(Camera* camera, SceneLights& lights);
		static void EndScene();


		static void Submit(Drawable& drawable);
		static void Submit(Shader::Ptr& shader, VertexArray::Ptr& vertexArray);
		static void Submit(Shader::Ptr& shader, glm::mat4& transform, VertexArray::Ptr& vertexArray);
		static void Submit(Shader::Ptr& shader, Mesh& mesh);
		static void Submit(Shader::Ptr& shader, glm::mat4& transform, Mesh& mesh);
		static void Submit(Shader::Ptr& shader, glm::mat4& transform, Mesh& mesh, Texture2D::Ptr& texture, const std::string& textureName);


		//Simple mesh renderer
		static void RenderCube(Vec3F position, Vec3F size, Vec4F color = {1.f,1.f,1.f,1.f}, float rotX = 0, float rotY = 0, float rotZ = 0);
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	public:

		struct SceneData
		{
			glm::mat4 m_ProjectionMatrix;
			glm::mat4 m_ViewMatrix;
			SceneLights lights;
		};

		struct SceneRendererData
		{
			Shader::Ptr m_MeshShader;

			Shader::Ptr m_IntermediateColorShader;
			Shader::Ptr m_IntermediateTextureShader;

			UniformBuffer::Ptr m_TransformBuffer;
			UniformBuffer::Ptr m_PointLightsBuffer;
			UniformBuffer::Ptr m_IntermediateColorBuffer;


		};


		static std::unique_ptr<SceneData>& GetSceneData();
		static std::unique_ptr<SceneRendererData>& GetSceneRendererData();

	private:
		static std::unique_ptr<SceneData> s_SceneData;
		static std::unique_ptr<SceneRendererData> s_SceneRendererData;
	};
}
