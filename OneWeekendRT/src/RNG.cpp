#include "RNG.h"

namespace ow
{
	RNG::RNG()
	{
		random_engine = std::mt19937_64(random_device());
		uniform_distribution = std::uniform_real_distribution<real>(0, 1);
	}

	RNG& RNG::instance()
	{
		static RNG instance;
		return instance;
	}
}