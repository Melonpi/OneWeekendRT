#ifndef OW_MATERIAL_H
#define OW_MATERIAL_H

#include "Ray.h"
#include "Hitable.h"
#include "Misc.h"
#include "RNG.h"
#include "Texture.h"

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
		explicit Lambertian(std::unique_ptr<Texture>&& albedo)
			:albedo_(std::move(albedo))
		{}

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override;
	private:
		std::unique_ptr<Texture> albedo_;
	};

	class Metal final : public Material
	{
	public:
		Vec3 albedo;
		real fuzz;
	public:
		Metal(const Vec3& albedo, real fuzz)
			:albedo(albedo), fuzz(fuzz)
		{
			OW_EXPECT(fuzz >= 0 && fuzz <= 1.0);
		}

		virtual bool scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const override;
	};

	class Dielectric : public Material
	{
	public:
		real ref_idx;
	public:
		explicit Dielectric(real ri)
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