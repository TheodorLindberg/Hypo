#pragma once
#include "Hypo/Config.h"

#ifdef HYPO_MAIN_EXPORTS

#define HYPO_MAIN_API HYPO_API_EXPORTS

#else

#define HYPO_MAIN_API HYPO_API_IMPORTS

#endif // HYPO_MAIN_EXPORTS
