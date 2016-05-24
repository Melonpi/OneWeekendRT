#ifndef OW_CAMERA_H
#define OW_CAMERA_H

#include "Ray.h"
#include "Misc.h"

namespace ow
{
	class Camera final : public Noncopyable
	{
	public:
		Camera()
		{
			lower_left_corner_ = { -2.0, -1.0, -1.0 };
			horizontal_ = { 4.0, 0.0, 0.0 };
			vertical_ = { 0.0, 2.0, 0.0 };
			origin_ = { 0.0, 0.0, 0.0 };
		}

		Ray getRay(real u, real v) const
		{
			return Ray(origin_, lower_left_corner_ + u*horizontal_ + v*vertical_);
		}
	private:
		Vec3 origin_;
		Vec3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
	};
}

#endif//OW_CAMERA_H