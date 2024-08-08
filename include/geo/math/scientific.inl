#pragma once

#include <geo/math/scientific.h>

#include <cmath>
#include <climits>

namespace geometry {

template <typename T>
inline T lerp(T a, T b, real_t t)
{
	return a + (b - a) * t;
}

template <typename T>
inline T (max)(T a, T b)
{
	return (a > b) ? a : b;
}

template <typename T>
inline T (min)(T a, T b)
{
	return (a < b) ? a : b;
}

template <typename T>
inline T clamp(T value, T min, T max)
{
	return geometry::min<T>(geometry::max<T>(value, min), max);
}

template <typename T>
inline T saturate(T value)
{
	return geometry::clamp<T>(value, T(0), T(1));
}

template <typename T>
inline int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

// Trigonometric functions
template <typename T>
inline T cos(angle<T> value)
{
	return std::cos(value.radian());
}

template <typename T>
inline T sin(angle<T> value)
{
	return std::sin(value.radian());
}

template <typename T>
inline T tan(angle<T> value)
{
	return std::tan(value.radian());
}
template <typename T> 
inline T cot(angle<T> value)
{
	return std::cos(value.radian()) / std::sin(value.radian());
}

template <typename T>
inline void sincos(angle<T> value, T& s, T& c)
{
	s = sin<T>(value);
	c = cos<T>(value);
}

template <typename T>
inline angle<T> arccos(T value)
{
	// std::acos return nan out that ranges.
	if (value <= T(-1))
		return geometry::pi<T>;
	else if (value >= T(1))
		return angle<T>::radian(0);
	else
		return angle<T>::radian(std::acos(value));
}

template <typename T>
inline angle<T> arcsin(T value)
{
	// std::asin return nan out that ranges.
	if (value <= T(-1))
		return -geometry::pi<T> / T(2);
	else if (value >= T(1))
		return geometry::pi<T> / T(2);
	else
		return angle<T>::radian(std::asin(value));
}

template <typename T>
inline angle<T> arctan(T value)
{
	return angle<T>::radian(std::atan(value));
}

template <typename T>
inline angle<T> arctan2(T y, T x)
{
	return angle<T>::radian(std::atan2(y, x));
}

// Hyperbolic functions
// [...]
// Exponential and logarithmic functions
template <typename T>
inline T exp(T value)
{
	return static_cast<T>(std::exp(value));
}

template <typename T>
inline T log(T value)
{
	return static_cast<T>(std::log(value));
}

template <typename T>
inline T log2(T value)
{
	return static_cast<T>(std::log2(value));
}

template <typename T>
inline T log10(T value)
{
	return static_cast<T>(std::log10(value));
}

// Power functions
template <typename T>
inline T pow(T value, real_t exponent)
{
	return static_cast<T>(std::pow(value, exponent));
}

template<typename T>
T sqr(T value)
{
	return value * value;
}

template <typename T>
inline T sqrt(T value)
{
	return static_cast<T>(std::sqrt(value));
}

// Rounding and remainder
template <typename T>
inline T ceil(T value)
{
	return static_cast<T>(std::ceil(value));
}

template <typename T>
inline T floor(T value)
{
	return static_cast<T>(std::floor(value));
}

template <typename T>
inline T trunc(T value)
{
	return static_cast<T>(std::trunc(value));
}

template <typename T>
inline T frac(T value)
{
	return value - trunc<T>(value);
}

// Others functions
template <typename T>
inline T abs(T value)
{
	if constexpr (std::is_signed<T>::value)
		return (value < T(0)) ? -value : value;
	else
		return value;
}

// Macro
template <typename T>
inline bool isNan(T value)
{
	return std::isnan(value);
}

template <typename T>
inline bool isInf(T value)
{
	return std::isinf(value);
}

}