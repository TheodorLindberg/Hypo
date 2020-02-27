#pragma once
#include "Hypo/Core.h"
#include "Keyboard.h"

namespace Hypo
{
	class KeyEvent
	{
	public:
		KeyEvent(unsigned int key, unsigned int scanCode, unsigned int mods)
			: key(key), scanCode(scanCode), mods(mods)
		{}
		bool HasMod(KeyMod mod) { return key & mods; }

		unsigned int key;
		unsigned int scanCode;
		unsigned int mods;
	};

	class TextEvent
	{
	public:
		TextEvent(unsigned int scancode)
			: scancode(scancode)
		{}

		unsigned int scancode;
	};
}