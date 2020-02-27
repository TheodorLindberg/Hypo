#pragma once
#include "Hypo/Config.h"

#ifdef HYPO_WINDOW_EXPORTS

#define HYPO_WINDOW_API HYPO_API_EXPORTS

#else

#define HYPO_WINDOW_API HYPO_API_IMPORTS

#endif // HYPO_3D_EXPORTS
