//#include "Hypo/Hypo.h"
//#include <Hypo/Window/Input.h>
//#include <iostream>
//#include <Hypo/Network/Socket/TcpSocket.h>
//#include "Hypo/Window/Window.h"
//
//#include <thread>
//#include <conio.h>
//#include "Hypo/Network/Socket/ServerSocket.h"
//#include "Hypo/Network/TcpServer/TcpServer.h"
//#include "Hypo/System/Streams/BinaryWriter.h"
//
//#include <sstream>
//#include "Hypo/System/Streams/BinaryReader.h"
//
//#include "Packet.h"
//
//class EchoServerConnection : public Hypo::TcpServerConnection
//{
//public:
//	EchoServerConnection(Hypo::TcpSocket& socket, Hypo::TcpServer& server)
//		: TcpServerConnection(socket), m_Server(server), m_Stream(&socket)
//	{
//		std::cout << "New connection" << std::endl;
//
//	}
//
//	void OnReadable() override
//	{
//		char* buf[1024];
//		auto received = m_Socket.Receive(buf, sizeof(buf));
//
//		for(auto& conn : m_Server.GetConnections())
//		{
//			m_Stream->Send(buf, received);
//		}
//
//		std::cout << "Client: " << m_Socket.GetLocalPort() << " sent: " << std::string(reinterpret_cast<const char*>(buf), received) << std::endl << std::endl;
//	}
//	void OnDisconnect() override
//	{
//		std::cout << "Client disconnecting" << std::endl;
//	}
//	void OnShutdown() override
//	{
//		std::cout << "Server shutting down" << std::endl;
//		m_Socket.Disconnect();
//	}
//private:
//	Hypo::SendStream* m_Stream;
//	Hypo::TcpServer& m_Server;
//};
//
//class EchoServerFactory : public Hypo::TcpServerFactory
//{
//public:
//	Hypo::TcpServerConnection* Handle(Hypo::TcpSocket& socket, Hypo::TcpServer& server) override
//	{
//		return new EchoServerConnection(socket, server);
//	}
//};
//
//int main()
//{
//	std::cout << "Starting server" << std::endl;
//
//
//
//	SendChatMessagePacket packet;
//	packet.name = "Hello";
//
//	Hypo::Buffer<char> buf(200);
//	Hypo::MemoryBinaryWriter writer1(buf);
//
//	writer1 << "Hello this is me";
//
//	Hypo::MemoryBinaryReader reader1(buf);
//
//	std::string text;
//	reader1 >> text;
//	std::cout << text;
//
//
//
//	std::stringstream stream;
//	
//	std::ostream& output(stream);
//
//
//	Hypo::BinaryWriter writer(stream);
//
//	writer << &packet;
//
//	//Read
//	Hypo::BinaryReader reader(stream);
//	SendChatMessagePacket packet2;
//	Hypo::uInt32 packetId, packetSize;
//
//	reader >> packetId >> packetSize;
//
//	packet2.Read(reader);
//
//
//
// 	Hypo::TcpServer server(new EchoServerFactory, "localhost", 12345);
//	server.Run();
//	return 0;
//}
