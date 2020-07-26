#include "networkpch.h"
#include "Socket.h"


namespace Hypo
{
	
	Socket::Socket(const Socket& other)
		:  m_Impl(other.m_Impl)
	{
		m_Impl->Duplicate();
	}


	Socket& Socket::operator=(const Socket& other)
	{
		if(this != &other)
		{
			if (m_Impl) m_Impl->Release();
			m_Impl = other.m_Impl;
			if (m_Impl) m_Impl->Duplicate();

		}
		return *this;
	}

	Socket::~Socket()
	{
		m_Impl->Release();
	}

	

	Socket::Socket(SocketImpl* impl)
		: m_Impl(impl)
	{
	}

	void Socket::Close()
	{
		m_Impl->Close();
	}

	uInt16 Socket::GetLocalPort()const
	{
		return 0;
	}

	IpAddress Socket::GetPeerAddress()const
	{
		return 0;
	}

	int Socket::Select(SocketList& readList, SocketList& writeList, SocketList& exceptList, Time timeout)
	{
		fd_set fdRead;
		fd_set fdWrite;
		fd_set fdExcept;

		int nfd = 0;
		FD_ZERO(&fdRead);
		for(auto& sock : readList)
		{
			hypo_socket_t fd = sock.GetSocketFD();
			if (fd != HYPO_INVALID_SOCKET)
			{
				if (int(fd) > nfd)
					nfd = int(fd);
				FD_SET(fd, &fdRead);
			}
		}
		FD_ZERO(&fdWrite);
		for (auto& sock : writeList)
		{
			hypo_socket_t fd = sock.GetSocketFD();
			if (fd != HYPO_INVALID_SOCKET)
			{
				if (int(fd) > nfd)
					nfd = int(fd);
				FD_SET(fd, &fdWrite);
			}
		}
		FD_ZERO(&fdExcept);
		for (auto& sock : exceptList)
		{
			hypo_socket_t fd = sock.GetSocketFD();
			if (fd != HYPO_INVALID_SOCKET)
			{
				if (int(fd) > nfd)
					nfd = int(fd);
				FD_SET(fd, &fdExcept);
			}
		}
		if (nfd == 0) return 0;

		Time remainingTime(timeout);
		int rc;
		do
		{
			struct timeval tv;
			tv.tv_sec = (long)remainingTime.AsSeconds();
			tv.tv_usec = (long)remainingTime.AsMicroseconds() % 1000000;
			Time start;
			rc = ::select(nfd + 1, &fdRead, &fdWrite, &fdExcept, &tv);
			if (rc < 0 && SocketImpl::LastError() == HYPO_EINTR)
			{
				Time end;
				Time waited = end - start;
				if (waited < remainingTime)
					remainingTime -= waited;
				else
					remainingTime = 0;
			}
		} while (rc < 0 && SocketImpl::LastError() == HYPO_EINTR);
		if (rc < 0) SocketImpl::Error();

		SocketList readyReadList;
		for (SocketList::const_iterator it = readList.begin(); it != readList.end(); ++it)
		{
			hypo_socket_t fd = it->GetSocketFD();
			if (fd != HYPO_INVALID_SOCKET)
			{
				if (FD_ISSET(fd, &fdRead))
					readyReadList.push_back(*it);
			}
		}
		std::swap(readList, readyReadList);
		SocketList readyWriteList;
		for (SocketList::const_iterator it = writeList.begin(); it != writeList.end(); ++it)
		{
			hypo_socket_t  fd = it->GetSocketFD();
			if (fd != HYPO_INVALID_SOCKET)
			{
				if (FD_ISSET(fd, &fdWrite))
					readyWriteList.push_back(*it);
			}
		}
		std::swap(writeList, readyWriteList);
		SocketList readyExceptList;
		for (SocketList::const_iterator it = exceptList.begin(); it != exceptList.end(); ++it)
		{
			hypo_socket_t  fd = it->GetSocketFD();
			if (fd != HYPO_INVALID_SOCKET)
			{
				if (FD_ISSET(fd, &fdExcept))
					readyExceptList.push_back(*it);
			}
		}
		std::swap(exceptList, readyExceptList);
		return rc;
	}

	bool Socket::Valid() const
	{
		return m_Impl->Valid();
	}

	int Socket::Available()
	{
		return m_Impl->Available();
	}
}
