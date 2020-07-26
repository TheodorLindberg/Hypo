

////////////////////////////////////////////////////////////
bool operator ==(Time left, Time right)
{
	return left.asMicroseconds() == right.asMicroseconds();
}a


////////////////////////////////////////////////////////////
bool operator !=(Time left, Time right)
{
	return left.asMicroseconds() != right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator <(Time left, Time right)
{
	return left.asMicroseconds() < right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator >(Time left, Time right)
{
	return left.asMicroseconds() > right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator <=(Time left, Time right)
{
	return left.asMicroseconds() <= right.asMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator >=(Time left, Time right)
{
	return left.asMicroseconds() >= right.asMicroseconds();
}


////////////////////////////////////////////////////////////
Time operator -(Time right)
{
	return microseconds(-right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time operator +(Time left, Time right)
{
	return microseconds(left.asMicroseconds() + right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator +=(Time& left, Time right)
{
	return left = left + right;
}


////////////////////////////////////////////////////////////
Time operator -(Time left, Time right)
{
	return microseconds(left.asMicroseconds() - right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator -=(Time& left, Time right)
{
	return left = left - right;
}


////////////////////////////////////////////////////////////
Time operator *(Time left, float right)
{
	return seconds(left.asSeconds() * right);
}


////////////////////////////////////////////////////////////
Time operator *(Time left, Int64 right)
{
	return microseconds(left.asMicroseconds() * right);
}


////////////////////////////////////////////////////////////
Time operator *(float left, Time right)
{
	return right * left;
}


////////////////////////////////////////////////////////////
Time operator *(Int64 left, Time right)
{
	return right * left;
}


////////////////////////////////////////////////////////////
Time& operator *=(Time& left, float right)
{
	return left = left * right;
}


////////////////////////////////////////////////////////////
Time& operator *=(Time& left, Int64 right)
{
	return left = left * right;
}


////////////////////////////////////////////////////////////
Time operator /(Time left, float right)
{
	return seconds(left.asSeconds() / right);
}


////////////////////////////////////////////////////////////
Time operator /(Time left, Int64 right)
{
	return microseconds(left.asMicroseconds() / right);
}


////////////////////////////////////////////////////////////
Time& operator /=(Time& left, float right)
{
	return left = left / right;
}


////////////////////////////////////////////////////////////
Time& operator /=(Time& left, Int64 right)
{
	return left = left / right;
}


////////////////////////////////////////////////////////////
float operator /(Time left, Time right)
{
	return left.asSeconds() / right.asSeconds();
}


////////////////////////////////////////////////////////////
Time operator %(Time left, Time right)
{
	return microseconds(left.asMicroseconds() % right.asMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator %=(Time& left, Time right)
{
	return left = left % right;
}
