#pragma once
#include "Hypo/Network/Export.h"


#if defined(HYPO_PLATFORM_WINDOWS)
#include <basetsd.h>
#endif

namespace Hypo
{
#if defined(HYPO_PLATFORM_WINDOWS)

	typedef UINT_PTR SocketHandle;

#else

	typedef int SocketHandle;

#endif
}