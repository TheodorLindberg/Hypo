#pragma once
#include <memory>
#include "Hypo/System/DataTypes/ObjPtr.h"
#include <Hypo/Network/Socket/SocketDefs.h>
#include <Hypo/Network/IpAddress.h>

namespace Hypo
{

	class HYPO_NETWORK_API  SocketImpl : public RefCountedObject
	{
	public:
		SocketImpl() = default;
		SocketImpl(hypo_socket_t impl);


		virtual void Connect(IpAddress& address, uInt16 port);

		virtual void Bind(const IpAddress& address, uInt16 port);
		virtual void Listen( int backlog = 64);

		virtual SocketImpl* Accept();
		virtual SocketImpl* Accept(IpAddress& address, uInt16& port);

		int Available();

		virtual int Send(const void* data, int size);
		virtual int Receive(void* data, int size);

		void SetBlocking(bool block);
		bool GetBlocking() const { return m_IsBlocking; }

		void Close();

		bool Valid() const;

		static int LastError();




		static void Error();
		static void Error(int code);
		static void Error(int code, const std::string& arg);

		hypo_socket_t SockFD() const { return m_SocketFD;  }
	protected:

		virtual void Init(int af);
		virtual void InitSocket(int af, int type, int proto = 0);

		bool CheckResult(int rc);
		bool CheckResult(int rc, const std::string& arg);
	private:
		

		hypo_socket_t m_SocketFD = INVALID_SOCKET;
		bool m_IsBlocking;

	};

}
