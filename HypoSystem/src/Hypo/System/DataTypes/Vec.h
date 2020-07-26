#pragma once
#include <glm/glm.hpp>
#include <algorithm>

namespace Hypo
{

	template <typename T>
	class _Vec2
	{
	public:
		_Vec2()
			: x(0), y(0)
		{}
		_Vec2(T val)
			: x(val), y(val)
		{}
		_Vec2(T x, T y)
			:
			x(x),
			y(y)
		{}
		_Vec2(std::pair<T,T> pair)
			:
			x(pair.first),
			y(pair.second)
		{}
		template<typename T2, typename T3>
		_Vec2(T2 x, T3 y)
			:
			x(static_cast<T>(x)),
			y(static_cast<T>(y))
		{}
		template <typename T2>
		explicit operator _Vec2<T2>() const
		{
			return{ (T2)x,(T2)y };
		}
		T		LenSq() const
		{
			return (x * x + y * y);
		}
		T		Len() const
		{
			return sqrt(LenSq());
		}
		_Vec2& Normalize()
		{
			const T length = Len();
			x /= length;
			y /= length;
			return *this;
		}
		_Vec2	GetNormalized() const
		{
			_Vec2 norm = *this;
			norm.Normalize();
			return norm;
		}
		_Vec2	operator-() const
		{
			return _Vec2(-x, -y);
		}
		_Vec2& operator=(const _Vec2& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			return *this;
		}
		_Vec2& operator+=(const _Vec2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}
		_Vec2& operator-=(const _Vec2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}
		T		operator*(const _Vec2& rhs) const
		{
			return x * rhs.x + y * rhs.y;
		}
		_Vec2	operator+(const _Vec2& rhs) const
		{
			return _Vec2(*this) += rhs;
		}
		_Vec2	operator-(const _Vec2& rhs) const
		{
			return _Vec2(*this) -= rhs;
		}
		_Vec2& operator*=(const T& rhs)
		{
			x *= rhs;
			y *= rhs;
			return *this;
		}
		_Vec2	operator*(const T& rhs) const
		{
			return _Vec2(*this) *= rhs;
		}
		_Vec2& operator/=(const T& rhs)
		{
			x /= rhs;
			y /= rhs;
			return *this;
		}
		_Vec2	operator/(const T& rhs) const
		{
			return _Vec2(*this) /= rhs;
		}
		bool	operator==(const _Vec2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}
		bool	operator!=(const _Vec2& rhs) const
		{
			return !(*this == rhs);
		}
	public:
		union
		{
			struct
			{
				T x;
				T y;
			};
			struct
			{
				T r;
				T g;
			};
		};
	};
	template <typename T>
	class _Vec3
	{
	public:
		_Vec3()
			: x(0), y(0),z(0)
		{}
		_Vec3(T val)
			: x(val), y(val), z(val)
		{}
		_Vec3(T x, T y, T z)
			:
			x(x), y(y),z(z)
		{}
		template<typename T2>
		_Vec3(T2 x, T2 y, T2 z)
			:
			x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z))
		{}

		_Vec3(glm::vec3 vec)
			:
			x(vec.x),y(vec.y),
			z(vec.z)
		{}
		template <typename T2>
		explicit operator _Vec3<T2>() const
		{
			return{ (T2)x,(T2)y,(T2)z };

		}

		T		LenSq() const
		{
			
			return x * x + y * y + z * z;
		}

		T		Len() const
		{
			return sqrt(LenSq());
		}
		_Vec3& Normalize()
		{
			const T length = Len();
			x /= length;
			y /= length;
			z /= length;
			return *this;
		}
		_Vec3	GetNormalized() const
		{
			_Vec3 norm = *this;
			norm.Normalize();
			return norm;
		}
		_Vec3	operator-() const
		{
			return _Vec3(-x, -y, -z);
		}
		_Vec3& operator=(const _Vec3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}
		_Vec3& operator+=(const _Vec3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}
		_Vec3& operator-=(const _Vec3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}
		T		operator*(const _Vec3& rhs) const
		{
			return x * rhs.x + y * rhs.y + z * rhs.z;
		}
		_Vec3	operator+(const _Vec3& rhs) const
		{
			return _Vec3(*this) += rhs;
		}
		_Vec3	operator-(const _Vec3& rhs) const
		{
			return _Vec3(*this) -= rhs;
		}
		_Vec3& operator*=(const T& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}
		_Vec3	operator*(const T& rhs) const
		{
			return _Vec3(*this) *= rhs;
		}
		_Vec3	operator%(const _Vec3& rhs) const
		{
			return _Vec3(
				y * rhs.z - z * rhs.y,
				z * rhs.x - x * rhs.z,
				x * rhs.y - y * rhs.x);
		}
		_Vec3& operator/=(const T& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}
		_Vec3	operator/(const T& rhs) const
		{
			return _Vec3(*this) /= rhs;
		}
		bool	operator==(const _Vec3& rhs) const
		{
			return x == rhs.x && y == rhs.y && rhs.z == z;
		}
		bool	operator!=(const _Vec3& rhs) const
		{
			return !(*this == rhs);
		}
		// clamp to between 0.0 ~ 1.0
		_Vec3& Saturate()
		{
			x = std::min(1.0f, std::max(0.0f, x));
			y = std::min(1.0f, std::max(0.0f, y));
			z = std::min(1.0f, std::max(0.0f, z));
			return *this;
		}
		// clamp to between 0.0 ~ 1.0
		_Vec3	GetSaturated() const
		{
			_Vec3 temp(*this);
			temp.Saturate();
			return temp;
		}
		// x3 = x1 * x2 etc.
		_Vec3& Hadamard(const _Vec3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}
		// x3 = x1 * x2 etc.
		_Vec3	GetHadamard(const _Vec3& rhs) const
		{
			_Vec3 temp(*this);
			temp.Hadamard(rhs);
			return temp;
		}
	public:
		union
		{
			struct
			{
				T x;
				T y;
				T z;
			};
			struct
			{
				T r;
				T g;
				T b;
			};
		};
	};

	template <typename T>
	class _Vec4 : public _Vec3<T>
	{
	public:
		_Vec4()
			: w(0)
		{}
		_Vec4(T val)
			: _Vec3(val), w(val)
		{}
		_Vec4(T x, T y, T z, T w)
			:
			_Vec3(x, y, z),
			w(w)
		{}
		_Vec4(const _Vec3& v3, float w = 1.0f)
			:
			_Vec3(v3),
			w(w)
		{}
		template <typename T2>
		explicit operator _Vec4<T2>() const
		{
			return{ (T2)x,(T2)y,(T2)z,(T2)w };
		}
		//T		LenSq() const
		//{
		//	return sq( *this );
		//}
		//T		Len() const
		//{
		//	return sqrt( LenSq() );
		//}
		//_Vec3&	Normalize()
		//{
		//	const T length = Len();
		//	x /= length;
		//	y /= length;
		//	z /= length;
		//	return *this;
		//}
		//_Vec3	GetNormalized() const
		//{
		//	_Vec3 norm = *this;
		//	norm.Normalize();
		//	return norm;
		//}
		_Vec4	operator-() const
		{
			return _Vec4(-x, -y, -z, -w);
		}
		_Vec4& operator=(const _Vec4& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			w = rhs.w;
			return *this;
		}
		_Vec4& operator+=(const _Vec4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
			return *this;
		}
		_Vec4& operator-=(const _Vec4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}
		//T		operator*( const _Vec4 &rhs ) const
		//{
		//	return x * rhs.x + y * rhs.y + z * rhs.z;
		//}
		_Vec4	operator+(const _Vec4& rhs) const
		{
			return _Vec4(*this) += rhs;
		}
		_Vec4	operator-(const _Vec4& rhs) const
		{
			return _Vec4(*this) -= rhs;
		}
		_Vec4& operator*=(const T& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
			return *this;
		}
		_Vec4	operator*(const T& rhs) const
		{
			return _Vec4(*this) *= rhs;
		}
		//_Vec4	operator%( const _Vec4& rhs ) const
		//{
		//	return _Vec4(
		//		y * rhs.z - z * rhs.y,
		//		z * rhs.x - x * rhs.z,
		//		x * rhs.y - y * rhs.x );
		//}
		_Vec4& operator/=(const T& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
			return *this;
		}
		_Vec4	operator/(const T& rhs) const
		{
			return _Vec4(*this) /= rhs;
		}
		bool	operator==(const _Vec4& rhs) const
		{
			return x == rhs.x && y == rhs.y && rhs.z == z && rhs.w == w;
		}
		bool	operator!=(const _Vec4& rhs) const
		{
			return !(*this == rhs);
		}
		// clamp to between 0.0 ~ 1.0
		_Vec4& Saturate()
		{
			x = std::min(1.0f, std::max(0.0f, x));
			y = std::min(1.0f, std::max(0.0f, y));
			z = std::min(1.0f, std::max(0.0f, z));
			w = std::min(1.0f, std::max(0.0f, w));
			return *this;
		}
		// clamp to between 0.0 ~ 1.0
		_Vec4	GetSaturated() const
		{
			_Vec4 temp(*this);
			temp.Saturate();
			return temp;
		}
		// x3 = x1 * x2 etc.
		_Vec4& Hadamard(const _Vec4& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
			return *this;
		}
		// x3 = x1 * x2 etc.
		_Vec4	GetHadamard(const _Vec4& rhs) const
		{
			_Vec4 temp(*this);
			temp.Hadamard(rhs);
			return temp;
		}
	public:
		union
		{
			T w;
			T a;
		};
	};

}