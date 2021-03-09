#pragma once

#include <geo/core/sfinae.h>
#include <geo/math/scientific.h>

namespace geometry {

template <typename T>
struct vec3;
template <typename T>
struct vec2;
template <typename T>
struct col4;


template <typename T = real_t>
struct vec4 {
	union {
		T data[4];
		struct {
			T x, y, z, w;
		};
	};
	vec4();
	explicit vec4(T value);
	explicit vec4(T x, T y, T z, T w);
	explicit vec4(const vec2<T> &vec, T z, T w);
	explicit vec4(const vec3<T> &vec, T w);
	explicit vec4(const col4<T> &vec);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	template <typename U = T, typename = IsFloatingPoint<U>>
	T norm() const;

	template <typename U = T, typename = IsFloatingPoint<U>>
	static vec4 normalize(const vec4 &vec);
	template <typename U = T, typename = IsFloatingPoint<U>>
	static T dot(const vec4 & lhs, const vec4 & rhs);
};

template <typename T>
bool operator==(const vec4<T> & lhs, const vec4<T> & rhs);
template <typename T>
bool operator!=(const vec4<T> &lhs, const vec4<T> &rhs);

template <typename T>
vec4<T> operator*(const vec4<T> &lhs, T rhs);
template <typename T>
vec4<T> operator*(T lhs, const vec4<T> &rhs);
template <typename T>
vec4<T> &operator*=(vec4<T> &lhs, T rhs);

template <typename T>
vec4<T> operator/(const vec4<T> &lhs, T rhs);
template <typename T>
vec4<T> &operator/=(vec4<T> &lhs, T rhs);

template <typename T>
vec4<T> operator+(const vec4<T> &lhs, const vec4<T> &rhs);
template <typename T>
vec4<T> &operator+=(vec4<T> &lhs, const vec4<T> &rhs);

template <typename T>
vec4<T> operator-(const vec4<T> &lhs, const vec4<T> &rhs);
template <typename T>
vec4<T> &operator-=(vec4<T> &lhs, const vec4<T> &rhs);

template <typename T>
vec4<T> operator-(const vec4<T> &vec);

}