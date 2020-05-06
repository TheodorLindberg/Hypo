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
#include "Hypo/3D/Asset/AssetManager.h"
#include "Hypo/3D/Asset/Light.h"
#include "Hypo/Graphics/NestedBufferLayout.h"


namespace Hypo {
	class ThridPersonKeyboardCamera;
}

int main()
{
	Hypo::Log::Init();
	Hypo::Window* window = Hypo::Window::Create();
	Hypo::init(window->GetGladProc());
	Hypo::InitRenderer(window->GetGladProc());
	
	//auto shaderData = Hypo::ShaderFromFile("res\\shaders\\simple.glsl");
	//auto shader = Hypo::Shader::Create(shaderData);



	//shader->Bind();

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

	
	//auto wallTexture = Hypo::Texture2D::Create(Hypo::TextureFromFile("res\\textures\\wall.jpg"));
	//auto forestTexture = Hypo::Texture2D::Create(Hypo::TextureFromFile("res\\textures\\references-outerra2.jpg"));

	auto wallTexture = Hypo::AssetManager::RetrieveTexture2DAsset("brick_wall","res\\textures\\wall.jpg" );
	auto forestTexture = Hypo::AssetManager::RetrieveTexture2DAsset("forrest", "res\\textures\\references-outerra2.jpg");

	Hypo::ThridPersonKeyboardCamera camera;

	auto mesh2 = Hypo::MeshFactory::CreateUVSphere(Hypo::VertexPosTex, 20, 20, 0.5f);
	
	camera.SetViewRect({ Hypo::RectFromSize<float>(0,0,static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight())) });
	camera.SetPosition({ -5,2, 0 });

	window->SetVSync(true);


	auto meshShaderData = Hypo::ShaderFromFile("res\\shaders\\lightShader.glsl");
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

	std::vector<Hypo::Vec3F> lightPositions = {
		{1.2f,1.1f,2.2f},
		{-3.f,1.5f,-3.1f},
		{3.4f,3.2f,-1.3f},
		{5.7f,2.1f,2.2f},
		{-2.1f,1.4f,-2.5f}
	};

	Hypo::SceneLights lights;
	for(int i = 0; i < 5; i++)
	{
		Hypo::PointLight light;
		light.Position = lightPositions[i];

		lights.PointLights.push_back(light);
	}


	auto cube = Hypo::MeshFactory::CreateCube(Hypo::VertexPosTex);

	float innerRadius = 0.3;
	float outerRadius = 1;
	Hypo::Vec4F innerColor = Hypo::Vec4F(1, 0, 1, 1);
	Hypo::Vec4F outerColor = Hypo::Vec4F(1, 0, 0, 1);


	Hypo::Vec3F rotation = {glm::pi<float>() / 2,0,0};

	
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

		
		Hypo::Renderer::BeginScene(&camera, lights);
		
		window->GetGraphicsContext()->ResetState();
		window->GetGraphicsContext()->EnableCullFace(Hypo::CullFace::Back);
		window->GetGraphicsContext()->EnableDepthTest(true);


		auto transform = Hypo::Transform::CreateTransform({0,0,0},{4,4,4}, rotation, {0,0,0});
		
		
		auto& planeShader = Hypo::Renderer::GetSceneRendererData()->m_MeshShader;
		
		
		Hypo::Renderer::Submit(planeShader, transform, vertexArray);

		//model.Rotate(Hypo::Vec3F{ 0.1f,0.1f,0.f, });
		auto cubeTransform = Hypo::Transform::CreateTransform({ 0,3,0 }, { 0.2,0.5,1 }, {0,0,0}, { 0,0,0 });
		
		Hypo::Renderer::Submit(Hypo::AssetManager::RetrieveShaderAsset("simpleMeshShader", "res\\shaders\\simpleMeshShader.glsl"), cubeTransform, cube, wallTexture, "texture1");

		/*for(auto& light : lights.PointLights)
		{

			Hypo::Renderer::RenderCube(light.Position, { 0.1,0.1,0.1 }, {1.f,0.5f,1.f, 1.f});
		}*/

		for(int i = 0;  i < 5; i++)
		{
			Hypo::Renderer::RenderCube(lights.PointLights[i].Position, { 0.1,0.1,0.1 }, { 1.f,0.5f,1.f, 1.f });
		}
		
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
