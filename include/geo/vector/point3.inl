#include <geo/vector/point3.h>
#include <geo/vector/vec3.h>
#include <geo/vector/norm3.h>

namespace geometry {

template <typename T>
inline point3<T>::point3()
{
}

template <typename T>
inline point3<T>::point3(T value) : x(value), y(value), z(value)
{
}

template <typename T>
inline point3<T>::point3(T x, T y, T z) : x(x), y(y), z(z)
{
}

template <typename T>
inline point3<T>::point3(const norm3<T> & normal) : x(normal.x), y(normal.y), z(normal.z)
{
}

template<typename T>
inline point3<T>::point3(const col3<T>& col) :
	point3(col.x, col.y, col.z)
{
}

template<typename T>
inline point3<T>::point3(const col4<T>& col) :
	point3(col.x, col.y, col.z)
{
}

template <typename T>
inline point3<T>::point3(const vec3<T> & vec) : x(vec.x), y(vec.y), z(vec.z)
{
}

template <typename T>
inline T & point3<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T & point3<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
inline real_t point3<T>::distance(const point3<T> &lhs, const point3<T> &rhs)
{
	return vec3<T>(rhs - lhs).norm();
}

template <typename T>
inline point3<T> point3<T>::lerp(const point3<T>& from, const point3<T>& to, real_t t)
{
	return geometry::lerp(from, to, t);
}

template<typename T>
inline point3<T> point3<T>::zero()
{
	return point3<T>(T(0));
}

template<typename T>
inline point3<T> point3<T>::one()
{
	return point3<T>(T(1));
}

template <typename T>
inline bool operator==(const point3<T> &lhs, const point3<T> &rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename T>
inline bool operator!=(const point3<T> &lhs, const point3<T> &rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline point3<T> operator*(const point3<T> &lhs, real_t rhs)
{
	point3<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline point3<T> operator*(real_t lhs, const point3<T> &rhs)
{
	point3<T> out(rhs);
	out *= lhs;
	return out;
}

template <typename T>
inline point3<T> & operator*=(point3<T> & lhs, real_t rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

template <typename T>
inline point3<T> operator/(const point3<T> &lhs, real_t rhs)
{
	point3<T> out(lhs);
	out /= rhs;
	return out;
}

template <typename T>
inline point3<T> & operator/=(point3<T> & lhs, real_t rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	return lhs;
}

template <typename T>
inline point3<T> operator+(const point3<T> &lhs, const vec3<T> &rhs)
{
	point3<T> out(lhs);
	out += rhs;
	return out;
}

template <typename T>
inline point3<T> &operator+=(point3<T> &lhs, const vec3<T> &rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

template <typename T>
inline point3<T> operator-(const point3<T>& lhs, const vec3<T>& rhs)
{
	point3<T> out(lhs);
	out -= rhs;
	return out;
}

template <typename T>
inline point3<T>& operator-=(point3<T>& lhs, const vec3<T>& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

template <typename T>
inline vec3<T> operator-(const point3<T> &lhs, const point3<T> &rhs)
{
	return vec3<T>(
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z
	);
}

template <typename T>
inline point3<T> operator-(const point3<T> &vec)
{
	return point3<T>(-vec.x, -vec.y, -vec.z);
}

}
