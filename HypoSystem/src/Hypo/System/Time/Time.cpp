#include "systempch.h"
#include "Time.h"

namespace Hypo
{

	const Time Time::Zero;

	Time::Time()
		: m_Microseconds(0)
	{
	}

	Time::Time(Int64 microseconds)
		: m_Microseconds(microseconds)
	{
	}

	Time Microseconds(Int64 amount)
	{
		return Time(amount);
	}

	Time Milliseconds(Int64 amount)
	{
		return Time(static_cast<Int64>(amount) * 1000);
	}

	Time Seconds(float amount)
	{
		return Time(static_cast<Int64>(amount * 1000000));
	}

	
	bool operator ==(Time left, Time right)
	{
		return left.AsMicroseconds() == right.AsMicroseconds();
	}


	
	bool operator !=(Time left, Time right)
	{
		return left.AsMicroseconds() != right.AsMicroseconds();
	}


	
	bool operator <(Time left, Time right)
	{
		return left.AsMicroseconds() < right.AsMicroseconds();
	}


	
	bool operator >(Time left, Time right)
	{
		return left.AsMicroseconds() > right.AsMicroseconds();
	}


	
	bool operator <=(Time left, Time right)
	{
		return left.AsMicroseconds() <= right.AsMicroseconds();
	}


	
	bool operator >=(Time left, Time right)
	{
		return left.AsMicroseconds() >= right.AsMicroseconds();
	}


	
	Time operator -(Time right)
	{
		return Microseconds(-right.AsMicroseconds());
	}


	
	Time operator +(Time left, Time right)
	{
		return Microseconds(left.AsMicroseconds() + right.AsMicroseconds());
	}


	
	Time& operator +=(Time& left, Time right)
	{
		return left = left + right;
	}


	
	Time operator -(Time left, Time right)
	{
		return Microseconds(left.AsMicroseconds() - right.AsMicroseconds());
	}


	
	Time& operator -=(Time& left, Time right)
	{
		return left = left - right;
	}


	
	Time operator *(Time left, float right)
	{
		return Seconds(left.AsSeconds() * right);
	}


	
	Time operator *(Time left, Int64 right)
	{
		return Microseconds(left.AsMicroseconds() * right);
	}


	
	Time operator *(float left, Time right)
	{
		return right * left;
	}


	
	Time operator *(Int64 left, Time right)
	{
		return right * left;
	}


	
	Time& operator *=(Time& left, float right)
	{
		return left = left * right;
	}


	
	Time& operator *=(Time& left, Int64 right)
	{
		return left = left * right;
	}


	
	Time operator /(Time left, float right)
	{
		return Seconds(left.AsSeconds() / right);
	}


	
	Time operator /(Time left, Int64 right)
	{
		return Microseconds(left.AsMicroseconds() / right);
	}


	
	Time& operator /=(Time& left, float right)
	{
		return left = left / right;
	}


	
	Time& operator /=(Time& left, Int64 right)
	{
		return left = left / right;
	}


	
	float operator /(Time left, Time right)
	{
		return left.AsSeconds() / right.AsSeconds();
	}


	
	Time operator %(Time left, Time right)
	{
		return Microseconds(left.AsMicroseconds() % right.AsMicroseconds());
	}


	
	Time& operator %=(Time& left, Time right)
	{
		return left = left % right;
	}

}