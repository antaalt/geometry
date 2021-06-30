#pragma once

#include <geo/matrix/mat4.h>

namespace geometry {

template <typename T = real_t>
struct frustum
{
	point3<T> corners[8];

	static frustum<T> fromProjection(const mat4<T>& projection);
	static frustum<T> fromInverseProjection(const mat4<T>& inverseProjection);

	point3<T> center() const;

	point3<T>* data() { return m_corners; }
	const point3<T>* data() const { return m_corners; }

	bool operator==(const frustum<T>& rhs) const;
	bool operator!=(const frustum<T>& rhs) const;
};

};