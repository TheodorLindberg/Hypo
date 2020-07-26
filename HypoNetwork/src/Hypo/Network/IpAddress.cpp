#include "networkpch.h"
#include "Hypo/Network/IpAddress.h"

#include "Socket/SocketDefs.h"

namespace Hypo
{

	const IpAddress IpAddress::None;
	const IpAddress IpAddress::Any(0, 0, 0, 0);
	const IpAddress IpAddress::LocalHost(127, 0, 0, 1);
	const IpAddress IpAddress::Broadcast(255, 255, 255, 255);


	IpAddress::IpAddress(const std::string& address)
	{
		Resolve(address);
	}

	IpAddress::IpAddress(const char* address)
	{
		Resolve(address);
	}

	IpAddress::IpAddress(Byte byte0, Byte byte1, Byte byte2, Byte byte3)
		:   m_Address(htonl((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3)),
			m_Valid(true)
	{
	}

	IpAddress::IpAddress(uInt32 address)
		:	m_Address(htonl(address)),
			m_Valid(true)
	{
	}

	std::string IpAddress::ToString() const
	{
		in_addr address;
		address.s_addr = m_Address;

		return inet_ntoa(address);
	}

	uInt32 IpAddress::ToInteger() const
	{
		return ntohl(m_Address);
	}

	IpAddress IpAddress::GetLocalAddress()
	{
		IpAddress localAddress;

		// Create the socket
		hypo_socket_t sock = socket(PF_INET, SOCK_DGRAM, 0);
		if (sock == HYPO_INVALID_SOCKET)
			return localAddress;

		sockaddr_in address;
		std::memset(&address, 0, sizeof(address));
		address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
		address.sin_family = AF_INET;
		address.sin_port = htons(9);

		// Connect the socket to localhost on any port
		if (connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == -1)
		{
			hypo_closesocket(sock);
			return localAddress;
		}

		// Get the local address of the socket connection
		int size = sizeof(address);
		if (getsockname(sock, reinterpret_cast<sockaddr*>(&address), &size) == -1)
		{
			hypo_closesocket(sock);
			return localAddress;
		}

		// Close the socket
		hypo_closesocket(sock);

		// Finally build the IP address
		localAddress = IpAddress(ntohl(address.sin_addr.s_addr));

		return localAddress;
	}

	IpAddress IpAddress::GetPublicAddress(Time timeout)
	{
		return IpAddress::None;
	}
	void IpAddress::Resolve(const std::string& address)
	{
		m_Address = 0;
		m_Valid = false;

		if (address == "255.255.255.255")
		{
			// The broadcast address needs to be handled explicitly,
			// because it is also the value returned by inet_addr on error
			m_Address = INADDR_BROADCAST;
			m_Valid = true;
		}
		else if (address == "0.0.0.0")
		{
			m_Address = INADDR_ANY;
			m_Valid = true;
		}
		else
		{
			// Try to convert the address as a byte representation ("xxx.xxx.xxx.xxx")
			uInt32 ip = inet_addr(address.c_str());
			if (ip != INADDR_NONE)
			{
				m_Address = ip;
				m_Valid = true;
			}
			else
			{
				// Not a valid address, try to convert it as a host name
				addrinfo hints;
				std::memset(&hints, 0, sizeof(hints));
				hints.ai_family = AF_INET;
				addrinfo* result = NULL;
				if (getaddrinfo(address.c_str(), NULL, &hints, &result) == 0)
				{
					if (result)
					{
						ip = reinterpret_cast<sockaddr_in*>(result->ai_addr)->sin_addr.s_addr;
						freeaddrinfo(result);
						m_Address = ip;
						m_Valid = true;
					}
				}
			}
		}
	}

	bool operator==(const IpAddress& left, const IpAddress& right)
	{
		return !(left < right) && !(right < left);
	}

	bool operator!=(const IpAddress& left, const IpAddress& right)
	{
		return !(left == right);
	}

	bool operator<(const IpAddress& left, const IpAddress& right)
	{
		return std::make_pair(left.m_Valid, left.m_Address) < std::make_pair(right.m_Valid, right.m_Address);
	}

	bool operator>(const IpAddress& left, const IpAddress& right)
	{
		return right < left;
	}

	bool operator<=(const IpAddress& left, const IpAddress& right)
	{
		return !(right < left);
	}

	bool operator>=(const IpAddress& left, const IpAddress& right)
	{
		return !(left < right);
	}

	std::istream& operator>>(std::istream& stream, IpAddress& address)
	{
		std::string str;
		stream >> str;
		address = IpAddress(str);

		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const IpAddress& address)
	{
		return stream << address.ToString();
	}
}
