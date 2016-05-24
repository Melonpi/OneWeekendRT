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

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override;
	};

	class Metal final : public Material
	{
	public:
		Vec3 albedo;
		real fuzz;
	public:
		Metal(const Vec3& albedo, real fuzz)
			:albedo(albedo), fuzz(fuzz)
		{}

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override;
	};

	class Dielectric : public Material
	{
	public:
		real ref_idx;
	public:
		Dielectric(real ri)
			:ref_idx(ri)
		{}

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override;
	};

	inline real schlick(real cosine, real ref)
	{
		real r0 = (1 - ref) / (1 + ref);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
}

#endif//OW_MATERIAL_H