#pragma once
#include "Hypo/Window/Exports.h"
#include "Hypo/Core.h"
#include <utility>

namespace Hypo {

	class HYPO_WINDOW_API Input
	{
	public:
		 static bool IsKeyPressed(int keycode);

		 static bool IsMouseButtonPressed(int button);
		 static Vec2F GetMousePosition();
		 static float GetMouseX();
		 static float GetMouseY();
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual Vec2F GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
		static Input* s_Instance;
	};

}
//Key codes

#define HYPO_MOUSE_BUTTON_1         0
#define HYPO_MOUSE_BUTTON_2         1
#define HYPO_MOUSE_BUTTON_3         2
#define HYPO_MOUSE_BUTTON_4         3
#define HYPO_MOUSE_BUTTON_5         4
#define HYPO_MOUSE_BUTTON_6         5
#define HYPO_MOUSE_BUTTON_7         6
#define HYPO_MOUSE_BUTTON_8         7
#define HYPO_MOUSE_BUTTON_LAST      HYPO_MOUSE_BUTTON_8
#define HYPO_MOUSE_BUTTON_LEFT      HYPO_MOUSE_BUTTON_1
#define HYPO_MOUSE_BUTTON_RIGHT     HYPO_MOUSE_BUTTON_2
#define HYPO_MOUSE_BUTTON_MIDDLE    HYPO_MOUSE_BUTTON_3
/*! @} */
// From glfw3.h
#define HYPO_KEY_SPACE              32
#define HYPO_KEY_APOSTROPHE         39  /* ' */
#define HYPO_KEY_COMMA              44  /* , */
#define HYPO_KEY_MINUS              45  /* - */
#define HYPO_KEY_PERIOD             46  /* . */
#define HYPO_KEY_SLASH              47  /* / */
#define HYPO_KEY_0                  48
#define HYPO_KEY_1                  49
#define HYPO_KEY_2                  50
#define HYPO_KEY_3                  51
#define HYPO_KEY_4                  52
#define HYPO_KEY_5                  53
#define HYPO_KEY_6                  54
#define HYPO_KEY_7                  55
#define HYPO_KEY_8                  56
#define HYPO_KEY_9                  57
#define HYPO_KEY_SEMICOLON          59  /* ; */
#define HYPO_KEY_EQUAL              61  /* = */
#define HYPO_KEY_A                  65
#define HYPO_KEY_B                  66
#define HYPO_KEY_C                  67
#define HYPO_KEY_D                  68
#define HYPO_KEY_E                  69
#define HYPO_KEY_F                  70
#define HYPO_KEY_G                  71
#define HYPO_KEY_H                  72
#define HYPO_KEY_I                  73
#define HYPO_KEY_J                  74
#define HYPO_KEY_K                  75
#define HYPO_KEY_L                  76
#define HYPO_KEY_M                  77
#define HYPO_KEY_N                  78
#define HYPO_KEY_O                  79
#define HYPO_KEY_P                  80
#define HYPO_KEY_Q                  81
#define HYPO_KEY_R                  82
#define HYPO_KEY_S                  83
#define HYPO_KEY_T                  84
#define HYPO_KEY_U                  85
#define HYPO_KEY_V                  86
#define HYPO_KEY_W                  87
#define HYPO_KEY_X                  88
#define HYPO_KEY_Y                  89
#define HYPO_KEY_Z                  90
#define HYPO_KEY_LEFT_BRACKET       91  /* [ */
#define HYPO_KEY_BACKSLASH          92  /* \ */
#define HYPO_KEY_RIGHT_BRACKET      93  /* ] */
#define HYPO_KEY_GRAVE_ACCENT       96  /* ` */
#define HYPO_KEY_WORLD_1            161 /* non-US #1 */
#define HYPO_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define HYPO_KEY_ESCAPE             256
#define HYPO_KEY_ENTER              257
#define HYPO_KEY_TAB                258
#define HYPO_KEY_BACKSPACE          259
#define HYPO_KEY_INSERT             260
#define HYPO_KEY_DELETE             261
#define HYPO_KEY_RIGHT              262
#define HYPO_KEY_LEFT               263
#define HYPO_KEY_DOWN               264
#define HYPO_KEY_UP                 265
#define HYPO_KEY_PAGE_UP            266
#define HYPO_KEY_PAGE_DOWN          267
#define HYPO_KEY_HOME               268
#define HYPO_KEY_END                269
#define HYPO_KEY_CAPS_LOCK          280
#define HYPO_KEY_SCROLL_LOCK        281
#define HYPO_KEY_NUM_LOCK           282
#define HYPO_KEY_PRINT_SCREEN       283
#define HYPO_KEY_PAUSE              284
#define HYPO_KEY_F1                 290
#define HYPO_KEY_F2                 291
#define HYPO_KEY_F3                 292
#define HYPO_KEY_F4                 293
#define HYPO_KEY_F5                 294
#define HYPO_KEY_F6                 295
#define HYPO_KEY_F7                 296
#define HYPO_KEY_F8                 297
#define HYPO_KEY_F9                 298
#define HYPO_KEY_F10                299
#define HYPO_KEY_F11                300
#define HYPO_KEY_F12                301
#define HYPO_KEY_F13                302
#define HYPO_KEY_F14                303
#define HYPO_KEY_F15                304
#define HYPO_KEY_F16                305
#define HYPO_KEY_F17                306
#define HYPO_KEY_F18                307
#define HYPO_KEY_F19                308
#define HYPO_KEY_F20                309
#define HYPO_KEY_F21                310
#define HYPO_KEY_F22                311
#define HYPO_KEY_F23                312
#define HYPO_KEY_F24                313
#define HYPO_KEY_F25                314
#define HYPO_KEY_KP_0               320
#define HYPO_KEY_KP_1               321
#define HYPO_KEY_KP_2               322
#define HYPO_KEY_KP_3               323
#define HYPO_KEY_KP_4               324
#define HYPO_KEY_KP_5               325
#define HYPO_KEY_KP_6               326
#define HYPO_KEY_KP_7               327
#define HYPO_KEY_KP_8               328
#define HYPO_KEY_KP_9               329
#define HYPO_KEY_KP_DECIMAL         330
#define HYPO_KEY_KP_DIVIDE          331
#define HYPO_KEY_KP_MULTIPLY        332
#define HYPO_KEY_KP_SUBTRACT        333
#define HYPO_KEY_KP_ADD             334
#define HYPO_KEY_KP_ENTER           335
#define HYPO_KEY_KP_EQUAL           336
#define HYPO_KEY_LEFT_SHIFT         340
#define HYPO_KEY_LEFT_CONTROL       341
#define HYPO_KEY_LEFT_ALT           342
#define HYPO_KEY_LEFT_SUPER         343
#define HYPO_KEY_RIGHT_SHIFT        344
#define HYPO_KEY_RIGHT_CONTROL      345
#define HYPO_KEY_RIGHT_ALT          346
#define HYPO_KEY_RIGHT_SUPER        347
#define HYPO_KEY_MENU               348