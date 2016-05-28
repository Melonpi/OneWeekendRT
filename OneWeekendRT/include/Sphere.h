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
		std::shared_ptr<Material> material;
	public:
		Sphere(const Vec3& center, real radius, std::shared_ptr<Material> material)
			:center(center), radius(radius), material(material)
		{}
		~Sphere()
		{}

		virtual bool hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const override;
	};
	
	class MovingSphere : public Hitable
	{
	public:
		MovingSphere() {}
		MovingSphere(const Vec3& start_center, const Vec3& end_center, real start_time, real end_time, real radius, std::shared_ptr<Material> material)
			:start_center(start_center), end_center(end_center),start_time(start_time),end_time(end_time),
			 radius(radius), material(material)
		{}
		~MovingSphere() {}

		virtual bool hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const override;
		Vec3 getCenter(real time) const
		{
			return start_center + ((time - start_time) / (end_time - start_time)) * (end_center - start_center);
		}
	private:
		Vec3 start_center;
		Vec3 end_center;
		real start_time;
		real end_time;
		real radius;
		std::shared_ptr<Material> material;
	};
}

#endif//OW_SPHERE_H