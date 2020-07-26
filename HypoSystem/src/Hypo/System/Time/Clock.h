#pragma once
#include "Hypo/Config.h"
#include "Hypo/System/Exports.h"
#include "Hypo/System/Time/Time.h"

namespace Hypo
{
	class HYPO_SYSTEM_API Clock
	{
	public:
		Clock();
		Time Reset();
		Time GetElapsedTime() const;
	private:
		Time m_StartTime;
	};
}
