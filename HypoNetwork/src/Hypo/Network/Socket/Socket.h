#pragma once
#include "Hypo/Network/Export.h"
#include "Hypo/Network/Socket/SocketHandle.h"



#include <Hypo/Core.h>


namespace Hypo
{
	class HYPO_NETWORK_API Socket
	{
	public:
		enum Status
		{
			Done,
			Error,
			Disconnected,
			NotReady,
			Partial
		};
		enum
		{
			AnyPort = 0
		};
	public:
		virtual ~Socket();

		void SetBlocking(bool blocking);
		bool IsBlocking() const;

	protected:
		enum Type
		{
			TCP,
			UDP
		};
		Socket(Type type);

		SocketHandle GetHandle() const;

		void Create();

		void Create(SocketHandle handle);

		void Close();
		
	private:
		Type m_Type;
		SocketHandle m_Socket;
		bool m_IsBlocking;

	};



}
