#include "Hypo/Hypo.h"
#include "Hypo/Config.h"
#include "imgui.h"
#include "Hypo/System/Util/Log.h"
#include "Hypo/Window/Window.h"
#include "glad/glad.h"
#include <iostream>

#include "Hypo/Graphics/Buffers.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Hypo/Graphics/Shader/UniformBinder.h"


int main()
{
	Hypo::Log::Init();
	Hypo::Window* window = Hypo::Window::Create();

	Hypo::init(window->GetGladProc());
	const int status = gladLoadGLLoader((GLADloadproc)window->GetGladProc());

	
	HYPO_CORE_ASSERT(status, "Failed to initialize Glad!");


	auto defaultShaderData = Hypo::ShaderFromFile("res\\shaders\\default.glsl");
	auto defaultShader = Hypo::Shader::Create(defaultShaderData);
	
	auto shaderData = Hypo::ShaderFromFile("res\\shaders\\simple.glsl");
	auto shader = Hypo::Shader::Create(shaderData);
	shader->Bind();
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	Hypo::ElementIndex indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	auto colorBinder = Hypo::UniformBinderManager::GetUniformBinder("Color");

	auto colorBuffer = Hypo::UniformBuffer::Create(colorBinder);

	colorBuffer->Set("color", Hypo::Vec4F(0.1f, 0.f, 0.5f, 1.f));

	shader->BindUniformBuffer(colorBuffer);
	

	auto vertexBuffer = Hypo::VertexBuffer::Create(gsl::span<float>(vertices), false);
	vertexBuffer->SetLayout(Hypo::BufferLayout{
		{Hypo::ShaderDataType::Float3,"aPos"}
	});

	
	auto indexBuffer = Hypo::IndexBuffer::Create(gsl::span<Hypo::ElementIndex>(indices), false);


	auto vertexArray = Hypo::VertexArray::Create();
	vertexArray->SetIndexBuffer(indexBuffer);
	vertexArray->AddVertexBuffer(vertexBuffer, shader);
	
	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	
	// settings
	Hypo::Vec4F color = Hypo::Vec4F(1, 0, 0, 1);
	float xOffset = 0.f;
	float xOffset2 = 0.f;
	float xOffset3 = 0.f;

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
			else if (event.type == Hypo::EventType::MouseMoved)
			{

			}
		}
		if (!running)
		{
			break;
		}
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



		// ------
		shader->Bind();
		vertexArray->Bind();
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		window->BeginImGui();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Begin("Color");

		ImGui::ColorPicker4("Color", reinterpret_cast<float*>(&color));
		ImGui::DragFloat("Offset", &xOffset, 0.05f, -1.f, 1.f);
		ImGui::DragFloat("Offset2", &xOffset2, 0.1f, -1.f, 1.f);
		ImGui::DragFloat("Offset3", &xOffset3, 0.1f, -1.f, 1.f);

		colorBuffer->Set("color", color);
		colorBuffer->SetArray("offset", xOffset, 0);
		colorBuffer->SetArray("offset", xOffset2, 1);
		colorBuffer->SetArray("offset", xOffset3, 2);

		ImGui::End();
		window->EndImGui();

		window->Display();
	}
	window->DisableImGui();

	
	Hypo::Log::Shutdown();
	return 0;

}
