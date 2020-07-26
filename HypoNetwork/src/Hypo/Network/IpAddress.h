#pragma once
#include "Hypo/Network/Export.h"
#include "Hypo/System/Time/Time.h"

namespace Hypo
{
	class HYPO_NETWORK_API IpAddress
	{
	public:
		IpAddress() = default;
		IpAddress(const std::string& address);
		IpAddress(const char* address);
		IpAddress(Byte byte0, Byte byte1, Byte byte2, Byte byte3);
		explicit IpAddress(uInt32 address);

		std::string ToString() const;
		uInt32 ToInteger() const;

		static IpAddress GetLocalAddress();
		static IpAddress GetPublicAddress(Time timeout = Time::Zero);
		bool Valid() const { return m_Valid; }

		static const IpAddress None;     
		static const IpAddress Any;      
		static const IpAddress LocalHost; 
		static const IpAddress Broadcast;
	private:

		friend HYPO_NETWORK_API bool operator <(const IpAddress& left, const IpAddress& right);


		void Resolve(const std::string& address);
		uInt32 m_Address = 0;
		bool   m_Valid = false;   
	};


	HYPO_NETWORK_API bool operator ==(const IpAddress& left, const IpAddress& right);

	HYPO_NETWORK_API bool operator !=(const IpAddress& left, const IpAddress& right);

	HYPO_NETWORK_API bool operator <(const IpAddress& left, const IpAddress& right);

	HYPO_NETWORK_API bool operator >(const IpAddress& left, const IpAddress& right);

	HYPO_NETWORK_API bool operator <=(const IpAddress& left, const IpAddress& right);

	HYPO_NETWORK_API bool operator >=(const IpAddress& left, const IpAddress& right);

	HYPO_NETWORK_API std::istream& operator >>(std::istream& stream, IpAddress& address);

	HYPO_NETWORK_API std::ostream& operator <<(std::ostream& stream, const IpAddress& address);
}
