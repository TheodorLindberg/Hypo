#pragma once
#include "Hypo/Network/Socket/Socket.h"



#include <winsock2.h>

namespace Hypo
{
	class HYPO_NETWORK_API SocketImpl
	{
	public:
		typedef int AddrLength;
		static sockaddr_in CreateAddress(uInt32 adress, unsigned short port);
		static SocketHandle InvalidSocket();
		static void Close(SocketHandle socket);

		static void SetBlocking(SocketHandle socket, bool block);
		static Socket::Status GetErrorStatus();
	};
}