#pragma once

#include "SocketImpl.h"
#include "Hypo/Network/IpAddress.h"
namespace Hypo
{

	class HYPO_NETWORK_API Socket
	{
	public:
		using SocketList = std::vector<Socket>;
		Socket() = delete;
		Socket(const Socket& other);
		Socket& operator= (const Socket& other);
		virtual ~Socket();

		static int Select(SocketList& readList, SocketList& writeList, SocketList& exceptList, Time timeout);

		bool Valid() const;
		int Available();

		uInt16 GetLocalPort() const;
		IpAddress GetPeerAddress() const;

		bool operator ==(const Socket& other) const;
		bool operator !=(const Socket& other) const;
		bool operator >(const Socket& other) const;
		bool operator >=(const Socket& other) const;
		bool operator <(const Socket& other) const;
		bool operator <=(const Socket& other) const;

		SocketImpl* Impl() const;

	protected:
		Socket(SocketImpl* impl);
		hypo_socket_t GetSocketFD() const;

		void Close();

	private:
		SocketImpl* m_Impl;
	};


	inline bool Socket::operator==(const Socket& other) const
	{
		return m_Impl == other.m_Impl;
	}

	inline bool Socket::operator!=(const Socket& other)const
	{
		return m_Impl != other.m_Impl;
	}

	inline bool Socket::operator>(const Socket& other)const
	{
		return m_Impl < other.m_Impl;
	}

	inline bool Socket::operator>=(const Socket& other)const
	{
		return m_Impl >= other.m_Impl;
	}

	inline bool Socket::operator<(const Socket& other)const
	{
		return m_Impl < other.m_Impl;
	}

	inline bool Socket::operator<=(const Socket& other)const
	{
		return m_Impl <= other.m_Impl;
	}

	inline hypo_socket_t Socket::GetSocketFD() const
	{
		return m_Impl->SockFD();
	}

	inline SocketImpl* Socket::Impl() const
	{
		return m_Impl;
	}
}
