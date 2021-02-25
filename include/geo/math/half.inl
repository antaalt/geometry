#include <geo/math/half.h>

namespace geometry {

inline half::half()
{
}

inline half::half(float value)
{
	*this = value;
}

inline half::half(double value)
{
	*this = static_cast<float>(value);
}

inline half& half::operator=(float value)
{
	// This ignore underflow, overflow, denormalized values, infinite values...
	uint32_t x = *reinterpret_cast<uint32_t*>(&value);
	data = ((x >> 16) & 0x8000) | ((((x & 0x7f800000) - 0x38000000) >> 13) & 0x7c00) | ((x >> 13) & 0x03ff);
	return *this;
}

inline half& half::operator=(double value)
{
	*this = static_cast<float>(value);
	return *this;
}

inline half::operator float() const
{
	// This ignore underflow, overflow, denormalized values, infinite values...
	union {
		uint32_t u;
		float f;
	} u;
	uint32_t h = data;
	u.u = ((h & 0x8000) << 16) | (((h & 0x7c00) + 0x1C000) << 13) | ((h & 0x03FF) << 13);
	return u.f;
}

inline half::operator double() const
{
	return static_cast<float>(*this);
}

inline half operator "" _h(long double h)
{
	return half(static_cast<float>(h));
}

inline half operator "" _h(unsigned long long int h)
{
	return half(static_cast<float>(h));
}

inline bool operator==(half lhs, half rhs)
{
	// Check for +0 & -0
	if (!(lhs.data << 1u) && !(rhs.data << 1u)) 
		return true;
	return lhs.data == rhs.data;
}

inline bool operator!=(half lhs, half rhs)
{
	// Check for +0 & -0
	if (!(lhs.data << 1u) && !(rhs.data << 1u))
		return false;
	return lhs.data != rhs.data;
}

inline bool operator<(half lhs, half rhs)
{
	// This works with half layout
	return lhs.data < rhs.data; 
}

inline bool operator>(half lhs, half rhs)
{ 
	return lhs.data > rhs.data;
}

inline bool operator<=(half lhs, half rhs)
{
	return lhs.data <= rhs.data; 
}

inline bool operator>=(half lhs, half rhs)
{ 
	return lhs.data >= rhs.data; 
}

inline half operator*(half lhs, half rhs)
{
	return half(static_cast<float>(lhs) * static_cast<float>(rhs));
}

inline half operator/(half lhs, half rhs)
{
	return half(static_cast<float>(lhs) / static_cast<float>(rhs));
}

inline half operator+(half lhs, half rhs)
{
	return half(static_cast<float>(lhs) + static_cast<float>(rhs));
}

inline half operator-(half lhs, half rhs)
{
	return half(static_cast<float>(lhs) - static_cast<float>(rhs));
}

inline half operator-(half value)
{
	return half(-static_cast<float>(value));
}

inline half& operator*=(half& lhs, half rhs)
{
	half r = lhs * rhs;
	lhs.data = r.data;
	return lhs;
}

inline half& operator/=(half& lhs, half rhs)
{
	half r = lhs / rhs;
	lhs.data = r.data;
	return lhs;
}

inline half& operator+=(half& lhs, half rhs)
{
	half r = lhs + rhs;
	lhs.data = r.data;
	return lhs;
}

inline half& operator-=(half& lhs, half rhs)
{
	half r = lhs - rhs;
	lhs.data = r.data;
	return lhs;
}

inline half operator*(half lhs, real_t rhs)
{
	return half(static_cast<float>(lhs) * rhs);
}

inline half operator/(half lhs, real_t rhs)
{
	return half(static_cast<float>(lhs) / rhs);
}

inline half operator+(half lhs, real_t rhs)
{
	return half(static_cast<float>(lhs) + rhs);
}

inline half operator-(half lhs, real_t rhs)
{
	return half(static_cast<float>(lhs) - rhs);
}

inline half operator*(real_t lhs, half rhs)
{
	return half(lhs * static_cast<float>(rhs));
}

inline half operator/(real_t lhs, half rhs)
{
	return half(lhs / static_cast<float>(rhs));
}

inline half operator+(real_t lhs, half rhs)
{
	return half(lhs + static_cast<float>(rhs));
}

inline half operator-(real_t lhs, half rhs)
{
	return half(lhs - static_cast<float>(rhs));
}

};