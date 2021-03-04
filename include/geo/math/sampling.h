#pragma once

#include <geo/math/angle.h>
#include <geo/math/coordinates.h>
#include <geo/vector/vec3.h>

namespace geometry {

template <typename T>
vec2<T> reflect(const vec2<T>& wi, const vec2<T>& normal);

template <typename T>
vec3<T> reflect(const vec3<T>& wi, const norm3<T>& normal);

template <typename T>
bool refract(vec3<T>& wo, const vec3<T>& wi, const norm3<T>& normal, real_t eta);

}
