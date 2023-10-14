#pragma once

#include <geo/math/scientific.h>
#include <geo/vector/vec3.h>

namespace geometry {

template <typename T>
struct mat3;
template <typename T>
struct mat4;

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
	explicit quat(const mat3<T>& matrix);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	T norm() const;

	static quat identity();
	static quat inverse(const quat& quaternion);
	static quat conjuguate(const quat &quaternion);
	static quat normalize(const quat &quaternion);
	static quat axis(const vec3<T> &axis, const angle<T> &angle);
	static quat euler(angle<T> yaw, angle<T> pitch, angle<T> roll); // z, y, x
	static real_t dot(const quat& lhs, const quat& rhs);
	static quat slerp(const quat& from, const quat& to, real_t t);
};


template <typename T>
bool operator==(const quat<T>& lhs, const quat<T>& rhs);
template <typename T>
bool operator!=(const quat<T>& lhs, const quat<T>& rhs);

template <typename T>
quat<T> operator*(const quat<T>& lhs, real_t rhs);
template <typename T>
quat<T> operator*(real_t lhs, const quat<T>& rhs);
template <typename T>
quat<T>& operator*=(quat<T>& lhs, real_t rhs);

template <typename T>
quat<T> operator/(const quat<T>& lhs, real_t rhs);
template <typename T>
quat<T>& operator/=(quat<T>& lhs, real_t rhs);

template <typename T>
quat<T> operator*(const quat<T>& lhs, const quat<T>& rhs);
template <typename T>
quat<T>& operator*=(quat<T>& lhs, const quat<T>& rhs);

template <typename T>
quat<T> operator+(const quat<T>& lhs, const quat<T>& rhs);
template <typename T>
quat<T>& operator+=(quat<T>& lhs, const quat<T>& rhs);

template <typename T>
quat<T> operator-(const quat<T>& lhs, const quat<T>& rhs);
template <typename T>
quat<T>& operator-=(quat<T>& lhs, const quat<T>& rhs);

template <typename T>
quat<T> operator-(const quat<T>& quat);

template <typename T>
vec3<T> operator*(const quat<T>& lhs, const vec3<T>& rhs);

}
