#pragma once

#include <cstdlib>

#include <geo/core/types.h>

namespace geometry {

// Generate a random number between 0 & 1 if floating point, 0 & max if integer
template <typename T = real_t> T random();

// Generate a random number between -range & +range
template <typename T = real_t> T random(T range);

// Generate a random number between start & end
template <typename T = real_t> T random(T start, T end);

}