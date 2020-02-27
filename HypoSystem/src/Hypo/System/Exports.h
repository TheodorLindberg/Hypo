#pragma once
#include "Hypo/Config.h"

#ifdef HYPO_SYSTEM_EXPORTS

#define HYPO_SYSTEM_API HYPO_API_EXPORTS

#else

#define HYPO_SYSTEM_API HYPO_API_IMPORTS

#endif // HYPO_MAIN_EXPORTS
