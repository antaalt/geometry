#pragma once

#include "scientific.h"

namespace geometry {

template <typename T>
struct vec2;
template <typename T>
struct mat4;

template <typename T>
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

	T &operator[](size_t index);
	const T &operator[](size_t index) const;
};

template <typename T>
struct mat3 {

	col3<T> cols[3];

	mat3();
	mat3(T value);
	mat3(col3<T> x, col3<T> y, col3<T> z);

	col3<T> &operator[](size_t index);
	const col3<T> &operator[](size_t index) const;

	static mat3 identity();
	static mat3 translate(const vec2<T>& translation);
	static mat3 rotate(radian<T> angle);
	static mat3 scale(const vec2<T>& scale);
	static mat3 TRS(const vec2<T>& t, radian<T> r, const vec2<T>& s);
};

template <typename T>
mat3<T> operator*(const mat3<T>& lhs, const mat3<T> &rhs);
template <typename T>
vec2<T> operator*(const mat3<T>& lhs, const vec2<T>& rhs);

}