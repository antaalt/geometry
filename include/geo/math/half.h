#pragma once

#include <geo/core/types.h>

namespace geometry {

// Basic half implementation. Use with care
struct half
{
	half();
	half(float value);
	half(double value);
	half(const half&) = default;
	half& operator=(float value);
	half& operator=(double value);
	~half() = default;

	operator float() const;
	operator double() const;

	union
	{
		uint16_t data;
		struct
		{
			uint16_t mantisse : 10;
			uint16_t exponent : 5;
			uint16_t sign : 1;
		} ieee;
	};
};

half operator "" _h(long double h);
half operator "" _h(unsigned long long int h);

bool operator==(half lhs, half rhs);
bool operator!=(half lhs, half rhs);
bool operator<(half lhs, half rhs);
bool operator>(half lhs, half rhs);
bool operator<=(half lhs, half rhs);
bool operator>=(half lhs, half rhs);

half operator*(half lhs, half rhs);
half operator/(half lhs, half rhs);
half operator+(half lhs, half rhs);
half operator-(half lhs, half rhs);
half operator-(half value);

half& operator*=(half& lhs, half rhs);
half& operator/=(half& lhs, half rhs);
half& operator+=(half& lhs, half rhs);
half& operator-=(half& lhs, half rhs);

half operator*(half lhs, real_t rhs);
half operator/(half lhs, real_t rhs);
half operator+(half lhs, real_t rhs);
half operator-(half lhs, real_t rhs);

half operator*(real_t lhs, half rhs);
half operator/(real_t lhs, half rhs);
half operator+(real_t lhs, half rhs);
half operator-(real_t lhs, half rhs);


}