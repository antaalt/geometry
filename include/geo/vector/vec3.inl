#include "vec3.h"
#include "norm3.h"
#include "point3.h"
#include "vec2.h"
#include "vec4.h"

namespace geometry {

template <typename T>
inline vec3<T>::vec3()
{
}

template <typename T>
inline vec3<T>::vec3(T value) :
	x(value), y(value), z(value)
{
}

template <typename T>
inline vec3<T>::vec3(T x, T y, T z) : 
	x(x), y(y), z(z)
{
}
template <typename T>
template <typename U>
inline vec3<T>::vec3(U x, U y, U z) :
	x(static_cast<T>(x)), y(static_cast<T>(y)), z(static_cast<T>(z))
{
}

template <typename T>
template <typename U>
inline vec3<T>::vec3(const vec3<U>& value) :
	vec3<T>(value.x, value.y, value.z)
{

}

template <typename T>
inline vec3<T>::vec3(const norm3<T> &normal) : 
	x(normal.x), y(normal.y), z(normal.z)
{
}

template <typename T>
inline vec3<T>::vec3(const point3<T> &point) : 
	x(point.x), y(point.y), z(point.z)
{
}

template<typename T>
inline vec3<T>::vec3(const col3<T>& col) :
	x(col.x), y(col.y), z(col.z)
{
}

template<typename T>
inline vec3<T>::vec3(const col4<T>& col) :
	vec3(col.x, col.y, col.z)
{
}

template <typename T>
inline vec3<T>::vec3(const vec2<T> &vec, T z) : 
	x(vec.x), y(vec.y), z(z)
{
}

template<typename T>
inline vec3<T>::vec3(const vec4<T>& vec) :
	x(vec.x), y(vec.y), z(vec.z)
{
}

template <typename T>
inline T & vec3<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T & vec3<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
template <typename U, typename>
inline T vec3<T>::norm() const
{
	return sqrt(dot(*this, *this));
}

template <typename T>
template <typename U, typename>
inline T vec3<T>::dot(const vec3<T> & lhs, const vec3<T> & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T>
template <typename U, typename>
inline T vec3<T>::dot(const vec3<T>& lhs, const norm3<T>& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

template <typename T>
template <typename U, typename>
inline vec3<T> vec3<T>::cross(const vec3<T> & lhs, const vec3<T> & rhs)
{
	return vec3<T>(
		lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x
	);
}

template<typename T>
inline vec3<T> vec3<T>::abs(const vec3<T>& value)
{
	return vec3<T>(
		geometry::abs<T>(value.x),
		geometry::abs<T>(value.y),
		geometry::abs<T>(value.z)
	);
}

template<typename T>
inline vec3<T> vec3<T>::min(const vec3& lhs, const vec3& rhs)
{
	return vec3<T>(
		geometry::min<T>(lhs.x, rhs.x),
		geometry::min<T>(lhs.y, rhs.y),
		geometry::min<T>(lhs.z, rhs.z)
	);
}

template<typename T>
inline vec3<T> vec3<T>::max(const vec3& lhs, const vec3& rhs)
{
	return vec3<T>(
		geometry::max<T>(lhs.x, rhs.x),
		geometry::max<T>(lhs.y, rhs.y),
		geometry::max<T>(lhs.z, rhs.z)
	);
}

template<typename T>
inline T vec3<T>::distance(const vec3& lhs, const vec3& rhs)
{
	vec3 diff = rhs - lhs;
	return geometry::sqrt(vec3<T>::dot(diff, diff));
}

template<typename T>
inline T vec3<T>::length(const vec3& lhs)
{
	return lhs.norm();
}

template<typename T>
inline vec3<T> vec3<T>::lerp(const vec3<T>& a, const vec3<T>& b, real_t t)
{
	return geometry::lerp(a, b, t);
}

template <typename T>
template <typename U, typename>
inline vec3<T> vec3<T>::normalize(const vec3<T> &vec)
{
	return vec / vec.norm();
}

template <typename T>
inline vec3<T> vec3<T>::zero()
{
	return vec3f(0.f);
}

template <typename T>
inline vec3<T> vec3<T>::one()
{
	return vec3f(1.f);
}

template <typename T>
inline vec3<T> vec3<T>::up()
{
#if defined(GEOMETRY_Y_UP)
	return vec3f(0.f, 1.f, 0.f);
#elif defined(GEOMETRY_Z_UP)
	return vec3f(0.f, 0.f, 1.f);
#endif
}

template <typename T>
inline vec3<T> vec3<T>::down()
{
	return -up();
}

template <typename T>
inline vec3<T> vec3<T>::forward()
{
	// Arbitrary choice. Could be controlled by user ?
#if defined(GEOMETRY_Y_UP)
	return vec3f(0.f, 0.f, 1.f); // z forward
#elif defined(GEOMETRY_Z_UP)
	return vec3f(1.f, 0.f, 0.f); // x forward
#endif
}

template <typename T>
inline vec3<T> vec3<T>::backward()
{
	return -forward();
}

template <typename T>
inline vec3<T> vec3<T>::right()
{
	// Depend on up & forward & handedness.
#if defined(GEOMETRY_Y_UP)
#if defined(GEOMETRY_RIGHT_HANDED)
	return vec3f(-1.f, 0.f, 0.f);
#elif defined(GEOMETRY_LEFT_HANDED)
	return vec3f(1.f, 0.f, 0.f);
#endif
#elif defined(GEOMETRY_Z_UP)
#if defined(GEOMETRY_RIGHT_HANDED)
	return vec3f(0.f, -1.f, 0.f);
#elif defined(GEOMETRY_LEFT_HANDED)
	return vec3f(0.f, 1.f, 1.f);
#endif
#endif
}

template <typename T>
inline vec3<T> vec3<T>::left()
{
	return -right();
}

template <typename T>
inline bool operator==(const vec3<T> & lhs, const vec3<T> & rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

template <typename T>
inline bool operator!=(const vec3<T> &lhs, const vec3<T> &rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline vec3<T> operator*(const vec3<T> &lhs, T rhs)
{
	vec3<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline vec3<T> operator*(T lhs, const vec3<T> &rhs)
{
	vec3<T> out(rhs);
	out *= lhs;
	return out;
}

template <typename T>
inline vec3<T> & operator*=(vec3<T> & lhs, T rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

template <typename T>
inline vec3<T> operator/(const vec3<T> &lhs, T rhs)
{
	vec3<T> out(lhs);
	out /= rhs;
	return out;
}

template <typename T>
inline vec3<T> & operator/=(vec3<T> & lhs, T rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	return lhs;
}

template <typename T>
vec3<T> operator/(const vec3<T>& lhs, const vec3<T>& rhs)
{
	vec3<T> out(lhs);
	out /= rhs;
	return out;
}

template <typename T>
vec3<T>& operator/=(vec3<T>& lhs, const vec3<T>& rhs)
{
	lhs.x /= rhs.x;
	lhs.y /= rhs.y;
	lhs.z /= rhs.z;
	return lhs;
}

template <typename T>
vec3<T> operator*(const vec3<T>& lhs, const vec3<T>& rhs)
{
	vec3<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
vec3<T>& operator*=(vec3<T>& lhs, const vec3<T>& rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	lhs.z *= rhs.z;
	return lhs;
}

template <typename T>
inline vec3<T> operator+(const vec3<T> &lhs, const vec3<T> &rhs)
{
	return vec3<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

template <typename T>
inline vec3<T> & operator+=(vec3<T> & lhs, const vec3<T> & rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &lhs, const vec3<T> &rhs)
{
	vec3<T> out(lhs);
	out -= rhs;
	return out;
}

template <typename T>
inline vec3<T> & operator-=(vec3<T> & lhs, const vec3<T> & rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

template <typename T>
inline vec3<T> operator-(const vec3<T> &vec)
{
	return vec3<T>(-vec.x, -vec.y, -vec.z);
}

}