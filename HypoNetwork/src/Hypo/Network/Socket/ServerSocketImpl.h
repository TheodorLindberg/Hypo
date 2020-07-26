#pragma once
#include "Hypo/Network/Socket/SocketImpl.h"

namespace Hypo
{
	class ServerSocketImpl : public SocketImpl
	{
	public:
		ServerSocketImpl() = default;
		~ServerSocketImpl() = default;
	};
}