#ifndef OW_HITABLE_H
#define OW_HITABLE_H

#include "Vec3.h"
#include "Ray.h"

namespace ow
{
	struct HitInfo final
	{
		real t;
		Vec3 p;
		Vec3 normal;
	};

	class Hitable
	{
	public:
		virtual ~Hitable() = 0;
		virtual bool hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const;
	};
}

#endif//OW_HITABLE_H