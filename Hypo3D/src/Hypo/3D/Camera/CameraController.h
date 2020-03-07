#pragma once
#include "Hypo/3D/Exports.h"
#include "Camera.h"

namespace  Hypo
{
	class HYPO_3D_API ThridPersonKeyboardCamera : public PerspectiveCamera
	{
	public:
		void Update(float dt);
	private:

	};
}