#ifndef OW_MATERIAL_H
#define OW_MATERIAL_H

#include "Ray.h"
#include "Hitable.h"
#include "Misc.h"
#include "RNG.h"

namespace ow
{
	class Material : public Noncopyable
	{
	public:
		virtual ~Material() {}
		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const = 0;
	};

	class Lambertian final : public Material
	{
	public:
		Vec3 albedo;
	public:
		Lambertian(const Vec3& albedo):
			albedo(albedo)
		{}

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override
		{
			Vec3 target = hit_info.p + hit_info.normal + RNG::randomInUnitSphere();
			scattered = Ray(hit_info.p, target - hit_info.p);
			attenuation = albedo;
			return true;
		}
	};

	class Metal final : public Material
	{
	public:
		Vec3 albedo;
	public:
		Metal(const Vec3& albedo)
			:albedo(albedo)
		{}

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override
		{
			Vec3 reflected = reflect(make_unit(in.direction), hit_info.normal);
			scattered = Ray(hit_info.p, reflected);
			attenuation = albedo;
			return dot(scattered.direction, hit_info.normal) > 0;
		}
	};

	inline real schlick(real cosine, real ref)
	{
		real r0 = (1 - ref) / (1 + ref);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
}

#endif//OW_MATERIAL_H