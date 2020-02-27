#pragma once
#include "Hypo/Core.h"

namespace Hypo
{
	enum class KeyMod
	{
		Shift = BIT(0),
		Control = BIT(1),
		Alt = BIT(2),
		Super = BIT(3),
		CapsLock = BIT(4),
		NumLock = BIT(5),
	};
}