#pragma once

#include <geo/core/sfinae.h>
#include <geo/math/scientific.h>
#include <geo/core/types.h>

namespace geometry {

template <typename T>
struct vec3;
template <typename T>
struct vec4;

template <typename T>
struct color4 {
	union {
		T data[4];
		struct {
			T r, g, b, a;
		};
	};
	color4();
	explicit color4(T value);
	explicit color4(T r, T g, T b, T a);
	template <typename U>
	explicit color4(const color4<U>& color);
	explicit color4(const vec3<T> &vec, T a);
	explicit color4(const vec4<T> &vec);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	real_t luminance() const;
	uint32_t toUint32();
	void fromUint32(uint32_t value);
	bool fromHexa(const char* hex_code);

	static color4<real_t> srgb2linear(const color4<byte_t> &color);
	static color4<byte_t> linear2srgb(const color4<real_t> &color);

	static color4<T> lerp(const color4<T>& a, const color4<T>& b, real_t t);
};

template <typename T>
bool operator==(const color4<T> &lhs, const color4<T> &rhs);
template <typename T>
bool operator!=(const color4<T> &lhs, const color4<T> &rhs);

template <typename T>
color4<T> operator*(const color4<T> &lhs, const color4<T> &rhs);
template <typename T>
color4<T> operator*(const color4<T> &lhs, real_t rhs);
template <typename T>
color4<T> operator*(T rhs, const color4<T> &lhs);
template <typename T>
color4<T> &operator*=(color4<T> &lhs, const color4<T> &rhs);
template <typename T>
color4<T> &operator*=(color4<T> &lhs, real_t rhs);

template <typename T>
color4<T> operator/(const color4<T> &lhs, real_t rhs);
template <typename T>
color4<T> &operator/=(color4<T> &lhs, real_t rhs);

template <typename T>
color4<T> operator+(const color4<T> &lhs, const color4<T> &rhs);
template <typename T>
color4<T> &operator+=(color4<T> &lhs, const color4<T> &rhs);

template <typename T>
color4<T> operator-(const color4<T> &lhs, const color4<T> &rhs);
template <typename T>
color4<T> &operator-=(color4<T> &lhs, const color4<T> &rhs);

template <typename T>
color4<T> operator-(const color4<T> &vec);

}