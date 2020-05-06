#pragma once
#include "Hypo/3D/Asset/Light.h"

namespace Hypo
{
	struct SceneLights
	{
		std::vector<PointLight> PointLights;
		std::vector<DirectionalLight> DirectionalLights;
		std::vector<SpotLight> SpotLights;
	};
}
