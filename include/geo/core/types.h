#pragma once

#include <stdint.h>

namespace geometry {

#if defined(GEOMETRY_DOUBLE_PRECISION)
using real_t = double;
#else
using real_t = float;
#endif
using byte = uint8_t;

};