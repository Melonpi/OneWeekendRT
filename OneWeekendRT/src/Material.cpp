#include "Material.h"

namespace ow
{
	bool Lambertian::scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 target = hit_info.p + hit_info.normal + RNG::randomInUnitSphere();
		scattered = Ray(hit_info.p, target - hit_info.p);
		attenuation = albedo;
		return true;
	}

	bool Metal::scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 reflected = reflect(make_unit(in.direction), hit_info.normal);
		scattered = Ray(hit_info.p, reflected + fuzz*RNG::randomInUnitSphere());
		attenuation = albedo;
		return dot(scattered.direction, hit_info.normal) > 0;
	}

	bool Dielectric::scatter(const Ray& in, const HitInfo& hit_info, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 outward_normal;
		Vec3 reflected = reflect(in.direction, hit_info.normal);
		real ni_over_nt;
		attenuation = Vec3(1.0, 1.0, 1.0);

		real reflect_ratio;
		real cosine;
		if (dot(in.direction, hit_info.normal) > 0)
		{
			outward_normal = -hit_info.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(in.direction, hit_info.normal);
		}else{
			outward_normal = hit_info.normal;
			ni_over_nt = 1.0f / ref_idx;
			cosine = -dot(in.direction, hit_info.normal) / in.direction.length();
		}

		Vec3 refracted;
		if (refract(in.direction, outward_normal, ni_over_nt, refracted))
		{
			reflect_ratio = schlick(cosine, ref_idx);
		}else{
			scattered = Ray(hit_info.p, reflected);
			reflect_ratio = 1.0;
		}
		if (RNG::rng() < reflect_ratio)
		{
			scattered = Ray(hit_info.p, reflected);
		}else{
			scattered = Ray(hit_info.p, refracted);
		}

		return true;
	}
}