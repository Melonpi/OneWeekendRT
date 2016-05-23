#ifndef OW_TYPES_H
#define OW_TYPES_H

#include <stdint.h>

namespace ow
{
#ifndef OW_USE_DOUBLE
    typedef float real;
#else
    typedef double real;
#endif
}

#endif//OW_TYPES_H