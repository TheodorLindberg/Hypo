#pragma once
#include "Hypo/Core.h"
#include <glm/glm.hpp>

namespace Hypo
{
	class WindowResizeEvent
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: width(width), height(height)
		{}
		glm::ivec2 GetSize() { return { width, height }; }

		unsigned int width;
		unsigned int height;
	};
	class WindowMoveEvent
	{
	public:
		WindowMoveEvent(int posX, int posY)
			: posX(posX), posY(posY)
		{}

		glm::ivec2 GetPosition() { return { posX, posY }; }

		int posX;
		int posY;
	};
}