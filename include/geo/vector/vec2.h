#pragma once

#include <geo/core/sfinae.h>
#include <geo/math/scientific.h>

namespace geometry {

template <typename T>
struct vec3;
template <typename T>
struct vec4;
template <typename T>
struct uv2;

template <typename T = real_t>
struct vec2 {
	union {
		T data[2];
		struct {
			T x, y;
		};
	};
	vec2();
	explicit vec2(T value);
	explicit vec2(T x, T y);
	template <typename U>
	explicit vec2(U x, U y);
	template <typename U>
	explicit vec2(const vec2<U> &vec);
	explicit vec2(const uv2<T> &uv);
	explicit vec2(const vec3<T> &vec);
	explicit vec2(const vec4<T> &vec);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	template <typename U = T, typename = IsFloatingPoint<U>>
	T norm() const;

	template <typename U = T, typename = IsFloatingPoint<U>>
	static T dot(const vec2 &lhs, const vec2 &rhs);
	template <typename U = T, typename = IsFloatingPoint<U>>
	static vec2<T> normalize(const vec2& vec);
	static vec2<T> abs(const vec2<T>& vec);
	static vec2<T> min(const vec2& lhs, const vec2& rhs);
	static vec2<T> max(const vec2& lhs, const vec2& rhs);
};

template <typename T>
bool operator==(const vec2<T> & lhs, const vec2<T> & rhs);
template <typename T>
bool operator!=(const vec2<T> &lhs, const vec2<T> &rhs);
template <typename T>
bool operator<(const vec2<T>& lhs, const vec2<T>& rhs);
template <typename T>
bool operator>(const vec2<T>& lhs, const vec2<T>& rhs);
template <typename T>
bool operator<=(const vec2<T>& lhs, const vec2<T>& rhs);
template <typename T>
bool operator>=(const vec2<T>& lhs, const vec2<T>& rhs);

template <typename T>
vec2<T> operator*(const vec2<T> &lhs, T rhs);
template <typename T>
vec2<T> operator*(T lhs, const vec2<T> &rhs);
template <typename T>
vec2<T> operator*(const vec2<T> &lhs, const vec2<T> &rhs);
template <typename T>
vec2<T> &operator*=(vec2<T> &lhs, T rhs);
template <typename T>
vec2<T> &operator*=(vec2<T> &lhs, const vec2<T>& rhs);

template <typename T>
vec2<T> operator/(const vec2<T> &lhs, T rhs);
template <typename T>
vec2<T> operator/(const vec2<T> &lhs, const vec2<T> &rhs);
template <typename T>
vec2<T> &operator/=(vec2<T> &lhs, T rhs);
template <typename T>
vec2<T> &operator/=(vec2<T> &lhs, const vec2<T> &rhs);

template <typename T>
vec2<T> operator+(const vec2<T> &lhs, const vec2<T> &rhs);
template <typename T>
vec2<T> &operator+=(vec2<T> &lhs, const vec2<T> &rhs);

template <typename T>
vec2<T> operator-(const vec2<T> &lhs, const vec2<T> &rhs);
template <typename T>
vec2<T> &operator-=(vec2<T> &lhs, const vec2<T> &rhs);

template <typename T>
vec2<T> operator-(const vec2<T> &vec);

}