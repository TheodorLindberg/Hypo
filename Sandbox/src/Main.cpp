#include "Hypo/Hypo.h"
#include "Hypo/Util/Log.h"
#include "Hypo/Config.h"
#include "Hypo/Events/Event.h"
#include "Hypo/Window.h"
#include "imgui.h"

int main()
{
	Hypo::Log::Init();


	float innerRadius = (float)0.3;
	float outerRadius = 1;
	Hypo::Vec4F innerColor = Hypo::Vec4F(1, 0, 1, 1);
	Hypo::Vec4F outerColor = Hypo::Vec4F(1, 0, 0, 1);

	Hypo::Window* window = Hypo::Window::Create();
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
		/*static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Begin("Spheres");
		ImGui::DragFloat("RadiusInner", &innerRadius, 0.005, 0, outerRadius);
		ImGui::DragFloat("RadiusOuter", &outerRadius, 0.005, 0, innerRadius);
		ImGui::ColorPicker4("ColorInner", reinterpret_cast<float*>(&innerColor));
		ImGui::ColorPicker4("ColorOuter", reinterpret_cast<float*>(&outerColor));
		ImGui::End();*/
		window->EndImGui();

		window->Display();
	}
	window->DisableImGui();
	Hypo::Log::Shutdown();
	delete window;
	return 0;

}
