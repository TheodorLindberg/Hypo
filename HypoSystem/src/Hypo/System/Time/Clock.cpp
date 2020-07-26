#include "systempch.h"
#include "Clock.h"
#include <chrono>

namespace Hypo
{

	Clock::Clock()
		: m_StartTime(Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()))
	{
	}

	Time Clock::Reset()
	{
		auto now = Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		auto last = m_StartTime;
		m_StartTime = now;
		return now - last;
	}

	Time Clock::GetElapsedTime() const
	{
		auto now = Microseconds(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count());
		return now - m_StartTime;
	}
}
