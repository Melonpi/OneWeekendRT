#include "Vec3.h"

namespace ow
{
	bool refract(const Vec3& incidence, const Vec3& normal, real ni_over_nt, Vec3& refracted)
	{
		Vec3 uv = make_unit(incidence);
		real dt = dot(uv, normal);
		real discriminant = 1.0f - ni_over_nt * (1 - dt*dt);
		if (discriminant > 0)
		{
			refracted = ni_over_nt*(uv - normal*dt) - normal*sqrt(discriminant);
			return true;
		}
		else {
			return false;
		}
	}
}