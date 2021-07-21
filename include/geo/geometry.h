#pragma once

// If no user settings defined, set the default coordinate system as right handed
#if !defined(GEOMETRY_LEFT_HANDED) && !defined(GEOMETRY_RIGHT_HANDED)
#define GEOMETRY_RIGHT_HANDED
#endif
// If no user settings defined, set the default clip space to GEOMETRY_CLIP_SPACE_NEGATIVE
// GEOMETRY_CLIP_SPACE_NEGATIVE -> clip space [-1, 1] (GL)
// GEOMETRY_CLIP_SPACE_POSITIVE -> clip space [0, 1] (D3D)
#if !defined(GEOMETRY_CLIP_SPACE_NEGATIVE) && !defined(GEOMETRY_CLIP_SPACE_POSITIVE)
#define GEOMETRY_CLIP_SPACE_NEGATIVE
#endif
// Precision of library
#if !defined(GEOMETRY_SINGLE_PRECISION) && !defined(GEOMETRY_DOUBLE_PRECISION)
#define GEOMETRY_SINGLE_PRECISION
#endif

#include <geo/math/scientific.h>
#include <geo/math/sampling.h>
#include <geo/math/coordinates.h>
#include <geo/math/angle.h>
#include <geo/math/half.h>
#include <geo/math/random.h>
#include <geo/math/frustum.h>
#include <geo/math/aabbox.h>
#include <geo/color/color4.h>
#include <geo/vector/vec2.h>
#include <geo/vector/vec3.h>
#include <geo/vector/vec4.h>
#include <geo/vector/point3.h>
#include <geo/vector/norm3.h>
#include <geo/vector/uv2.h>
#include <geo/matrix/mat3.h>
#include <geo/matrix/mat4.h>
#include <geo/matrix/quat.h>
#include <geo/core/print.h>

namespace geometry {

using quatf = quat<float>;
using quatd = quat<double>;

using uv2f = uv2<float>;
using uv2d = uv2<double>;

using point3f = point3<float>;
using point3d = point3<double>;
using norm3f = norm3<float>;
using norm3d = norm3<double>;

using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2i = vec2<int32_t>;
using vec2u = vec2<uint32_t>;
using vec3f = vec3<float>;
using vec3d = vec3<double>;
using vec3i = vec3<int32_t>;
using vec3u = vec3<uint32_t>;
using vec4f = vec4<float>;
using vec4d = vec4<double>;

using color3f = color3<float>;
using color24 = color3<uint8_t>;
using color4f = color4<float>;
using color32 = color4<uint8_t>;

using col3f = col3<float>;
using col3d = col3<double>;
using mat3f = mat3<float>;
using mat3d = mat3<double>;

using col4f = col4<float>;
using col4d = col4<double>;
using mat4f = mat4<float>;
using mat4d = mat4<double>;

using anglef = angle<float>;
using angled = angle<double>;

}

#include <geo/math/scientific.inl>
#include <geo/math/sampling.inl>
#include <geo/math/coordinates.inl>
#include <geo/math/angle.inl>
#include <geo/math/half.inl>
#include <geo/math/random.inl>
#include <geo/math/frustum.inl>
#include <geo/math/aabbox.inl>
#include <geo/color/color3.inl>
#include <geo/color/color4.inl>
#include <geo/vector/vec2.inl>
#include <geo/vector/vec3.inl>
#include <geo/vector/vec4.inl>
#include <geo/vector/point3.inl>
#include <geo/vector/norm3.inl>
#include <geo/vector/uv2.inl>
#include <geo/matrix/mat3.inl>
#include <geo/matrix/mat4.inl>
#include <geo/matrix/quat.inl>