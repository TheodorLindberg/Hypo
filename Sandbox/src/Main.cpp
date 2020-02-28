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


int main()
{
	Hypo::Log::Init();
	Hypo::Window* window = Hypo::Window::Create();
	

	Hypo::init(window->GetGladProc());
	const int status = gladLoadGLLoader((GLADloadproc)window->GetGladProc());

	
	HYPO_CORE_ASSERT(status, "Failed to initialize Glad!");

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
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	auto vertexBuffer = Hypo::VertexBuffer::Create(gsl::span<float>(vertices), false);

	
	auto indexBuffer = Hypo::IndexBuffer::Create(gsl::span<Hypo::ElementIndex>(indices), false);
	
	glBindVertexArray(VAO);

	vertexBuffer->Bind();
	indexBuffer->Bind();

	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	
	// settings
	float innerRadius = (float)0.3;
	float outerRadius = 1;
	Hypo::Vec4F innerColor = Hypo::Vec4F(1, 0, 1, 1);
	Hypo::Vec4F outerColor = Hypo::Vec4F(1, 0, 0, 1);

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
		
		window->BeginImGui();
		
		window->EndImGui();
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		window->Display();
	}
	window->DisableImGui();

	
	Hypo::Log::Shutdown();
	return 0;

}
