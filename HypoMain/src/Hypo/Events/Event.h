#pragma once
#include "Hypo/Core.h"
#include "KeyboardEvents.h"
#include "MouseEvents.h"
#include "ApplicationEvents.h"

namespace Hypo
{
	enum class EventType : unsigned char
	{
		None = 0,
		WindowClose, WindowResize, WindowMoved, WindowFocus, WindowLostFocus,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCategory : unsigned char
	{
		EventCategoryNone = 0,
		EventCategoryWindow = BIT(0),
		EventCategoryKeyboard = BIT(1),
		EventCategoryInput = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),
		//Joystick = BIT(5),
		//Touch = BIT(6)
	};

	class Event
	{
	public:
		Event(EventType type = EventType::None, int category = EventCategory::EventCategoryNone)
			: type(type), categoryFlag(category)
		{}
		EventType type;
		int categoryFlag;

		union
		{
			KeyEvent key;
			TextEvent text;

			MouseButtonEvent mouseButton;
			MouseScrollEvent mouseScroll;
			MouseMoveEvent mouseMove;

			WindowResizeEvent windowResize;
			WindowMoveEvent windowMove;
		};
	};
}
