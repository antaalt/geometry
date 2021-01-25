#include "mat3.h"
#include "norm3.h"
#include "point3.h"
#include "vec3.h"
#include "quat.h"
#include "mat4.h"

namespace geometry {

template <typename T>
inline col3<T>::col3()
{
}

template <typename T>
inline col3<T>::col3(T value) : x(value), y(value), z(value)
{
}

template <typename T>
inline col3<T>::col3(const vec2<T>& xy, T z) : x(xy.x), y(xy.y), z(z)
{
}

template <typename T>
inline col3<T>::col3(T x, T y, T z) : x(x), y(y), z(z)
{
}

template <typename T>
inline T & col3<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T &col3<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
inline mat3<T>::mat3()
{
}

template <typename T>
inline mat3<T>::mat3(T value) : cols{ col3(value), col3(value), col3(value) }
{
}

template <typename T>
inline mat3<T>::mat3(col3<T> x, col3<T> y, col3<T> z) : cols{ x, y, z }
{
}

template <typename T>
inline col3<T> & mat3<T>::operator[](size_t index)
{
	return cols[index];
}

template <typename T>
inline const col3<T> & mat3<T>::operator[](size_t index) const
{
	return cols[index];
}

template <typename T>
vec2<T> mat3<T>::multiplyPoint(const vec2<T>& point) const
{
	return vec2<T>(
		cols[0].x * point.x + cols[1].x * point.y + cols[2].x,
		cols[0].y * point.x + cols[1].y * point.y + cols[2].y
	);
}

template <typename T>
vec2<T> mat3<T>::multiplyVector(const vec2<T>& point) const
{
	return vec2<T>(
		cols[0].x * point.x + cols[1].x * point.y,
		cols[0].y * point.x + cols[1].y * point.y
		);
}

template <typename T>
inline mat3<T> mat3<T>::identity()
{
	return mat3(
		col3<T>(1.f, 0.f, 0.f),
		col3<T>(0.f, 1.f, 0.f),
		col3<T>(0.f, 0.f, 1.f)
	);
}

template <typename T>
inline mat3<T> mat3<T>::translate(const vec2<T>& translation)
{
	return mat3(
		col3<T>(1.f, 0.f, 0.f),
		col3<T>(0.f, 1.f, 0.f),
		col3<T>(translation, 1.f)
	);
}

template <typename T>
inline mat3<T> mat3<T>::rotate(radian<T> angle)
{
	return mat3(
		col3<T>(cos(angle), -sin(angle), 0.f),
		col3<T>(sin(angle), cos(angle), 0.f),
		col3<T>(0.f, 0.f, 1.f)
	);
}

template <typename T>
inline mat3<T> mat3<T>::scale(const vec2<T>& scale)
{
	return mat3(
		col3<T>(scale.x, 0.f, 0.f),
		col3<T>(0.f, scale.y, 0.f),
		col3<T>(0.f, 0.f, 1.f)
	);
}

template <typename T>
inline mat3<T> mat3<T>::TRS(const vec2<T>& t, radian<T> r, const vec2<T>& s)
{
	return scale(s) * rotate(r) * translate(t);
}

template <typename T>
inline mat3<T> operator*(const mat3<T>& lhs, const mat3<T> &rhs)
{
	mat3<T> out(0.f);
	for (int iCol = 0; iCol < 3; iCol++)
		for (int iRow = 0; iRow < 3; iRow++)
			for (int k = 0; k < 3; k++)
				out[iCol][iRow] += rhs[iCol][k] * lhs[k][iRow];
	return out;
}

template <typename T>
vec2<T> operator*(const mat3<T>& lhs, const vec2<T>& rhs)
{
	return vec2<T>(
		lhs[0].x * rhs.x + lhs[1].x * rhs.y + lhs[2].x,
		lhs[0].y * rhs.x + lhs[1].y * rhs.y + lhs[2].y
	);
}

template <typename T>
mat3<T>& operator*=(mat3<T>& lhs, const mat3<T>& rhs)
{
	mat3<T> out(0.f);
	for (int iCol = 0; iCol < 3; iCol++)
		for (int iRow = 0; iRow < 3; iRow++)
			for (int k = 0; k < 3; k++)
				out[iCol][iRow] += lhs[k][iRow] * rhs[iCol][k];
	return (lhs = out);
}

}