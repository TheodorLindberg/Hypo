#pragma once
#include "Core.h"
#include <vector>
#include <stdint.h>
#include "Hypo/System/DataTypes/Vec.h"
#include "Hypo/System/DataTypes/Rect.h"

#define S_PI 3.14159265359

namespace Hypo
{

	// Scalar data types
	typedef std::uint64_t uInt64;
	typedef std::uint32_t uInt32;
	typedef std::uint16_t uInt16;
	typedef std::uint8_t uInt8;

	typedef std::int64_t Int64;
	typedef std::int32_t Int32;
	typedef std::int16_t Int16;
	typedef std::int8_t Int8;

	typedef unsigned int TextureID;

	typedef unsigned char Byte;


	//Vector namings
	typedef _Vec2<Int64> Vec2L;
	typedef _Vec3<Int64> Vec3L;
	typedef _Vec4<Int64> Vec4L;

	typedef _Vec2<Int32> Vec2I;
	typedef _Vec3<Int32> Vec3I;
	typedef _Vec4<Int32> Vec4I;

	typedef _Vec2<Int16> Vec2S;
	typedef _Vec3<Int16> Vec3S;
	typedef _Vec4<Int16> Vec4S;

	typedef _Vec2<uInt8> Vec2B;
	typedef _Vec3<uInt8> Vec3B;
	typedef _Vec4<uInt8> Vec4B;

	typedef _Vec2<float> Vec2F;
	typedef _Vec3<float> Vec3F;
	typedef _Vec4<float> Vec4F;

	typedef _Vec2<double> Vec2D;
	typedef _Vec3<double> Vec3D;
	typedef _Vec4<double> Vec4D;


	typedef _Vec2<uInt32> Vec2U;
	typedef _Vec3<uInt32> Vec3U;
	typedef _Vec4<uInt32> Vec4U;

	//Rect namings
	typedef _Rect<Int64> RectL;
	typedef _Rect<Int32> RectI;
	typedef _Rect<Int16> RectS;
	typedef _Rect<Int8> RectB;

	typedef _Rect<float> RectF;
	typedef _Rect<double> RectD;
	typedef _Rect<uInt32> RectU;
	
	using Index = uInt32;


	inline int BitSetCount(int value, char bitSearchCount = 32) {
		int count = 0;
		for (int i = 0; i < bitSearchCount; i++)
		{
			count += value & 0x1;
			value = value >> 1;
		}
		return count;
	}
}