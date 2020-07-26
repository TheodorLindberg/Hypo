#include "networkpch.h"
#include "ServerSocket.h"
#include "ServerSocketImpl.h"
#include "Hypo/System/Core/Exception.h"


namespace Hypo
{
	ServerSocket::ServerSocket()
		: Socket(new ServerSocketImpl())
	{
	}

	ServerSocket::ServerSocket(const ServerSocket& socket)
		: Socket(socket)
	{
		if (!dynamic_cast<ServerSocketImpl*>(Impl()))
			throw InvalidArgumentException("Cannot assign incompatible socket");
	}

	ServerSocket::ServerSocket(uInt16 port, int backlog)
		: Socket(new ServerSocketImpl())
	{
		Bind(port);
		Listen(backlog);
	}

	ServerSocket::~ServerSocket()
	{
	}

	ServerSocket& ServerSocket::operator=(const ServerSocket& socket)
	{
		if (dynamic_cast<ServerSocketImpl*>(socket.Impl()))
			Socket::operator = (socket);
		else
			throw InvalidArgumentException("Cannot assign incompatible socket");
		return *this;
	}

	void ServerSocket::Bind(uInt16 port)
	{
		Bind(IpAddress::Any, port);
	}

	void ServerSocket::Bind(const IpAddress& address, uInt16 port)
	{
		Impl()->Bind(address, port);
	}

	void ServerSocket::Listen(int backlog)
	{
		Impl()->Listen(backlog);
	}

	TcpSocket ServerSocket::Accept(IpAddress& address, uInt16 port)
	{
		return TcpSocket(Impl()->Accept(address, port));
	}

	TcpSocket ServerSocket::Accept()
	{
		return TcpSocket(Impl()->Accept());
	}
}
