#ifndef OW_SPHERE_H
#define OW_SPHERE_H

#include "Hitable.h"
#include "Ray.h"
#include "Vec3.h"

namespace ow
{
	class Sphere : public Hitable
	{
	public:
		Vec3 center;
	};
}

#endif//OW_SPHERE_H