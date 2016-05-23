#include "Sphere.h"

namespace ow
{
	bool Sphere::hit(const Ray& ray, real t_min, real t_max, HitInfo& hit_info) const
	{
		Vec3 ray2center = ray.origin - center;
		real a = dot(ray.direction, ray.direction);
		real b = dot(ray2center, ray.direction);
		real c = dot(ray2center, ray2center) - radius*radius;
		real discriminant = b*b - a*c;
		if (discriminant > 0)
		{
			real t = (-b - sqrt(discriminant)) / a;
			if (t < t_max && t > t_min)
			{
				hit_info.t = t;
				hit_info.p = ray.pointAtParameter(t);
				hit_info.normal = (hit_info.p - center) / radius;
				return true;
			}
			t = (-b + sqrt(discriminant)) / a;
			if (t < t_max && t > t_min)
			{
				hit_info.t = t;
				hit_info.p = ray.pointAtParameter(t);
				hit_info.normal = (hit_info.p - center) / radius;
				return true;
			}
		}
		return false;
	}
}