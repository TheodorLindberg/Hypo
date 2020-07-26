#pragma once
#include "TcpServerConnection.h"

namespace Hypo
{
	class TcpServerFactory
	{
	public:
		using Ptr = ObjPtr<TcpServerFactory>;

		virtual ~TcpServerFactory() = default;
		virtual TcpServerConnection* Handle(class TcpSocket& socket,class TcpServer& server) = 0;
	};
}
