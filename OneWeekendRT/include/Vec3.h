#ifndef OW_VEC3_H
#define OW_VEC3_H

#include "Types.h"
#include "Misc.h"

#include <math.h>

namespace ow
{
	class Vec3 final
	{
	public:
		union
		{
			struct {
				real x, y, z;
			};
			struct {
				real r, g, b;
			};
			real e[3];
		};

	public:
		Vec3()
			:x(0),y(0),z(0)
		{}
		Vec3(const Vec3& vec)
			:x(vec.x), y(vec.y), z(vec.z)
		{}
		Vec3(real e1, real e2, real e3)
			:x(e1), y(e2), z(e3)
		{}

		inline const Vec3& operator+() const { return *this; }
		inline Vec3 operator-() const { return Vec3(-x, -y, -z); }
		inline real operator[](int i) const { OW_EXPECT(0 >= i && i <= 2); return e[i]; }

		inline Vec3 operator+=(const Vec3& rhs)
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
			return *this;
		}

		inline Vec3 operator-=(const Vec3& rhs)
		{
			this->x -= rhs.x;
			this->y -= rhs.y;
			this->z -= rhs.z;
			return *this;
		}

		inline Vec3 operator*=(const Vec3 rhs)
		{
			this->x *= rhs.x;
			this->y *= rhs.y;
			this->z *= rhs.z;
			return *this;
		}

		inline Vec3 operator/=(const Vec3 rhs)
		{
			this->x /= rhs.x;
			this->y /= rhs.y;
			this->z /= rhs.z;
			return *this;
		}

		inline Vec3& operator*=(real t)
		{
			this->x *= t;
			this->y *= t;
			this->z *= t;
			return *this;
		}

		inline Vec3& operator/=(real t)
		{
			real inv_t = 1.0f / t;
			this->x *= inv_t;
			this->y *= inv_t;
			this->z *= inv_t;
			return *this;
		}

		inline real length() const
		{
			return sqrt(x*x + y*y + z*z);
		}

		inline real lengthSquared() const
		{
			return x*x + y*y + z*z;
		}

		inline void normalize()
		{
			real inv_length = 1.0f / length();
			x *= inv_length;
			y *= inv_length;
			z *= inv_length;
		}
	};

	inline Vec3 operator+(const Vec3& lhs, const Vec3&rhs)
	{
		return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	inline Vec3 operator-(const Vec3& lhs, const Vec3&rhs)
	{
		return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	inline Vec3 operator*(const Vec3& lhs, const Vec3&rhs)
	{
		return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	inline Vec3 operator/(const Vec3& lhs, const Vec3&rhs)
	{
		return Vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	inline Vec3 operator*(real t, const Vec3& rhs)
	{
		return Vec3(t * rhs.x, t * rhs.y, t * rhs.z);
	}

	inline Vec3 operator*(const Vec3& lhs, real t)
	{
		return Vec3(t * lhs.x, t * lhs.y, t * lhs.z);
	}

	inline Vec3 operator/(const Vec3& lhs, real t)
	{
		real inv_t = 1.0f / t;
		return Vec3(lhs.x * inv_t, lhs.y * inv_t, lhs.z * inv_t);
	}

	inline Vec3 min(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(
			lhs.x < rhs.x ? lhs.x : rhs.x,
			lhs.y < rhs.y ? lhs.y : rhs.y,
			lhs.z < rhs.z ? lhs.z : rhs.z
		);
	}

	inline Vec3 max(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(
			lhs.x > rhs.x ? lhs.x : rhs.x,
			lhs.y > rhs.y ? lhs.y : rhs.y,
			lhs.z > rhs.z ? lhs.z : rhs.z
		);
	}

	inline real dot(const Vec3& lhs, const Vec3& rhs)
	{
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}

	inline Vec3 cross(const Vec3& lhs, const Vec3& rhs)
	{
		return Vec3(
			lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1],
		    -(lhs.e[0] * rhs.e[2] - lhs.e[2] * rhs.e[0]),
			lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]
		);
	}

	inline Vec3 make_unit(const Vec3& vec)
	{
		return vec / vec.length();
	}

	inline Vec3 reflect(const Vec3& incidence, const Vec3& normal)
	{
		return incidence - 2 * dot(incidence, normal) * normal;
	}

	bool refract(const Vec3& incidence, const Vec3& normal, real ni_over_nt, Vec3& refracted);
}

#endif//OW_VEC3_H