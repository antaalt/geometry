#pragma once

#include <geo/math/scientific.h>
#include <geo/vector/vec3.h>

namespace geometry {

template <typename T = real_t>
struct quat {
	union {
		T data[4];
		struct {
			T x, y, z, w;
		};
	};
	quat();
	template <typename U>
	explicit quat(U x, U y, U z, U w);
	explicit quat(T x, T y, T z, T w);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	T norm() const;

	static quat identity();
	static quat conjuguate(const quat &quaternion);
	static quat normalize(const quat &quaternion);
	static quat axis(const vec3<T> &axis, const radian<T> &angle);
	static quat euler(radian<T> yaw, radian<T> pitch, radian<T> roll); // z, y, x

	quat operator*(real_t scalar) const;
	quat &operator*=(real_t scalar);

	quat operator*(const quat &rhs) const;
	quat &operator*=(const quat &rhs);

	quat operator+(const quat &rhs) const;
	quat &operator+=(const quat &rhs);

	quat operator-(const quat &rhs) const;
	quat &operator-=(const quat &rhs);

	vec3<T> operator*(const vec3<T> &rhs);
};

}
