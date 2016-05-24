#ifndef OW_CAMERA_H
#define OW_CAMERA_H

#include "Types.h"
#include "Ray.h"
#include "Misc.h"
#include "RNG.h"

namespace ow
{
	class Camera final : public Noncopyable
	{
	public:
		Camera(const Vec3& lookfrom, const Vec3& lookat, const Vec3& up, real fov, real aspect, real aperture, real focus_dist)
		{
			lens_radius_ = aperture / 2;
			real theta = fov * M_PI / 180.0f;
			real half_height = tan(theta / 2);
			real half_width = aspect * half_height;

			origin_ = lookfrom;
			w_ = make_unit(lookfrom - lookat);
			u_ = make_unit(cross(up, w_));
			v_ = cross(w_, u_);

			lower_left_corner_ = origin_ - half_width*focus_dist*u_ - half_height*focus_dist*v_ - focus_dist*w_;
			horizontal_ = 2 * half_width*focus_dist*u_;
			vertical_ = 2*half_height*focus_dist*v_;
		}

		Ray getRay(real u, real v) const
		{
			Vec3 ray = lens_radius_ * RNG::randomInUnitDisk();
			Vec3 offset = u_ * ray.x + v_ * ray.y;
			return Ray(origin_ + offset, lower_left_corner_ + u*horizontal_ + v*vertical_ - origin_ - offset);
		}
	private:
		Vec3 origin_;
		Vec3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
		Vec3 u_, v_, w_;
		real lens_radius_;
	};
}

#endif//OW_CAMERA_H