#pragma once

#include <geo/matrix/mat4.h>
#include <geo/vector/vec4.h>
#include <geo/math/aabbox.h>

namespace geometry {

template <typename T = real_t>
struct frustum
{
	point3<T> corners[8];

	struct planes {
		vec4<T> planes[6]; // left, right, bottom, top, near, far

		bool intersect(const aabbox<T>& bound) const;
	};

	static planes extract(const mat4<T>& projection);

	static frustum<T> fromProjection(const mat4<T>& projection);
	static frustum<T> fromInverseProjection(const mat4<T>& inverseProjection);

	point3<T> center() const;

	bool operator==(const frustum<T>& rhs) const;
	bool operator!=(const frustum<T>& rhs) const;
};

};