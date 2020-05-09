#pragma once
#include "Hypo/Network/Export.h"
#include "Hypo/Network/Socket/Socket.h"

namespace Hypo
{
	class HYPO_NETWORK_API TcpSocket : public Socket
	{
	public:
		TcpSocket();

		unsigned short GetLocalPort() const;
		uInt32 GetRemoteAddress() const;
		unsigned short GetRemotePort() const;


		Status Connect(const uInt32 remoteAddress, unsigned short remotePort, uInt32 timeout);
		
		void Disconnect();
		
		Status Send(const void* data, std::size_t size);
		Status Send(const void* data, std::size_t size, std::size_t& sent);

		Status Receive(void* data, std::size_t size, std::size_t& received);
	};

	
}
