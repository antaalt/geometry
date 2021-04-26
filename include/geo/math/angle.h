#pragma once

#include <geo/core/types.h>

namespace geometry {

template <typename T = real_t>
struct angle {
	constexpr explicit angle();
	// Create an angle with a given radian value
	static constexpr angle radian(T value);
	// Create an angle with a given degree value
	static constexpr angle degree(T value);

	// Pi variable
	static constexpr const T pi = static_cast<T>(3.141592653589793);

	// Get the angle value in radian
	constexpr T radian() const;
	// Get the angle value in degree
	constexpr T degree() const;

	// Convert radian to degree
	static constexpr T rad2deg(T rad);
	// Convert degree to radian
	static constexpr T deg2rad(T deg);

	// Operator
	constexpr angle<T> operator+(const angle<T>& rhs) const;
	constexpr angle<T> operator-(const angle<T>& rhs) const;
	constexpr angle<T> operator/(const angle<T>& rhs) const;
	constexpr angle<T> operator*(const angle<T>& rhs) const;
	constexpr angle<T>& operator+=(const angle<T>& rhs);
	constexpr angle<T>& operator-=(const angle<T>& rhs);
	constexpr angle<T>& operator/=(const angle<T>& rhs);
	constexpr angle<T>& operator*=(const angle<T>& rhs);
	constexpr angle<T> operator-() const;
	// Scale an angle
	template <typename U> friend constexpr angle<U> operator*(const angle<U>& lhs, real_t rhs);
	template <typename U> friend constexpr angle<U> operator*(real_t lhs, const angle<U>& rhs);
	constexpr angle<T> operator/(T rhs) const;
	constexpr angle<T>& operator*=(T rhs);
	constexpr angle<T>& operator/=(T rhs);
	// Compare an angle
	constexpr bool operator==(const angle<T>& rhs) const;
	constexpr bool operator!=(const angle<T>& rhs) const;
	constexpr bool operator< (const angle<T>& rhs) const;
	constexpr bool operator> (const angle<T>& rhs) const;
	constexpr bool operator<=(const angle<T>& rhs) const;
	constexpr bool operator>=(const angle<T>& rhs) const;
private:
	constexpr explicit angle(T value);
private:
	T m_angle; // angle is always stored as radian.
};

// Scale an angle
template <typename T> constexpr angle<T> operator*(const angle<T>& lhs, real_t rhs);
template <typename T> constexpr angle<T> operator*(real_t lhs, const angle<T>& rhs);


template <typename T>
static constexpr const angle<T> pi = angle<T>::radian(angle<T>::pi);

}
