#pragma once
#include "Hypo/Config.h"

#ifdef HYPO_NETWORK_EXPORTS

#define HYPO_NETWORK_API HYPO_API_EXPORTS

#else

#define HYPO_NETWORK_API HYPO_API_IMPORTS

#endif // HYPO_NETWORK_EXPORTS
