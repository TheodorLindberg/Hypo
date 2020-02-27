#pragma once
#include "Hypo.h"

namespace Hypo
{
	template<typename T>
	class _Rect
	{
	public:
		typedef T Type;

		_Rect(T left, T right, T top, T bottom)
			: left(left), right(right), top(top), bottom(bottom)
		{}
		_Rect(_Vec2<T> topLeft, _Vec2<T> bottomRight)
			: left(topLeft.x), right(bottomRight.x), top(topLeft.y), bottom(bottomRight.y)
		{}
		_Rect()
			: left(0), right(0), top(0), bottom(0)
		{}
		template<typename T2>
		inline operator _Rect<T2>()
		{
			return { static_cast<T2>(left),static_cast<T2>(right),static_cast<T2>(top),static_cast<T2>(bottom) };
		}
		_Vec2<T> GetSize() { return { abs(right - left), abs(bottom - top) }; }
		_Vec2<T> GetPosition() { return { left, top }; }

		T GetWidth() { return abs(right - left); }
		T GetHeight() { return abs(bottom - top); }

		void ScaleDown(int value)
		{
			left += value;
			right -= value;
			top += value;
			bottom -= value;
		}
		_Rect<T> GetScaledDown(int value)
		{
			_SRect<T> rect;
			rect.left = left + value;
			rect.right = right - value;
			rect.top = top + value;
			rect.bottom = bottom - value;
			return rect;
		}

		_Vec4<T> ToVector() { return { left, right, top, bottom }; }

		T left;
		T right;
		T top;
		T bottom;
	};

	template<typename T>
	_Rect<T> RectFromSize(T x, T y, T width, T height)
	{
		return { x, x + width, y, y + height };
	}
	template<typename T>
	_Rect<T> RectFromSize(_Vec2<T> pos, _Vec2<T> dims)
	{
		return { pos, {pos.x + dims.x, pos.y + dims.y} };
	}
}