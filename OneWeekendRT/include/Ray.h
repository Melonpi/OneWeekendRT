#ifndef OW_RAY_H
#define OW_RAY_H

#include "Vec3.h"

namespace ow
{
	struct Ray final
	{
	public:
		Vec3 origin;
		Vec3 direction;
		real time;
	public:
		Ray() {}
		Ray(const Ray& ray)
			:origin(ray.origin), direction(ray.direction)
		{}
		Ray(const Vec3& origin, const Vec3& direction, real time = 0.0)
			:origin(origin), direction(direction), time(time)
		{}

		Vec3 pointAtParameter(real t) const
		{
			return origin + t*direction;
		}
	};
}

#endif//OW_RAY_H