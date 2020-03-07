#pragma once
#include "Hypo/3D/Exports.h"

namespace Hypo
{
	class PointLight
	{
	public:
		Vec3F Position = {0,0,0};
		Vec3F Color = {1,1,1};
		float specular = 1;
	private:
	};
}