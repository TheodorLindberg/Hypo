#pragma once
#include <Hypo/Network/Export.h>
#include <Hypo/Network/Socket/SocketImpl.h>

namespace Hypo
{
	class TcpSocketImpl : public SocketImpl
	{
	public:
		TcpSocketImpl() = default;
		TcpSocketImpl(hypo_socket_t socket);
		~TcpSocketImpl() = default;
	private:
	};

}
