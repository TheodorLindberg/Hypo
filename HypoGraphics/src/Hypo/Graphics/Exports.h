#pragma once
#include "Hypo/Config.h"

#ifdef HYPO_GRAPHICS_EXPORTS

#define HYPO_GRAPHICS_API HYPO_API_EXPORTS

#else

#define HYPO_GRAPHICS_API HYPO_API_IMPORTS

#endif // HYPO_MAIN_EXPORTS
