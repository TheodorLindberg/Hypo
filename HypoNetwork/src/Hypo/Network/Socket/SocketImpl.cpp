#include "networkpch.h"
#include "SocketImpl.h"
#include "Hypo/Network/NetExceptions.h"
#include <spdlog/spdlog.h>
#include "TcpSocketImpl.h"


namespace Hypo
{
	SocketImpl::SocketImpl(hypo_socket_t impl)
		: m_SocketFD(impl)
	{
		if (m_SocketFD == HYPO_INVALID_SOCKET)
			throw Hypo::InvalidSocketException();
	}

	void SocketImpl::Connect(IpAddress& address, uInt16 port)
	{

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(address.ToInteger());
		addr.sin_port = htons(port);
		if (m_SocketFD == HYPO_INVALID_SOCKET)
		{
			Init(AF_INET);
		}

		connect(m_SocketFD, reinterpret_cast<sockaddr*>(&addr), sizeof(addr));
		Error();
	}

	void SocketImpl::Bind(const IpAddress& address, Hypo::uInt16 port)
	{

		if (m_SocketFD == HYPO_INVALID_SOCKET)
		{
			Init(AF_INET);
		}

		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(address.ToInteger());
		addr.sin_port = htons(port);
		CheckResult(bind(m_SocketFD, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)));
	}

	void SocketImpl::Listen(int backlog)
	{
		CheckResult(listen(m_SocketFD, backlog));
	}

	SocketImpl* SocketImpl::Accept()
	{
		hypo_socket_t sd = accept(m_SocketFD, NULL, NULL);
		if(sd != HYPO_INVALID_SOCKET)
		{
			//TODO: Return socket
			return new TcpSocketImpl(sd);
		} 
		else
		{
			Error();
			return nullptr;
		}
	}

	SocketImpl* SocketImpl::Accept(IpAddress& address, uInt16& port)
	{
		sockaddr_storage buffer;
		struct sockaddr* pSA = reinterpret_cast<struct sockaddr*>(&buffer);
		hypo_socklen_t saLen = sizeof(buffer);
		hypo_socket_t sd;
		do
		{
			sd = ::accept(m_SocketFD, pSA, &saLen);
		} while (sd == HYPO_INVALID_SOCKET && LastError() == HYPO_EINTR);
		if (sd != HYPO_INVALID_SOCKET)
		{
			//clientAddr = SocketAddress(pSA, saLen);
			address = pSA->sa_data;
			port =  reinterpret_cast<sockaddr_in*>(pSA)->sin_port;
			return new TcpSocketImpl(sd);
		}
		Error(); // will throw
		return nullptr;
	}

	int SocketImpl::Available()
	{
		int result = 0;
		int rc = ioctlsocket(m_SocketFD, FIONREAD, reinterpret_cast<u_long*>(&result));
		if (rc) Error();
		return result;
	}

	inline int SocketImpl::Send(const void* data, int size)
	{
		int rc = send(m_SocketFD, reinterpret_cast<const char*>(data), size, 0);

		if (rc < 0)Error();
		return rc;
	}

	inline int SocketImpl::Receive(void* data, int size)
	{
		int rc = recv(m_SocketFD, reinterpret_cast<char*>(data), size, 0);

		if (rc < 0)Error();
		return rc;
	}

	void SocketImpl::SetBlocking(bool block)
	{
	}

	void SocketImpl::Close()
	{
		hypo_closesocket(m_SocketFD);
		m_SocketFD = HYPO_INVALID_SOCKET;
	}

	bool SocketImpl::Valid() const
	{
		return m_SocketFD != HYPO_INVALID_SOCKET;
	}

	inline int SocketImpl::LastError()
	{
		return WSAGetLastError();
	}

	void SocketImpl::Error()
	{
		Error(LastError(), "");
	}

	void SocketImpl::Error(int code)
	{
		Error(code, "");
	}

	void SocketImpl::Error(int code, const std::string& arg)
	{
		switch (code)
		{
		case HYPO_ENOERR: return;
		case HYPO_ESYSNOTREADY:
			throw NetException("Net subsystem not ready", code);
		case HYPO_ENOTINIT:
			throw NetException("Net subsystem not initialized", code);
		case HYPO_EINTR:
			throw IOException("Interrupted", code);
		case HYPO_EACCES:
			throw IOException("Permission denied", code);
		case HYPO_EFAULT:
			throw IOException("Bad address", code);
		case HYPO_EINVAL:
			throw InvalidArgumentException(code);
		case HYPO_EMFILE:
			throw IOException("Too many open files", code);
		case HYPO_EWOULDBLOCK:
			throw IOException("Operation would block", code);
		case HYPO_EINPROGRESS:
			throw IOException("Operation now in progress", code);
		case HYPO_EALREADY:
			throw IOException("Operation already in progress", code);
		case HYPO_ENOTSOCK:
			throw IOException("Socket operation attempted on non-socket", code);
		case HYPO_EDESTADDRREQ:
			throw NetException("Destination address required", code);
		case HYPO_EMSGSIZE:
			throw NetException("Message too long", code);
		case HYPO_EPROTOTYPE:
			throw NetException("Wrong protocol type", code);
		case HYPO_ENOPROTOOPT:
			throw NetException("Protocol not available", code);
		case HYPO_EPROTONOSUPPORT:
			throw NetException("Protocol not supported", code);
		case HYPO_ESOCKTNOSUPPORT:
			throw NetException("Socket type not supported", code);
		case HYPO_ENOTSUP:
			throw NetException("Operation not supported", code);
		case HYPO_EPFNOSUPPORT:
			throw NetException("Protocol family not supported", code);
		case HYPO_EAFNOSUPPORT:
			throw NetException("Address family not supported", code);
		case HYPO_EADDRINUSE:
			throw NetException("Address already in use", arg, code);
		case HYPO_EADDRNOTAVAIL:
			throw NetException("Cannot assign requested address", arg, code);
		case HYPO_ENETDOWN:
			throw NetException("Network is down", code);
		case HYPO_ENETUNREACH:
			throw NetException("Network is unreachable", code);
		case HYPO_ENETRESET:
			throw NetException("Network dropped connection on reset", code);
		case HYPO_ECONNABORTED:
			throw ConnectionAbortedException(code);
		case HYPO_ECONNRESET:
			throw ConnectionResetException(code);
		case HYPO_ENOBUFS:
			throw IOException("No buffer space available", code);
		case HYPO_EISCONN:
			throw NetException("Socket is already connected", code);
		case HYPO_ENOTCONN:
			throw NetException("Socket is not connected", code);
		case HYPO_ESHUTDOWN:
			throw NetException("Cannot send after socket shutdown", code);
		case HYPO_ETIMEDOUT:
			throw TimeoutException(code);
		case HYPO_ECONNREFUSED:
			throw ConnectionRefusedException(arg, code);
		case HYPO_EHOSTDOWN:
			throw NetException("Host is down", arg, code);
		case HYPO_EHOSTUNREACH:
			throw NetException("No route to host", arg, code);
		default:
			throw NetException("Socket error", arg, code);
		}
	}

	void SocketImpl::Init(int af)
	{
		InitSocket(af, SOCK_STREAM);
	}

	void SocketImpl::InitSocket(int af, int type, int proto)
	{
		m_SocketFD = ::socket(af, type, proto);
		if (m_SocketFD == HYPO_INVALID_SOCKET)
			Error();
	}

	bool SocketImpl::CheckResult(int rc)
	{
		if (rc != 0)
		{
			Error();
			return false;
		}
		return true;

	}
	bool SocketImpl::CheckResult(int rc, const std::string& arg)
	{
		if (rc != 0)
		{

			return false;
			Error(LastError(), arg);
		}
		return true;
	}

#ifdef HYPO_PLATFORM_WINDOWS
	
#pragma comment(lib, "WS2_32.lib")
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
#endif

}

