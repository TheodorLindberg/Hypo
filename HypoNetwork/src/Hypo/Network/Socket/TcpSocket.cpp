#include "networkpch.h"
#include "TcpSocket.h"
#include "Platform/Windows/WindowsSocketImpl.h"

namespace Hypo
{
	TcpSocket::TcpSocket()
		: Socket(TCP)
	{
	}

	unsigned short TcpSocket::GetLocalPort() const
	{
		if (GetHandle() != SocketImpl::InvalidSocket())
		{
			// Retrieve informations about the local end of the socket
			sockaddr_in address;
			SocketImpl::AddrLength size = sizeof(address);
			if (getsockname(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
			{
				return ntohs(address.sin_port);
			}
		}

		// We failed to retrieve the port
		return 0;
	}

	uInt32 TcpSocket::GetRemoteAddress() const
	{
		if (GetHandle() != SocketImpl::InvalidSocket())
		{
			// Retrieve informations about the remote end of the socket
			sockaddr_in address;
			SocketImpl::AddrLength size = sizeof(address);
			if (getpeername(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
			{
				return (ntohl(address.sin_addr.s_addr));
			}
		}

		// We failed to retrieve the address
		return 0x00000000;
	}

	unsigned short TcpSocket::GetRemotePort() const
	{
		if (GetHandle() != SocketImpl::InvalidSocket())
		{
			// Retrieve informations about the remote end of the socket
			sockaddr_in address;
			SocketImpl::AddrLength size = sizeof(address);
			if (getpeername(GetHandle(), reinterpret_cast<sockaddr*>(&address), &size) != -1)
			{
				return ntohs(address.sin_port);
			}
		}

		// We failed to retrieve the port
		return 0;
	}

	Socket::Status TcpSocket::Connect(const uInt32 remoteAddress, unsigned short remotePort, uInt32 timeout)
	{

		// Disconnect the socket if it is already connected
		Disconnect();

		// Create the internal socket if it doesn't exist
		Create();

		// Create the remote address
		sockaddr_in address = SocketImpl::CreateAddress(remoteAddress, remotePort);

		if (timeout <= 0)
		{
			// ----- We're not using a timeout: just try to connect -----

			// Connect the socket
			if (::connect(GetHandle(), reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1)
				return SocketImpl::GetErrorStatus();

			// Connection succeeded
			return Done;
		}
		else
		{
			// ----- We're using a timeout: we'll need a few tricks to make it work -----

			// Save the previous blocking state
			bool blocking = IsBlocking();

			// Switch to non-blocking to enable our connection timeout
			if (blocking)
				SetBlocking(false);

			// Try to connect to the remote address
			if (::connect(GetHandle(), reinterpret_cast<sockaddr*>(&address), sizeof(address)) >= 0)
			{
				// We got instantly connected! (it may no happen a lot...)
				SetBlocking(blocking);
				return Done;
			}

			// Get the error status
			Status status = SocketImpl::GetErrorStatus();

			// If we were in non-blocking mode, return immediately
			if (!blocking)
				return status;

			// Otherwise, wait until something happens to our socket (success, timeout or error)
			if (status == Socket::NotReady)
			{
				// Setup the selector
				fd_set selector;
				FD_ZERO(&selector);
				FD_SET(GetHandle(), &selector);

				// Setup the timeout
				timeval time;
				time.tv_sec = static_cast<long>(timeout / 1000000);
				time.tv_usec = static_cast<long>(timeout % 1000000);

				// Wait for something to write on our socket (which means that the connection request has returned)
				if (select(static_cast<int>(GetHandle() + 1), NULL, &selector, NULL, &time) > 0)
				{
					// At this point the connection may have been either accepted or refused.
					// To know whether it's a success or a failure, we must check the address of the connected peer
					if (GetRemoteAddress() != 0)
					{
						// Connection accepted
						status = Done;
					}
					else
					{
						// Connection refused
						status = SocketImpl::GetErrorStatus();
					}
				}
				else
				{
					// Failed to connect before timeout is over
					status = SocketImpl::GetErrorStatus();
				}
			}

			// Switch back to blocking mode
			SetBlocking(true);

			return status;
		}
	}

	void TcpSocket::Disconnect()
	{
		Close();
	}

	Socket::Status TcpSocket::Send(const void* data, std::size_t size)
	{
		if (!IsBlocking())
			std::cout << "Warning: Partial sends might not be handled properly." << std::endl;

		std::size_t sent;

		return Send(data, size, sent);
	}

	Socket::Status TcpSocket::Send(const void* data, std::size_t size, std::size_t& sent)
	{
		// Check the parameters
		if (!data || (size == 0))
		{
			std::cout << "Cannot send data over the network (no data to send)" << std::endl;
			return Error;
		}

		// Loop until every byte has been sent
		int result = 0;
		for (sent = 0; sent < size; sent += result)
		{
			// Send a chunk of data
			result = ::send(GetHandle(), static_cast<const char*>(data) + sent, size - sent, 0);

			// Check for errors
			if (result < 0)
			{
				Status status = SocketImpl::GetErrorStatus();

				if ((status == NotReady) && sent)
					return Partial;

				return status;
			}
		}

		return Done;
	}

	Socket::Status TcpSocket::Receive(void* data, std::size_t size, std::size_t& received)
	{
		// First clear the variables to fill
		received = 0;

		// Check the destination buffer
		if (!data)
		{
			std::cout << "Cannot receive data from the network (the destination buffer is invalid)" << std::endl;
			return Error;
		}

		// Receive a chunk of bytes
		int sizeReceived = recv(GetHandle(), static_cast<char*>(data), static_cast<int>(size), 0);

		// Check the number of bytes received
		if (sizeReceived > 0)
		{
			received = static_cast<std::size_t>(sizeReceived);
			return Done;
		}
		else if (sizeReceived == 0)
		{
			return Socket::Disconnected;
		}
		else
		{
			return SocketImpl::GetErrorStatus();
		}
	}
}
