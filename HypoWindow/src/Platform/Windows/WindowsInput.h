#pragma once
#include "Hypo/Window/Input.h"
#include "Hypo/Window/Exports.h"

namespace Hypo {

	class HYPO_WINDOW_API WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;

		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual Vec2F GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}
