#include "networkpch.h"
#include "TcpSocket.h"
#include "TcpSocketImpl.h"
#include "Hypo/System/Core/Exception.h"

namespace Hypo
{
	TcpSocket::TcpSocket()
		: Socket(new TcpSocketImpl())
	{
	}

	TcpSocket::TcpSocket(SocketImpl* impl)
		: Socket(impl)
	{
		if (!dynamic_cast<TcpSocketImpl*>(Impl()))
			throw InvalidArgumentException("Cannot create socket with incompatible socket");
	}

	TcpSocket::TcpSocket(IpAddress& address, unsigned short port)
		: Socket(new TcpSocketImpl())
	{
		Connect(address, port);
	}

	TcpSocket::TcpSocket(const TcpSocket& socket)
		: Socket(socket)
	{
		if (!dynamic_cast<TcpSocketImpl*>(Impl()))
			throw InvalidArgumentException("Cannot assign incompatible socket");
	}

	TcpSocket::~TcpSocket()
	{
	}

	TcpSocket& TcpSocket::operator=(const Socket& socket)
	{
		if (dynamic_cast<TcpSocketImpl*>(socket.Impl()))
			Socket::operator = (socket);
		else
			throw InvalidArgumentException("Cannot assign incompatible socket");
		return *this;
	}

	void TcpSocket::Connect(IpAddress& address, unsigned short port)
	{
		Impl()->Connect(address, port);
	}

	void TcpSocket::Disconnect()
	{
		Close();
	}

	int TcpSocket::Available()
	{
		return Impl()->Available();
	}

	int TcpSocket::Receive(void* data, int size)
	{
		return Impl()->Receive(data, size);
	}

	int TcpSocket::Send(const void* data, int size)
	{
		return Impl()->Send(data, size);
	}
}
