#include "networkpch.h"
#include "Socket.h"

#if defined(HYPO_PLATFORM_WINDOWS)
#include <Platform/Windows/WindowsSocketImpl.h>


#else
#include <SFML/Network/Unix/SocketImpl.hpp>
#endif


namespace Hypo
{
	Socket::Socket(Type type) :
		m_Type(type),
		m_Socket(SocketImpl::InvalidSocket()),
		m_IsBlocking(true)
	{}

	Socket::~Socket()
	{
		Close();
	}

	void Socket::SetBlocking(bool blocking)
	{
		m_IsBlocking = blocking;
		SocketImpl::SetBlocking(m_Socket, blocking);
	}

	bool Socket::IsBlocking() const
	{
		return m_IsBlocking;
	}


	SocketHandle Socket::GetHandle() const
	{
		return m_Socket;
	}

	void Socket::Create()
	{
		// Don't create the socket if it already exists
		if (m_Socket == SocketImpl::InvalidSocket())
		{
			SocketHandle handle = socket(PF_INET, m_Type == TCP ? SOCK_STREAM : SOCK_DGRAM, 0);

			if (handle == SocketImpl::InvalidSocket())
			{
				std:std::cout << "Failed to create socket" << std::endl;
				return;
			}

			Create(handle);
		}
	}

	void Socket::Create(SocketHandle handle)
	{
		// Don't create the socket if it already exists
		if (m_Socket == SocketImpl::InvalidSocket())
		{
			// Assign the new handle
			m_Socket = handle;

			// Set the current blocking state
			SetBlocking(m_IsBlocking);

			if (m_Type == TCP)
			{
				// Disable the Nagle algorithm (i.e. removes buffering of TCP packets)
				int yes = 1;
				if (setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
				{
					std::cout << "Failed to set socket option \"TCP_NODELAY\" ; "
						<< "all your TCP packets will be buffered" << std::endl;
				}

				// On Mac OS X, disable the SIGPIPE signal on disconnection
#ifdef SFML_SYSTEM_MACOS
				if (setsockopt(m_socket, SOL_SOCKET, SO_NOSIGPIPE, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
				{
					err() << "Failed to set socket option \"SO_NOSIGPIPE\"" << std::endl;
				}
#endif
			}
			else
			{
				// Enable broadcast by default for UDP sockets
				int yes = 1;
				if (setsockopt(m_Socket, SOL_SOCKET, SO_BROADCAST, reinterpret_cast<char*>(&yes), sizeof(yes)) == -1)
				{
					std::cout << "Failed to enable broadcast on UDP socket" << std::endl;
				}
			}
		}
	}

	void Socket::Close()
	{
		// Close the socket
		if (m_Socket != SocketImpl::InvalidSocket())
		{
			SocketImpl::Close(m_Socket);
			m_Socket = SocketImpl::InvalidSocket();
		}
	}
}
