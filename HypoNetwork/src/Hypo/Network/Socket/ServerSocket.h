#pragma once
#include "Socket.h"
#include "TcpSocket.h"

namespace Hypo
{
	class HYPO_NETWORK_API ServerSocket : public Socket
	{
	public:
		ServerSocket();
		ServerSocket(const ServerSocket& socket);
		ServerSocket(uInt16 port, int backlog);

		virtual ~ServerSocket();

		ServerSocket& operator=(const ServerSocket& socket);

		void Bind(uInt16 port);
		void Bind(const IpAddress& address, uInt16 port);
		void Listen(int backlog);
		TcpSocket Accept(IpAddress& address, uInt16 port);
		TcpSocket Accept();

	};
}
