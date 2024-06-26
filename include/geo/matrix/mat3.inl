#include <geo/matrix/mat3.h>
#include <geo/matrix/quat.h>
#include <geo/matrix/mat4.h>
#include <geo/vector/norm3.h>
#include <geo/vector/point3.h>
#include <geo/vector/vec3.h>

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

template<typename T>
inline col3<T>::col3(const vec3<T>& vec) : x(vec.x), y(vec.y), z(vec.z)
{
}

template <typename T>
inline col3<T>::col3(T x, T y, T z) : x(x), y(y), z(z)
{
}

template <typename T>
inline col3<T>::col3(const col4<T>& col) :
	x(col.x), y(col.y), z(col.z)
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
inline mat3<T>::mat3(T value) : cols{ col3<T>(value), col3<T>(value), col3<T>(value) }
{
}

template <typename T>
inline mat3<T>::mat3(col3<T> x, col3<T> y, col3<T> z) : cols{ x, y, z }
{
}

template <typename T>
inline mat3<T>::mat3(const mat4<T>& mat) :
	cols{ col3<T>(mat[0]), col3<T>(mat[1]), col3<T>(mat[2]) }
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
inline mat3<T> mat3<T>::rotate(angle<T> angle)
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
inline mat3<T> mat3<T>::TRS(const vec2<T>& t, angle<T> r, const vec2<T>& s)
{
	return translate(t) * rotate(r) * scale(s);
}

template <typename T>
inline mat3<T> mat3<T>::inverse(const mat3<T>& mat)
{
	const T& a = mat[0][0];
	const T& b = mat[1][0];
	const T& c = mat[2][0];
	const T& d = mat[0][1];
	const T& e = mat[1][1];
	const T& f = mat[2][1];
	const T& g = mat[0][2];
	const T& h = mat[1][2];
	const T& k = mat[2][2];

	const T det = T(1) / mat.det();

	return mat3(
		col3<T>(
			det *  (e * k - f * h),
			det * -(d * k - f * g),
			det *  (d * h - e * g)
		),
		col3<T>(
			det * -(b * k - c * h),
			det *  (a * k - c * g),
			det * -(a * h - b * g)
		),
		col3<T>(
			det *  (b * f - c * e),
			det * -(a * f - c * d),
			det *  (a * e - b * d)
		)
	);
}

template <typename T>
inline mat3<T> mat3<T>::transpose(const mat3<T>& mat)
{
	mat3<T> output;
	for (uint8_t x = 0; x < 3; x++)
		for (uint8_t y = 0; y < 3; y++)
			output[x][y] = mat[y][x];
	return output;
}

template <typename T>
T mat3<T>::det() const
{
	return cols[0][0] * (cols[1][1] * cols[2][2] - cols[2][1] * cols[1][2])
		- cols[1][0] * (cols[0][1] * cols[2][2] - cols[2][1] * cols[0][2])
		+ cols[2][0] * (cols[0][1] * cols[1][2] - cols[1][1] * cols[0][2]);
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
vec3<T> operator*(const mat3<T>& lhs, const vec3<T>& rhs)
{
	// Column vector
	return vec3<T>(
		lhs[0].x * rhs.x + lhs[1].x * rhs.y + lhs[2].x * rhs.z,
		lhs[0].y * rhs.x + lhs[1].y * rhs.y + lhs[2].y * rhs.z,
		lhs[0].z * rhs.x + lhs[1].z * rhs.y + lhs[2].z * rhs.z
	);
}

template <typename T>
vec3<T> operator*(const vec3<T>& lhs, const mat3<T>& rhs)
{
	// Row vector
	return vec3<T>(
		lhs.x * rhs[0].x * lhs.y + rhs[0].y * lhs.z + rhs[0].z,
		lhs.x * rhs[1].x * lhs.y + rhs[1].y * lhs.z + rhs[1].z,
		lhs.x * rhs[2].x * lhs.y + rhs[2].y * lhs.z + rhs[2].z
	);
}
template <typename T>
vec2<T> operator*(const mat3<T>& lhs, const vec2<T>& rhs)
{
	// Should handle w division here ?
	return vec2<T>(
		lhs[0].x * rhs.x + lhs[1].x * rhs.y + lhs[2].x,
		lhs[0].y * rhs.x + lhs[1].y * rhs.y + lhs[2].y
	);
}
template <typename T>
mat3<T> operator*(const mat3<T>& lhs, T rhs)
{
	return mat3<T>(
		col3<T>(lhs.cols[0].x * rhs, lhs.cols[0].y * rhs, lhs.cols[0].z * rhs),
		col3<T>(lhs.cols[1].x * rhs, lhs.cols[1].y * rhs, lhs.cols[1].z * rhs),
		col3<T>(lhs.cols[2].x * rhs, lhs.cols[2].y * rhs, lhs.cols[2].z * rhs)
	);
}
template <typename T>
mat3<T> operator*(T lhs, const mat3<T>& rhs)
{
	return mat3<T>(
		col3<T>(lhs * rhs.cols[0].x, lhs * rhs.cols[0].y, lhs * rhs.cols[0].z),
		col3<T>(lhs * rhs.cols[1].x, lhs * rhs.cols[1].y, lhs * rhs.cols[1].z),
		col3<T>(lhs * rhs.cols[2].x, lhs * rhs.cols[2].y, lhs * rhs.cols[2].z)
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