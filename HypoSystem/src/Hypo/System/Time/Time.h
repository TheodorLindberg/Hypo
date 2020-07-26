#pragma once
#include "Hypo/Config.h"
#include "Hypo/System/Exports.h"

namespace Hypo
{
	class HYPO_SYSTEM_API Time
	{
	public:
		Time();
		Time(Int64 microseconds);
		float AsSeconds() const { return m_Microseconds / 1000000.f; }
		Int64 AsMilliseconds() const { return static_cast<Int64>(m_Microseconds / 1000); };
		Int64 AsMicroseconds() const { return m_Microseconds; };

		static const Time Zero;
	private:
		friend HYPO_SYSTEM_API Time Microseconds(Int64);
		friend HYPO_SYSTEM_API Time Milliseconds(Int64);
		friend HYPO_SYSTEM_API Time Seconds(float);
	private:
		Int64 m_Microseconds = 0;
	};

	HYPO_SYSTEM_API Time Microseconds(Int64 amount);
	HYPO_SYSTEM_API Time Milliseconds(Int64 amount);
	HYPO_SYSTEM_API Time Seconds(float amount);


	HYPO_SYSTEM_API bool operator ==(Time left, Time right);
	HYPO_SYSTEM_API bool operator !=(Time left, Time right);
	HYPO_SYSTEM_API bool operator <(Time left, Time right);
	HYPO_SYSTEM_API bool operator >(Time left, Time right);
	HYPO_SYSTEM_API bool operator <=(Time left, Time right);
	HYPO_SYSTEM_API bool operator >=(Time left, Time right);
	HYPO_SYSTEM_API Time operator -(Time right);
	HYPO_SYSTEM_API Time operator +(Time left, Time right);
	HYPO_SYSTEM_API Time& operator +=(Time& left, Time right);
	HYPO_SYSTEM_API Time operator -(Time left, Time right);
	HYPO_SYSTEM_API Time& operator -=(Time& left, Time right);
	HYPO_SYSTEM_API Time operator *(Time left, float right);
	HYPO_SYSTEM_API Time operator *(Time left, Int64 right);
	HYPO_SYSTEM_API Time operator *(float left, Time right);
	HYPO_SYSTEM_API Time operator *(Int64 left, Time right);
	HYPO_SYSTEM_API Time& operator *=(Time& left, float right);
	HYPO_SYSTEM_API Time& operator *=(Time& left, Int64 right);
	HYPO_SYSTEM_API Time operator /(Time left, float right);
	HYPO_SYSTEM_API Time operator /(Time left, Int64 right);
	HYPO_SYSTEM_API Time& operator /=(Time& left, float right);
	HYPO_SYSTEM_API Time& operator /=(Time& left, Int64 right);
	HYPO_SYSTEM_API float operator /(Time left, Time right);
	HYPO_SYSTEM_API Time operator %(Time left, Time right);
	HYPO_SYSTEM_API Time& operator %=(Time& left, Time right);

}