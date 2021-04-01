#pragma once
#include <geo/math/scientific.h>

namespace geometry {

template <typename T>
struct norm3;
template <typename T>
struct point3;
template <typename T>
struct vec3;
template <typename T>
struct quat;

template <typename T = real_t>
struct col4 {
	union {
		T data[4];
		struct {
			T x, y, z, w;
		};
	};
	col4();
	col4(T value);
	col4(T x, T y, T z, T w);
	template <typename U>
	col4(U x, U y, U z, U w);
	col4(norm3<T> vec, T w);
	col4(vec3<T> vec, T w);
	col4(vec4<T> vec);
	col4(point3<T> vec, T w);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;
};

template <typename T = real_t>
struct mat4 {

	col4<T> cols[4];

	mat4();
	mat4(T value);
	mat4(col4<T> x, col4<T> y, col4<T> z, col4<T> w);
	mat4(const quat<T> &quat);

	col4<T> &operator[](size_t index);
	const col4<T> &operator[](size_t index) const;

	static mat4 identity();
	static mat4 translate(const vec3<T> &translation);
	static mat4 rotate(const vec3<T> &axis, angle<T> angle);
	static mat4 rotate(const quat<T>& quat);
	static mat4 scale(const vec3<T> &scale);
	static mat4 TRS(const vec3<T> & t, const quat<T> & r, const vec3<T> & s);
	static mat4 inverse(const mat4 &mat);
	static mat4 transpose(const mat4& mat);
	static mat4 perspective(const angle<T> &fovY, real_t ratio, real_t nearZ, real_t farZ);
	static mat4 orthographic(real_t bottom, real_t top, real_t left, real_t right);
	static mat4 orthographic(real_t bottom, real_t top, real_t left, real_t right, real_t nearZ, real_t farZ);
	static mat4 lookAt(const point3<T> & eye, const point3<T> & target, const norm3<T> &up = norm3<T>(0, 1, 0));
	static mat4 from2D(const mat3<T>& mat);

	T det() const;
	point3<T> multiplyPoint3x4(const point3<T>& point) const;
	point3<T> multiplyPoint(const point3<T>& point) const;
	vec3<T> multiplyVector(const vec3<T>& vector) const;
};

template <typename T>
mat4<T> operator*(const mat4<T>& lhs, const mat4<T> &rhs);
template <typename T>
mat4<T> &operator*=(mat4<T>& lhs, const mat4<T> &rhs);
template <typename T>
point3<T> operator*(const mat4<T>& lhs, const point3<T> &rhs);
template <typename T>
vec3<T> operator*(const mat4<T>& lhs, const vec3<T> &rhs);
template <typename T>
vec4<T> operator*(const mat4<T>& lhs, const vec4<T> &rhs);

}
