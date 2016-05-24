#ifndef OW_RNG_H
#define OW_RNG_H

#include "Vec3.h"
#include "Misc.h"
#include <random>

namespace ow
{
	class RNG final : public Noncopyable
	{
	public:
		inline static real rng()
		{
			RNG& rng = instance();
			return rng.uniform_distribution(rng.random_engine);
		}

		static Vec3 randomInUnitSphere()
		{
			Vec3 p;
			do {
				p = 2.0f * Vec3(rng(), rng(), rng()) - Vec3(1, 1, 1);
			} while (p.lengthSquared() >= 1.0);
			return p;
		}
	private:
		RNG();
		static RNG& instance();

		std::random_device random_device;
		std::mt19937_64 random_engine;
		std::uniform_real_distribution<real> uniform_distribution;
	};
}

#endif//OW_RNG_H