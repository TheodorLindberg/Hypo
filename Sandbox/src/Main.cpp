#include "Hypo/Hypo.h"
#include "Hypo/Config.h"
#include "imgui.h"
#include "Hypo/System/Util/Log.h"
#include "Hypo/Window/Window.h"


#include <iostream>

#include "Hypo/Graphics/Buffers.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"
#include "Hypo/Graphics/Texture/TextureAsset.h"
#include "Hypo/Graphics/Texture/Texture.h"
#include "Hypo/3D/Renderer/RendererAPI.h"
#include "Hypo/3D/Renderer/RenderCommand.h"
#include "Hypo/3D/Renderer/Renderer.h"
#include "Hypo/3D/Model/Model.h"
#include "Hypo/3D/Camera/CameraController.h"
#include "Hypo/Graphics/BufferLayout.h"
#include <glm/ext/scalar_constants.inl>


namespace Hypo {
	class ThridPersonKeyboardCamera;
}

int main()
{
	Hypo::Log::Init();
	Hypo::Window* window = Hypo::Window::Create();
	Hypo::init(window->GetGladProc());
	Hypo::InitRenderer(window->GetGladProc());
	
	 
	auto shaderData = Hypo::ShaderFromFile("res\\shaders\\simple.glsl");
	auto shader = Hypo::Shader::Create(shaderData);
	shader->Bind();

	float vertices[] = {
		// positions				// texture coords
		 1.f,  1.f, 0.0f, 0,0,1.f,  4.0f, 4.0f,   // top right
		 1.f, -1.f, 0.0f, 0,0,1.f,  4.0f, 0.0f,   // bottom right
		-1.f, -1.f, 0.0f, 0,0,1.f,  0.0f, 0.0f,   // bottom left
		-1.f,  1.f, 0.0f, 0,0,1.f,  0.0f, 4.0f    // top left 
	};
	Hypo::ElementIndex indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	
	auto wallTexture = Hypo::Texture2D::Create(Hypo::TextureFromFile("res\\textures\\wall.jpg"));
	auto forestTexture = Hypo::Texture2D::Create(Hypo::TextureFromFile("res\\textures\\references-outerra2.jpg"));



	Hypo::ThridPersonKeyboardCamera camera;

	auto mesh2 = Hypo::MeshFactory::CreateUVSphere(Hypo::VertexPosTex, 20, 20, 0.5f);
	
	camera.SetViewRect({ Hypo::RectFromSize<float>(0,0,static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())) });
	camera.SetPosition({ -5,2, 0 });

	window->SetVSync(true);


	auto meshShaderData = Hypo::ShaderFromFile("res\\shaders\\meshShader.glsl");
	auto meshShader = Hypo::Shader::Create(meshShaderData);


	auto vertexBuffer = Hypo::VertexBuffer::Create(gsl::span<const float>(vertices));
	vertexBuffer->SetLayout(Hypo::BufferLayout{
		{Hypo::ShaderDataType::Float3,"a_Position"},
		{Hypo::ShaderDataType::Float3,"a_Normal"},
		{Hypo::ShaderDataType::Float2,"a_TexCoord"},
		});

	auto indexBuffer = Hypo::IndexBuffer::Create(gsl::span<Hypo::ElementIndex>(indices));

	auto vertexArray = Hypo::VertexArray::Create();
	vertexArray->SetIndexBuffer(indexBuffer);
	vertexArray->AddVertexBuffer(vertexBuffer, meshShader);
	
	// settings
	Hypo::Vec4F color = Hypo::Vec4F(1, 0, 0, 1);
	float xOffset = 0.f;
	float xOffset2 = 0.f;
	float xOffset3 = 0.f;

	Hypo::SimpleModel model(Hypo::MeshFactory::CreateUVSphere(Hypo::VertexPosTexNorm, 20, 20, 2.f), meshShader, wallTexture);
	

	float innerRadius = 0.3;
	float outerRadius = 1;
	Hypo::Vec4F innerColor = Hypo::Vec4F(1, 0, 1, 1);
	Hypo::Vec4F outerColor = Hypo::Vec4F(1, 0, 0, 1);


	Hypo::Vec3F rotation = {glm::pi<float>() / 2,0,0};

	auto lightBuffer = Hypo::UniformBuffer::Create(Hypo::UniformBinderManager::GetUniformBinder("Light"));
	
	window->EnableImGui();
	bool running = true;
	while (running)
	{
		Hypo::Event event;
		while (window->PollEvent(event))
		{
			if (event.type == Hypo::EventType::WindowClose)
			{
				running = false;
			}
		}
		if (!running)
		{
			break;
		}
		//Update
		camera.Update(1.f / 60.f);


		//Rendering
		Hypo::RenderCommand::SetClearColor({ 0.5,0,0,1 });
		Hypo::RenderCommand::Clear(Hypo::RendererAPI::CLEAR_COLOR | Hypo::RendererAPI::CLEAR_DEPTH);

		
		Hypo::Renderer::BeginScene(&camera);
		/*
		window->GetGraphicsContext()->ResetState();
		window->GetGraphicsContext()->EnableCullFace(Hypo::CullFace::Back);
		window->GetGraphicsContext()->EnableDepthTest(true);
	
		Hypo::Renderer::m_SetupData->m_MeshShader->BindTexture(forestTexture, "texture1");
		Hypo::Renderer::RenderCube({ 0,2,0 }, { 1,1,1 }, { 1,0,1,1 });

		auto sphereTransform = Hypo::Transform::CreateTransform({ 2,1,2 }, { 1,1,1 }, rotation, { 0,0,0 });
		Hypo::Renderer::Submit(Hypo::Renderer::m_SetupData->m_MeshShader, sphereTransform, mesh2);
		window->GetGraphicsContext()->ResetState();
		window->GetGraphicsContext()->EnableCullFace(Hypo::CullFace::Disabled);
		window->GetGraphicsContext()->EnableDepthTest(true);
		*/
		auto transform = Hypo::Transform::CreateTransform({0,0,0},{4,4,4}, rotation, {0,0,0});
		 
		Hypo::Renderer::m_SetupData->m_MeshShader->BindTexture(wallTexture, "texture1");
		lightBuffer->Set("color", Hypo::Vec3F{ 0.5,1,1 });
		lightBuffer->Set("position", Hypo::Vec3F{ 2,2,2 });

		
			auto& planeShader = Hypo::Renderer::m_SetupData->m_MeshShader;
		
		planeShader->BindUniformBuffer(lightBuffer);

		Hypo::Renderer::m_ActiveSceneData->m_TransformUniforms->Set("u_ViewPos", camera.GetPosition());
		Hypo::Renderer::Submit(planeShader, transform, vertexArray);

		//model.Rotate(Hypo::Vec3F{ 0.1f,0.1f,0.f, });
		
		//Hypo::Renderer::Submit(model);

		
		Hypo::Renderer::EndScene();


		
		window->BeginImGui();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Begin("Color");
	
		ImGui::DragFloat3("Rotation", (float*)&rotation, 3.14f / 8.f, -3.14, 3.14);
		
		ImGui::End();

		ImGui::Begin("Spheres");
		ImGui::DragFloat("RadiusInner", &innerRadius, 0.005, 0, outerRadius);
		ImGui::DragFloat("RadiusOuter", &outerRadius, 0.005, 0, innerRadius);
		ImGui::ColorPicker4("ColorInner", reinterpret_cast<float*>(&innerColor));
		ImGui::ColorPicker4("ColorOuter", reinterpret_cast<float*>(&outerColor));
		ImGui::End();
		
		
		
		window->EndImGui();

		window->Display();
	}
	window->DisableImGui();

	
	Hypo::Log::Shutdown();
	return 0;

}
