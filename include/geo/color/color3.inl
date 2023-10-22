#include <geo/color/color3.h>

namespace geometry {

template <typename T>
inline color3<T>::color3()
{
}

template <typename T>
inline color3<T>::color3(T value) :
	r(value), g(value), b(value)
{
}

template<typename T>
template<typename U>
inline color3<T>::color3(const color3<U>& value) :
	color3(static_cast<T>(value.r), static_cast<T>(value.g), static_cast<T>(value.b))
{
}

template<typename T>
inline color3<T>::color3(T r, T g, T b) :
	r(r), g(g), b(b)
{
}

template<typename T>
inline color3<T>::color3(const vec3<T>& vec) :
	color3(vec.x, vec.y, vec.z)
{
}

template <typename T>
inline T & color3<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T & color3<T>::operator[](size_t index) const
{
	return data[index];
}

template<typename T>
template <typename U, typename>
inline T color3<T>::luminance() const
{
	static const color3<T> l(T(0.2126), T(0.7152), T(0.0722));
	return r * l.r + g * l.g + b * l.b;
}

template<typename T>
inline real_t srgb2linear(real_t value)
{
	if (value <= T(0.04045))
		return value * T(1) / T(12.92);
	return pow<T>((value + T(0.055)) * T(1) / T(1.055), T(2.4));
}

template<typename T>
inline real_t linear2srgb(real_t value)
{
	if (value <= real_t(0.0031308))
		return real_t(12.92) * value;
	return real_t(1.055) * pow<real_t>(value, real_t(1) / real_t(2.4)) - real_t(0.055);
}

template<typename T>
template <typename U, typename>
inline color3<T> color3<T>::srgb2linear(const color3<T>& color)
{
	return color3<T>(
		srgb2linear(color.r),
		srgb2linear(color.g),
		srgb2linear(color.b)
	);
}

template<typename T>
template <typename U, typename>
inline color3<T> color3<T>::linear2srgb(const color3<T>& color)
{
	return color3<T>(
		linear2srgb(color.r),
		linear2srgb(color.g),
		linear2srgb(color.b)
	);
}

template <typename T>
inline bool operator==(const color3<T> &lhs, const color3<T> &rhs)
{
	return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

template <typename T>
inline bool operator!=(const color3<T> &lhs, const color3<T> &rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline color3<T> operator*(const color3<T> &lhs, const color3<T> &rhs)
{
	color3<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline color3<T> operator*(const color3<T> &lhs, real_t rhs)
{
	color3<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline color3<T> operator*(T lhs, const color3<T> &rhs)
{
	color3<T> out(rhs);
	out *= lhs;
	return out;
}

template <typename T>
color3<T> & operator*=(color3<T> & lhs, const color3<T> & rhs)
{
	lhs.r *= rhs.r;
	lhs.g *= rhs.g;
	lhs.b *= rhs.b;
	lhs.a *= rhs.a;
	return lhs;
}

template <typename T>
color3<T> & operator*=(color3<T> & lhs, real_t rhs)
{
	lhs.r = static_cast<T>(lhs.r * rhs);
	lhs.g = static_cast<T>(lhs.g * rhs);
	lhs.b = static_cast<T>(lhs.b * rhs);
	lhs.a = static_cast<T>(lhs.a * rhs);
	return lhs;
}

template <typename T>
inline color3<T> operator/(const color3<T> &lhs, real_t rhs)
{
	return color3<T>(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs, lhs.a / rhs);
}

template <typename T>
color3<T> & operator/=(color3<T> & lhs, real_t rhs)
{
	lhs.r = static_cast<T>(lhs.r / rhs);
	lhs.g = static_cast<T>(lhs.g / rhs);
	lhs.b = static_cast<T>(lhs.b / rhs);
	lhs.a = static_cast<T>(lhs.a / rhs);
	return lhs;
}

template <typename T>
inline color3<T> operator+(const color3<T> &lhs, const color3<T> &rhs)
{
	return color3<T>(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
}

template <typename T>
inline color3<T> &operator+=(color3<T> &lhs, const color3<T> &rhs)
{
	lhs.r += rhs.r; lhs.g += rhs.g; lhs.b += rhs.b; lhs.a += rhs.a; return lhs;
}

template <typename T>
inline color3<T> operator-(const color3<T> &lhs, const color3<T> &rhs)
{
	return color3<T>(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a);
}

template <typename T>
inline color3<T> &operator-=(color3<T> &lhs, const color3<T> &rhs)
{
	lhs.r -= rhs.r; lhs.g -= rhs.g; lhs.b -= rhs.b; lhs.a -= rhs.a; return lhs;
}

template <typename T>
inline color3<T> operator-(const color3<T> &vec)
{
	return color3<T>(-vec.r, -vec.g, -vec.b, -vec.a);
}

}
