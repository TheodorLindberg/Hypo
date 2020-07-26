#pragma once

namespace Hypo
{
	class TcpServerConnection
	{
	public:
		TcpServerConnection(TcpSocket& socket)
			: m_Socket(socket)
		{}
		virtual ~TcpServerConnection() = default;
		//Called when there is data to be read on the socket
		virtual void OnReadable() = 0;
		//Called when socket disconnected
		virtual void OnDisconnect() = 0;
		//Called when server is stopping
		virtual void OnShutdown() = 0;
		 TcpSocket& GetSocket()  { return m_Socket; }
	protected:
		TcpSocket m_Socket;

	};
}