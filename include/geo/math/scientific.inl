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
inline angle<T> arccos(T value)
{
	return angle<T>::radian(std::acos(value));
}

template <typename T>
inline angle<T> arcsin(T value)
{
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
	return std::exp(value);
}

template <typename T>
inline T log(T value)
{
	return std::log(value);
}

template <typename T>
inline T log10(T value)
{
	return std::log10(value);
}

// Power functions
template <typename T>
inline T pow(T value, real_t exponent)
{
	return std::pow(value, exponent);
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
	return std::ceil(value);
}

template <typename T>
inline T floor(T value)
{
	return std::floor(value);
}

template <typename T>
inline T trunc(T value)
{
	return std::trunc(value);
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
inline T isNan(T value)
{
	return std::isnan(value);
}

template <typename T>
inline T isInf(T value)
{
	return std::isinf(value);
}

}