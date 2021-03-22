#pragma once

#include <geo/math/angle.h>

namespace geometry {

template <typename T>
constexpr angle<T>::angle() : 
	m_angle(0) 
{
}

template <typename T>
constexpr angle<T>::angle(T value) : 
	m_angle(value)
{
}

template <typename T>
constexpr angle<T> angle<T>::radian(T value)
{ 
	return angle<T>(value); 
}

template <typename T>
constexpr angle<T> angle<T>::degree(T value)
{
	return angle<T>(deg2rad(value)); 
}

template <typename T>
constexpr T angle<T>::radian() const
{ 
	return m_angle; 
}

template <typename T>
constexpr T angle<T>::degree() const
{ 
	return rad2deg(m_angle);
}

template <typename T>
constexpr T angle<T>::rad2deg(T rad)
{ 
	return rad / angle<T>::pi * static_cast<T>(180);
}

template <typename T>
constexpr T angle<T>::deg2rad(T deg)
{ 
	return deg / static_cast<T>(180) * angle<T>::pi; 
}

template <typename T>
constexpr angle<T> angle<T>::operator+(const angle<T>& rhs) const
{ 
	return angle<T>(m_angle + rhs.m_angle); 
}

template <typename T>
constexpr angle<T> angle<T>::operator-(const angle<T>& rhs) const
{ 
	return angle<T>(m_angle - rhs.m_angle); 
}

template <typename T>
constexpr angle<T> angle<T>::operator/(const angle<T>& rhs) const
{
	return angle<T>(m_angle / rhs.m_angle); 
}

template <typename T>
constexpr angle<T> angle<T>::operator*(const angle<T>& rhs) const
{
	return angle<T>(m_angle * rhs.m_angle);
}

template <typename T>
constexpr angle<T>& angle<T>::operator+=(const angle<T>& rhs)
{ 
	m_angle += rhs.m_angle; 
	return *this; 
}

template <typename T>
constexpr angle<T>& angle<T>::operator-=(const angle<T>& rhs)
{
	m_angle -= rhs.m_angle;
	return *this;
}

template <typename T>
constexpr angle<T>& angle<T>::operator/=(const angle<T>& rhs)
{ 
	m_angle /= rhs.m_angle; 
	return *this; 
}

template <typename T>
constexpr angle<T>& angle<T>::operator*=(const angle<T>& rhs)
{
	m_angle *= rhs.m_angle; 
	return *this;
}

template <typename T>
constexpr angle<T> angle<T>::operator-() const
{ 
	return angle<T>(-m_angle); 
}

template <typename T>
constexpr angle<T> angle<T>::operator*(T rhs) const
{ 
	return angle<T>(m_angle * rhs); 
}

template <typename T>
constexpr angle<T> angle<T>::operator/(T rhs) const
{ 
	return angle<T>(m_angle / rhs);
}

template <typename T>
constexpr angle<T>& angle<T>::operator*=(T rhs)
{ 
	m_angle *= rhs; return *this; 
}

template <typename T>
constexpr angle<T>& angle<T>::operator/=(T rhs)
{ 
	m_angle /= rhs; return *this;
}

template <typename T>
constexpr bool angle<T>::operator==(const angle<T>& rhs) const
{ 
	return m_angle == rhs.m_angle;
}

template <typename T>
constexpr bool angle<T>::operator!=(const angle<T>& rhs) const
{ 
	return m_angle != rhs.m_angle;
}

template <typename T>
constexpr bool angle<T>::operator<(const angle<T>& rhs) const
{ 
	return m_angle < rhs.m_angle; 
}

template <typename T>
constexpr bool angle<T>::operator>(const angle<T>& rhs) const
{
	return m_angle > rhs.m_angle;
}

template <typename T>
constexpr bool angle<T>::operator<=(const angle<T>& rhs) const
{ 
	return m_angle <= rhs.m_angle;
}

template <typename T>
constexpr bool angle<T>::operator>=(const angle<T>& rhs) const
{ 
	return m_angle >= rhs.m_angle; 
}

}
