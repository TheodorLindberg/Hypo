#include "networkpch.h"
#include "Platform/Windows/WindowsSocketImpl.h"

#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

namespace Hypo
{
	sockaddr_in SocketImpl::CreateAddress(uInt32 adress, unsigned short port)
	{

		sockaddr_in addr;
		std::memset(&addr, 0, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_port = htons(port);
		//addr.sin_addr.s_addr = htonl(adress);
		std::string address = "127.0.0.1";
		inet_pton(AF_INET, address.c_str(), &addr.sin_addr);
		return addr;
	}

	SocketHandle SocketImpl::InvalidSocket()
	{
		return INVALID_SOCKET;
	}

	void SocketImpl::Close(SocketHandle socket)
	{
		closesocket(socket);
	}

	void SocketImpl::SetBlocking(SocketHandle socket, bool block)
	{
		u_long blocking = block ? 0 : 1;
		ioctlsocket(socket, FIONBIO, &blocking);
	}

	Socket::Status SocketImpl::GetErrorStatus()
	{
		switch (WSAGetLastError())
		{
		case WSAEWOULDBLOCK:  return Socket::NotReady;
		case WSAEALREADY:     return Socket::NotReady;
		case WSAECONNABORTED: return Socket::Disconnected;
		case WSAECONNRESET:   return Socket::Disconnected;
		case WSAETIMEDOUT:    return Socket::Disconnected;
		case WSAENETRESET:    return Socket::Disconnected;
		case WSAENOTCONN:     return Socket::Disconnected;
		case WSAEISCONN:      return Socket::Done; // when connecting a non-blocking socket
		default:              return Socket::Error;
		}
	}

	struct SocketInitializer
	{
		SocketInitializer()
		{
			WSADATA init;
			WSAStartup(MAKEWORD(2, 2), &init);
		}

		~SocketInitializer()
		{
			WSACleanup();
		}
	};

	SocketInitializer globalInitializer;
}
