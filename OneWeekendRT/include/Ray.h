#ifndef OW_RAY_H
#define OW_RAY_H

#include "Vec3.h"

namespace ow
{
	class Ray final
	{
	public:
		Vec3 origin;
		Vec3 direction;
	public:
		Ray() {}
		Ray(const Vec3& origin, const Vec3& direction)
			:origin(origin), direction(direction)
		{}

		Vec3 pointAtParameter(real t) const
		{
			return origin + t*direction;
		}
	};
}

#endif//OW_RAY_H