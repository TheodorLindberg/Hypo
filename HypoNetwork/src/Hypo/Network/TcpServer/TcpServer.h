#pragma once
#include <Hypo/Network/Socket/ServerSocket.h>
#include <Hypo/Network/TcpServer/TcpServerFactory.h>
#include <Hypo/Network/TcpServer/TcpServerConnection.h>


namespace Hypo
{
	class HYPO_NETWORK_API TcpServer
	{
	public:
		using ConnectionList = std::vector<TcpServerConnection*>;
		TcpServer();
		TcpServer(TcpServerFactory::Ptr factory, ServerSocket socket);
		TcpServer(TcpServerFactory::Ptr factory, uInt16 port, int backlog = 64);
		TcpServer(TcpServerFactory::Ptr factory, const IpAddress& address, uInt16 port, int backlog = 64);
		~TcpServer();

		void Init(const IpAddress& address, uInt16 port, int backlog = 64);

		void Run();

		void Stop();
		ConnectionList& GetConnections() { return m_Connections;  }
	private:
		volatile bool m_Running;
		ServerSocket m_ServerSocket; 
		TcpServerFactory::Ptr m_Factory;

		ConnectionList m_Connections;
	};
}