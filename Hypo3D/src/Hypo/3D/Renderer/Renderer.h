#pragma once
#include "RenderCommand.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"

#include "Hypo/Graphics/Shader/UniformBuffer.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hypo
{

	void HYPO_3D_API InitRenderer(void*);
	class Drawable;
	class HYPO_3D_API Renderer
	{
	public:
		struct RendererSetupData
		{
			UniformBinder::Ptr m_TransformBinder;
			UniformBuffer::Ptr m_TransformBuffer;
			
			UniformBinder::Ptr m_ColorBinder;
			UniformBuffer::Ptr m_ColorBuffer;
			Shader::Ptr m_SimpleColorShader;


		};

		struct SceneData
		{
			glm::mat4 viewMatrix;
			glm::mat4 invViewMatrix;
			glm::mat4 projectionViewMatrix;
			RectF viewBounds;
			UniformBuffer::Ptr m_TransformUniforms;
		};
		static void BeginScene(/*Camera* camera*/);
		static void EndScene();

		static void Submit(VertexArray::Ptr& vertexArray);
	//	static void Submit(Mesh& vertexArray);
		


		static void Submit(Drawable& drawable);
		static void Submit(Shader::Ptr& shader, VertexArray::Ptr& vertexArray);
		static void Submit(Shader::Ptr& shader, glm::mat4& transform, VertexArray::Ptr& vertexArray);
		//static void Submit(Shader::Ptr& shader, Mesh& mesh);
		//static void Submit(Shader::Ptr& shader, glm::mat4& transform, Mesh& mesh);
		
		static void RenderCube(Vec3F position, Vec3F size, Vec4F color = {1.f,1.f,1.f,1.f}, float rotX = 0, float rotY = 0, float rotZ = 0);
		static void RenderPlane();
		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static std::unique_ptr<RendererSetupData> m_SetupData;
		static std::unique_ptr<SceneData> m_ActiveSceneData;
	};
}
