#ifndef OW_TYPES_H
#define OW_TYPES_H

#include <stdint.h>
#include <float.h>

namespace ow
{
#ifndef OW_USE_DOUBLE
    typedef float real;
	static const real REAL_EPS = 1e-8f;
	static const real REAL_MAX = FLT_MAX;
	static const real M_PI = 3.14159265358f;
#else
    typedef double real;
	static const real REAL_EPS = 1e-8;
	static const real REAL_MAX = FLT_MAX;
	static const real M_PI = 3.14159265358;
#endif
}

#endif//OW_TYPES_H