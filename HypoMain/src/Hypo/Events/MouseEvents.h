#pragma once
#include "Hypo/Core.h"
#include <glm/vec2.hpp>
namespace Hypo
{
	class MouseMoveEvent
	{
	public:
		MouseMoveEvent(float x, float y)
			: x(x), y(y)
		{}

		glm::vec2 GetPosition() { return { x,y }; }

		float x;
		float y;
	};
	class MouseButtonEvent
	{
	public:
		MouseButtonEvent(unsigned int button, float x, float y)
			: button(button), x(x), y(y)
		{}

		glm::vec2 GetMousePosition() { return { x,y }; }

		unsigned int button;
		float x;
		float y;
	};
	class MouseScrollEvent
	{
	public:
		MouseScrollEvent(float deltaX, float deltaY, float x, float y)
			: deltaX(deltaX), deltaY(deltaY), x(x), y(y)
		{}
		glm::vec2 GetMousePosition() { return { x,y }; }

		float deltaX;
		float deltaY;
		float x;
		float y;
	};
}