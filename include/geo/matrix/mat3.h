#pragma once

#include <geo/math/scientific.h>

namespace geometry {

template <typename T>
struct vec2;
template <typename T>
struct mat4;
template <typename T>
struct col4;

template <typename T = real_t>
struct col3 {
	union {
		T data[3];
		struct {
			T x, y, z;
		};
	};
	col3();
	col3(T value);
	col3(const vec2<T> &xy, T z);
	col3(T x, T y, T z);
	col3(const col4<T> &);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;
};

template <typename T = real_t>
struct mat3 {

	col3<T> cols[3];

	mat3();
	mat3(T value);
	mat3(col3<T> x, col3<T> y, col3<T> z);
	mat3(const mat4<T>& mat);

	col3<T> &operator[](size_t index);
	const col3<T> &operator[](size_t index) const;

	vec2<T> multiplyPoint(const vec2<T>& point) const;
	vec2<T> multiplyVector(const vec2<T>& point) const;

	static mat3 identity();
	static mat3 translate(const vec2<T>& translation);
	static mat3 rotate(angle<T> angle);
	static mat3 scale(const vec2<T>& scale);
	static mat3 TRS(const vec2<T>& t, angle<T> r, const vec2<T>& s);
	static mat3 inverse(const mat3& mat);
	static mat3 transpose(const mat3& mat);

	T det() const;

};

template <typename T>
mat3<T> operator*(const mat3<T>& lhs, const mat3<T> &rhs);
template <typename T>
vec3<T> operator*(const mat3<T>& lhs, const vec3<T>& rhs);
template <typename T>
vec2<T> operator*(const mat3<T>& lhs, const vec2<T>& rhs);
template <typename T>
mat3<T>& operator*=(mat3<T>& lhs, const mat3<T>& rhs);

}