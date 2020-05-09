#include "Hypo/Hypo.h"
#include <Hypo/Window/Input.h>
#include <iostream>
#include <Hypo/Network/Socket/TcpSocket.h>
#include "Hypo/Window/Window.h"

struct Ip
{
	union 
	{
		struct
		{

			Hypo::uInt8 b1;
			Hypo::uInt8 b2;
			Hypo::uInt8 b3;
			Hypo::uInt8 b4;
		};
		Hypo::uInt32 ip;
	};
};

int main()
{
	Ip ip;
	ip.b1 = 127;
	ip.b2 = 0;
	ip.b3 = 0;
	ip.b4 = 1;
	/*
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> server;
	} while (server == sf::IpAddress::None);
	*/
	// Create a socket for communicating with the server
	Hypo::TcpSocket socket;

	// Connect to the server
	if (socket.Connect(ip.ip, 9977, 0) != Hypo::Socket::Done)
		return -1;
	std::cout << "Connected to server " << ip.ip << std::endl;


	// Send an answer to the server
	const char out[] = "Hi, I'm a client";
	if (socket.Send(out, sizeof(out)) != Hypo::Socket::Done)
		return -1;
	std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;

	// Receive a message from the server
	char in[128];
	std::size_t received;
	if (socket.Receive(in, sizeof(in), received) != Hypo::Socket::Done)
		return -1;
	std::cout << "Message received from the server: \"" << in << "\"" << std::endl;
	return 0;
}
