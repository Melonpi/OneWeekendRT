#ifndef OW_CAMERA_H
#define OW_CAMERA_H

#include "Types.h"
#include "Ray.h"
#include "Misc.h"

namespace ow
{
	class Camera final : public Noncopyable
	{
	public:
		Camera(const Vec3& lookfrom, const Vec3& lookat, const Vec3& up, real fov, real aspect)
		{
			Vec3 u, v, w;
			real theta = fov * M_PI / 180.0f;
			real half_height = tan(theta / 2);
			real half_width = aspect * half_height;

			origin_ = lookfrom;
			w = make_unit(lookfrom - lookat);
			u = make_unit(cross(up, w));
			v = cross(w, u);

			lower_left_corner_ = origin_ - half_width*u - half_height*v - w;
			horizontal_ = 2 * half_width*u;
			vertical_ = 2*half_height*v;
		}

		Ray getRay(real u, real v) const
		{
			return Ray(origin_, lower_left_corner_ + u*horizontal_ + v*vertical_ - origin_);
		}
	private:
		Vec3 origin_;
		Vec3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
	};
}

#endif//OW_CAMERA_H