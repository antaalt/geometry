#pragma once

#include <geo/math/scientific.h>

namespace geometry {

template <typename T>
struct vec3;
template <typename T>
struct vec4;

template <typename T>
struct color3 {
	union {
		T data[3];
		struct {
			T r, g, b;
		};
	};
	color3();
	explicit color3(T value);
	template <typename U>
	explicit color3(const color3<U> &value);
	explicit color3(T r, T g, T b);
	explicit color3(const vec3<T> &vec);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	T luminance() const;

	static color3<T> srgb2linear(const color3<T> &color);
	static color3<T> linear2srgb(const color3<T> &color);
};

template <typename T>
bool operator==(const color3<T> &lhs, const color3<T> &rhs);
template <typename T>
bool operator!=(const color3<T> &lhs, const color3<T> &rhs);

template <typename T>
color3<T> operator*(const color3<T> &lhs, const color3<T> &rhs);
template <typename T>
color3<T> operator*(const color3<T> &lhs, real_t rhs);
template <typename T>
color3<T> operator*(T rhs, const color3<T> &lhs);
template <typename T>
color3<T> &operator*=(color3<T> &lhs, const color3<T> &rhs);
template <typename T>
color3<T> &operator*=(color3<T> &lhs, real_t rhs);

template <typename T>
color3<T> operator/(const color3<T> &lhs, real_t rhs);
template <typename T>
color3<T> &operator/=(color3<T> &lhs, real_t rhs);

template <typename T>
color3<T> operator+(const color3<T> &lhs, const color3<T> &rhs);
template <typename T>
color3<T> &operator+=(color3<T> &lhs, const color3<T> &rhs);

template <typename T>
color3<T> operator-(const color3<T> &lhs, const color3<T> &rhs);
template <typename T>
color3<T> &operator-=(color3<T> &lhs, const color3<T> &rhs);

template <typename T>
color3<T> operator-(const color3<T> &vec);

}