#pragma once
#include "Hypo/Config.h"

#ifdef HYPO_3D_EXPORTS

#define HYPO_3D_API HYPO_API_EXPORTS

#else

#define HYPO_3D_API HYPO_API_IMPORTS

#endif // HYPO_3D_EXPORTS
