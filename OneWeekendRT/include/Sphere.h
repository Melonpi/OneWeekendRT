#ifndef OW_SPHERE_H
#define OW_SPHERE_H

#include "Hitable.h"
#include "Ray.h"
#include "Vec3.h"

namespace ow
{
	class Sphere final : public Hitable
	{
	public:
		Vec3 center;
		real radius;
	public:
		Sphere()
			:center(Vec3(0, 0, 0)), radius(1.0)
		{}
		Sphere(const Vec3& center, float radius)
			:center(center), radius(radius)
		{}
		~Sphere()
		{}

		virtual bool hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const override;
	};
}

#endif//OW_SPHERE_H