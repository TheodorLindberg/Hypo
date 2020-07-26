#pragma once

namespace Hypo
{
	class Packet;

	class SendStream
	{
	public:
		SendStream() = default;
		virtual ~SendStream() = default;
		virtual int Send(const void* buffer, int size) = 0;
		void SendSinglePacket(Packet* packet);

	};
}