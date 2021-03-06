#pragma once

#include <geo/math/scientific.h>

namespace geometry {

template <typename T>
struct point3;
template <typename T>
struct vec3;
template <typename T>
struct col3;
template <typename T>
struct col4;

template <typename T = real_t>
struct norm3 {
	union {
		T data[3];
		struct {
			T x, y, z;
		};
	};

	norm3();
	explicit norm3(T value);
	explicit norm3(T x, T y, T z);
	explicit norm3(const vec3<T> &vec);
	explicit norm3(const col3<T> &col);
	explicit norm3(const col4<T> &col);
	explicit norm3(const point3<T> &point);

	T &operator[](size_t index);
	const T &operator[](size_t index) const;

	T norm() const;

	static T dot(const norm3 &lhs, const norm3 &rhs);
	static norm3 normalize(const norm3 &vec);
	static norm3 faceForward(const norm3 &n, const vec3<T> &v);
};

template <typename T>
bool operator==(const norm3<T> &lhs, const norm3<T> &rhs);
template <typename T>
bool operator!=(const norm3<T> &lhs, const norm3<T> &rhs);

template <typename T>
norm3<T> operator*(const norm3<T> &lhs, real_t rhs);
template <typename T>
norm3<T> operator*(real_t lhs, const norm3<T> &rhs);
template <typename T>
norm3<T> &operator*=(norm3<T> &lhs, real_t rhs);

template <typename T>
norm3<T> operator/(const norm3<T> &lhs, real_t rhs);
template <typename T>
norm3<T> &operator/=(norm3<T> &lhs, real_t rhs);

template <typename T>
norm3<T> operator+(const norm3<T> &lhs, const norm3<T> &rhs);
template <typename T>
norm3<T> &operator+=(norm3<T> &lhs, const norm3<T> &rhs);

template <typename T>
norm3<T> operator-(const norm3<T> &lhs, const norm3<T> &rhs);
template <typename T>
norm3<T> &operator-=(norm3<T> &lhs, const norm3<T> &rhs);

template <typename T>
norm3<T> operator-(const norm3<T> &vec);


}
