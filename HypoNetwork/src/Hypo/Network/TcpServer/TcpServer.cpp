#include "networkpch.h"
#include "TcpServer.h"
#include "Hypo/System/Core/Exception.h"

namespace Hypo
{
	TcpServer::TcpServer()
		: m_Running(true)
	{
	}

	TcpServer::TcpServer(TcpServerFactory::Ptr factory, ServerSocket socket)
		: m_Running(true), m_ServerSocket(socket), m_Factory(factory)
	{
		if (!m_ServerSocket.Valid())
			throw InvalidArgumentException("Invalid server socket passed to TcpServer");
	}

	TcpServer::TcpServer(TcpServerFactory::Ptr factory, uInt16 port, int backlog)
		: m_ServerSocket(port, backlog), m_Running(true), m_Factory(factory)
	{}

	TcpServer::TcpServer(TcpServerFactory::Ptr factory, const IpAddress& address, uInt16 port, int backlog)
		: m_Running(true), m_ServerSocket(port, backlog), m_Factory(factory)
	{}

	TcpServer::~TcpServer()
	{
		for(auto* conn : m_Connections)
		{
			conn->OnShutdown();
			delete conn;
		}
	}

	void TcpServer::Init(const IpAddress& address, uInt16 port, int backlog)
	{
		m_ServerSocket = ServerSocket(port, backlog);
	}

	void TcpServer::Run()
	{
		if (!m_ServerSocket.Valid())
			throw IllegalStateException("Attempting to run TcpServer with invalid server socket");

		Socket::SocketList read;
		Socket::SocketList write;
		Socket::SocketList except;

		while(m_Running)
		{
			for(auto& conn : m_Connections)
			{
				read.push_back(conn->GetSocket());
			}
			read.push_back(m_ServerSocket);
			if(Socket::Select(read, write,except, Hypo::Milliseconds(10)))
			{
				for(auto& sock : read)
				{
					if(sock == m_ServerSocket)
					{
						auto newConnection = m_ServerSocket.Accept();
						m_Connections.push_back(m_Factory->Handle(newConnection, *this));

					} 
					else
					{
						for(ConnectionList::iterator it = m_Connections.begin(); it != m_Connections.end(); ++it)
						{
							auto conn = (*it);
							if(sock == conn->GetSocket())
							{
								if(sock.Available() == 0)
								{
									conn->OnDisconnect();
									delete conn;
									it = m_Connections.erase(it);
									if (it == m_Connections.end()) break;
								} 
								else
								{
									conn->OnReadable();
								}
							}
						}
					}
				}
			}
			read.clear();
		}
	}

	void TcpServer::Stop()
	{
		m_Running = false;
	}
}
