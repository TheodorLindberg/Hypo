#include "Hypo/Hypo.h"
#include "Hypo/Config.h"
#include "imgui.h"
#include "Hypo/System/Util/Log.h"
#include "Hypo/Window/Window.h"


#include <iostream>
#include "Hypo/3D/Renderer/Renderer.h"
#include "serial/serial.h"
#include <glm/ext/scalar_constants.inl>

struct SensorInputData
{
	unsigned char id;
	unsigned short angle;
	unsigned short distance;
};

std::vector<SensorInputData> ReadSensorInput(serial::Serial& serial)
{
	std::vector<SensorInputData> readings;
	while(serial.available())
	{
		Hypo::uInt8 messageStart = 0;
		serial.read(&messageStart, 1);

		if (messageStart == 0x1E)
		{
			Hypo::uInt16 messageSize = 0;
			serial.read(reinterpret_cast<Hypo::uInt8*>(&messageSize), 2);

			//We have an incomming message
			if (messageSize)
			{
				Hypo::uInt8* data = new Hypo::uInt8[messageSize];
				serial.read(data, messageSize);


				Hypo::uInt8 commandType = data[0];

				Hypo::uInt8* commandData = &data[1];

				switch (commandType)
				{
				case 4:
				{
					struct SensorReadingPacket
					{
						unsigned short sensorId;
						unsigned short sensorAngle;
						unsigned short sensorDistance;
						unsigned short padding;
					};
					SensorReadingPacket packet = { 0 };
					memcpy(&packet, commandData, sizeof(SensorReadingPacket));
					std::cout << "Sensor: " << packet.sensorId << " Angle: " << packet.sensorAngle << " Distance: " << packet.sensorDistance << std::endl;
					readings.push_back(SensorInputData{(unsigned char)packet.sensorId, packet.sensorAngle, packet.sensorDistance});
					break;
				}

				case 123:



					char message[16];

					memcpy(message, commandData, 16);

					message[10] = 'x';

				default:
					break;
				}
				delete data;

			}
		}
		Sleep(2);
	}
	return std::move(readings);
}

int main()
{
	Hypo::Log::Init();
	Hypo::Window* window = Hypo::Window::Create();
	Hypo::init(window->GetGladProc());
	Hypo::InitRenderer(window->GetGladProc());

	auto ports = serial::list_ports();


	serial::Serial arduino("COM4", 9600);
	if(!arduino.isOpen())
	{
		std::cout << "Error connecting" << std::endl;
	} 
	else
	{
		arduino.flush();
		
	}


	static constexpr int gridWidth = 450;
	static constexpr int gridHeight= 450;

	static constexpr float gridColumnWidth = 2.f;
	static constexpr float gridColumnHeight= 2.f;

	Hypo::uInt32 gridData[gridHeight][gridWidth];
	
	window->EnableImGui();
	bool running = true;

	std::unordered_map<unsigned char, unsigned short> distanceSensor1;

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

		

		Hypo::RenderCommand::SetClearColor({ 0.5,0,0,1 });
		Hypo::RenderCommand::Clear(Hypo::RendererAPI::CLEAR_COLOR | Hypo::RendererAPI::CLEAR_DEPTH);
		//Update

		auto updates = ReadSensorInput(arduino);
		for (auto& data : updates)
		{
			distanceSensor1[data.angle] = data.distance;
		}
		window->BeginImGui();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Begin("Sensor1Input", NULL, ImGuiWindowFlags_NoScrollbar);

		const ImVec2 p = ImGui::GetCursorScreenPos();
		Hypo::Vec2F center = Hypo::Vec2F{ p.x + 250, p.y + 300 };
		memset(gridData, 0, sizeof(gridData));
		for(auto it = distanceSensor1.begin(); it != distanceSensor1.end(); ++it) 
		{
			float angle = it->first;
			float distance = it->second;


			if (distance == 0)
				distance = 200;
			if (distance > 200)
				distance = 200;
			auto* list = ImGui::GetWindowDrawList();

			Hypo::Vec2F angleVector = { glm::cos(angle / 180.f * glm::pi<float>()), glm::sin(-angle / 180.f * glm::pi<float>()) };


			auto end = (center + angleVector * 210);
			list->AddLine({ center.x, center.y }, {end.x, end.y}, 0xFF0000FF, 1);


			auto reading = (center + angleVector * distance);
			list->AddLine({ center.x, center.y }, { reading.x, reading.y }, 0xFF00FFFF, 1);

			auto middle = (center + angleVector * 5);
			list->AddLine({ center.x, center.y }, { middle.x, middle.y }, 0xFF300000, 1);


			auto gridPosition = angleVector * distance + Hypo::Vec2F{ 225,225 };
			gridData[(int)gridPosition.x][(int)gridPosition.y] = 0xFFFFFFFF;
		}


		ImGui::End();

		ImGui::Begin("Grid", NULL,ImGuiWindowFlags_NoScrollbar);
		
		//int height = ImGui::GetContentRegionAvail().y;
		//int width = ImGui::GetContentRegionAvail().x;

		for(int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				const ImVec2 p = ImGui::GetCursorScreenPos();
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				unsigned int color = gridData[y][x] | 0xFF000000;

				ImVec2 a = ImVec2{ p.x + x * gridColumnWidth, p.y + y * gridColumnHeight };
				ImVec2 b = ImVec2{ p.x + x * gridColumnWidth + gridColumnWidth, p.y + y * gridColumnHeight + gridColumnHeight };

				draw_list->AddRectFilled(a,b, color);

			}
		}

		ImGui::End();



		window->EndImGui();


		window->Display();
	}
	window->DisableImGui();


	Hypo::Log::Shutdown();
	return 0;

}
