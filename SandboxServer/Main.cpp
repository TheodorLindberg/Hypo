#include <iostream>
#include "Hypo/Network/Socket/TcpSocket.h"
#include "Hypo/Window/Window.h"
#include "Hypo/3D/Renderer/Renderer.h"
#include "Hypo/System/Util/Log.h"

enum class ConnectionStatus
{
	Disconnected =0,
	Connected,
	Connecting,
	Disconnecting
};

int main()
{
	std::cout << "start";
	Hypo::Log::Init();
	std::cout << "log";
	auto* window = Hypo::Window::Create(Hypo::WindowProps("ChatClient"));
	std::cout << "window";
	Hypo::init(window->GetGladProc());
	std::cout << "init";
	Hypo::InitRenderer(window->GetGladProc());
	std::cout << "renderer";

	window->EnableImGui();
	std::cout << "imgui   ";
	std::cout << "init";

	char ipAddress[14] = "localhost";
	int port = 12345;
	char message[128] = {0};
	char name[32] = { 0 };

	ConnectionStatus status = ConnectionStatus::Disconnected;
	std::string username;
	std::vector<std::string> messages;
	Hypo::TcpSocket client;

	while(true)
	{
		Hypo::Event e;
		while(window->PollEvent(e))
		{
			if (e.type == Hypo::EventType::WindowClose)
				return 0;
		}

		if(status == ConnectionStatus::Connected  && client.Available())
		{
			int available = client.Available();
			if (available)
			{
				char* buf = new char[available];
				int received = client.Receive(buf, available);
				messages.push_back(std::string(buf, received));

			}
		}

		Hypo::RenderCommand::SetClearColor({ 0.5,0,0,1 });
		Hypo::RenderCommand::Clear(Hypo::RendererAPI::CLEAR_COLOR | Hypo::RendererAPI::CLEAR_DEPTH);

		window->BeginImGui();

		ImGui::Begin("Chat");
		ImGui::TextUnformatted("IP");
		ImGui::SameLine();
		ImGui::InputText("", ipAddress, sizeof(ipAddress));
		ImGui::InputInt("Port", &port);

		ImGui::SameLine();
		if (status == ConnectionStatus::Disconnected)
		{
			if(ImGui::Button("Connect"))
			{
				Hypo::IpAddress addr(ipAddress);
				if(addr.Valid())
				{
					client.Connect(addr, port);
					status = ConnectionStatus::Connected;
				}
			}
		}
		else
		{
			if(ImGui::Button("Disconnect"))
			{
				client.Disconnect();
				status = ConnectionStatus::Disconnected;
			}
		}

		ImGui::InputText("Name", name, sizeof(name));
		ImGui::SameLine();
		if (ImGui::Button("Set"))
		{
			int len = std::strlen(name);
			if (len > 0)
			{
				username = std::string(name, len);
			}

		}


		ImGui::BeginChild("Chat", ImVec2(300,150), true);

		for(auto& message : messages)
		{
			ImGui::Text(message.c_str());
			
		}
		ImGui::EndChild();


		ImGui::TextUnformatted("Message");
		ImGui::SameLine();
		ImGui::InputText("Message", message, sizeof(message));
		ImGui::SameLine();
		if(ImGui::Button("Send"))
		{
			int len = std::strlen(message);
			if(len > 0)
			{
				std::string msg = username + ": " + std::string(message, len);
				client.Send(msg.c_str(), msg.size());
			}
			
		}
		ImGui::End();


		static bool open = true;
		ImGui::ShowDemoWindow(&open);
		window->EndImGui();

		window->Display();
	}
	return 0; 
}
