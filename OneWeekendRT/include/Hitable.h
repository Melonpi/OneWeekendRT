#ifndef OW_HITABLE_H
#define OW_HITABLE_H

#include "Vec3.h"
#include "Ray.h"
#include "Misc.h"
#include <memory>

namespace ow
{
	class Material;
	struct HitInfo final
	{
	public:
		real t;
		Vec3 p;
		Vec3 normal;
		std::shared_ptr<Material> material;
	public:
		HitInfo()
			:t(REAL_MAX)
		{}
	};

	class Hitable : public Noncopyable
	{
	public:
		Hitable() {}
		Hitable(const Hitable&) = delete;
		const Hitable& operator=(const Hitable&) = delete;
		virtual ~Hitable() {}
		virtual bool hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const = 0;
	};
}

#endif//OW_HITABLE_H