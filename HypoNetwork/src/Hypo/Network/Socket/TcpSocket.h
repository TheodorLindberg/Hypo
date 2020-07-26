#pragma once
#include "Socket.h"
#include "Hypo/System/Streams/SendStream.h"

namespace Hypo
{
	class HYPO_NETWORK_API TcpSocket : public Socket, public SendStream
	{
	public:
		TcpSocket();
		TcpSocket(SocketImpl* impl);
		TcpSocket(IpAddress& address, unsigned short port);

		TcpSocket(const TcpSocket& socket);


		virtual ~TcpSocket();

		TcpSocket& operator = (const Socket& socket);

		void Connect(IpAddress& address, unsigned short port);

		void Disconnect();
		
		int Available();

		int Receive(void* data, int size);
		int Send(const void* data, int size) override;
	private:
	};
}
