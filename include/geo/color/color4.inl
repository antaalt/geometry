#include <geo/color/color4.h>

namespace geometry {

template <typename T>
inline color4<T>::color4()
{
}

template <typename T>
inline color4<T>::color4(T value) :
	r(value), g(value), b(value), a(value)
{
}

template<>
template<>
inline color4<byte_t>::color4(const color4<real_t>& value)
{
	*this = linear2srgb(value);
}

template<>
template<>
inline color4<real_t>::color4(const color4<byte_t>& value)
{
	*this = srgb2linear(value);
}

template <typename T>
inline color4<T>::color4(T r, T g, T b, T a) :
	r(r), g(g), b(b), a(a)
{
}

template<typename T>
inline color4<T>::color4(const vec3<T>& vec, T a) :
	r(vec.x), g(vec.y), b(vec.z), a(a)
{
}

template<typename T>
inline color4<T>::color4(const vec4<T>& vec) :
	r(vec.x), g(vec.y), b(vec.z), a(vec.w)
{
}

template <typename T>
inline T & color4<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T & color4<T>::operator[](size_t index) const
{
	return data[index];
}

template<typename T>
inline real_t color4<T>::luminance() const
{
	if constexpr (std::is_same<real_t, T>::value)
	{
		static const color3<T> l(0.2126f, 0.7152f, 0.0722f);
		return r * l.r + g * l.g + b * l.b;
	}
	else
	{
		static_assert(false);
	}
}

template<typename T>
inline uint32_t color4<T>::toUint32()
{
	if constexpr (std::is_same<byte_t, T>::value)
	{
		return static_cast<uint32_t>(a << 24) | static_cast<uint32_t>(b << 16) | static_cast<uint32_t>(g << 8) | static_cast<uint32_t>(r << 0);
	}
	else if constexpr (std::is_same<real_t, T>::value)
	{
		color4<byte_t> color = linear2srgb(*this);
		return static_cast<uint32_t>(color.a << 24) | static_cast<uint32_t>(color.b << 16) | static_cast<uint32_t>(color.g << 8) | static_cast<uint32_t>(color.r << 0);
	}
	else
	{
		static_assert(false);
	}
}
template<typename T>
inline void color4<T>::fromUint32(uint32_t value)
{
	if constexpr (std::is_same<byte_t, T>::value)
	{
		r = (value >> 0) & 0xFF;
		g = (value >> 8) & 0xFF;
		b = (value >> 16) & 0xFF;
		a = (value >> 24) & 0xFF;
	}
	else if constexpr (std::is_same<real_t, T>::value)
	{
		color4<byte_t> color;
		color.r = (value >> 0) & 0xFF;
		color.g = (value >> 8) & 0xFF;
		color.b = (value >> 16) & 0xFF;
		color.a = (value >> 24) & 0xFF;
		*this = srgb2linear(color);
	}
	else
	{
		static_assert(false);
	}
}

template<typename T>
inline bool color4<T>::fromHexa(const char* hex_code)
{
	size_t len = strlen(hex_code);
	if (len == 7 && hex_code[0] == '#')
	{
		char* endptr;
		unsigned long value = strtoul(hex_code + 1, endptr, 16);
		if (endptr == hex_code || value > 0xFFFFFFFF)
			return false;
		fromUint32(static_cast<uint32_t>(value));
		return true;
	}
	else if (len == 6 && std::isdigit(hex_code[0]))
	{
		char* endptr;
		unsigned long value = strtoul(hex_code, endptr, 16);
		if (endptr == hex_code || value > 0xFFFFFFFF)
			return false;
		fromUint32(static_cast<uint32_t>(value));
		return true;
	}
	else
	{
		return false; // Invalid input.
	}
}

inline real_t srgb2linear(real_t value)
{
	if (value <= real_t(0.04045))
		return value * real_t(1) / real_t(12.92);
	return pow<real_t>((value + real_t(0.055)) * real_t(1) / real_t(1.055), real_t(2.4));
}

inline real_t linear2srgb(real_t value)
{
	if (value <= real_t(0.0031308))
		return real_t(12.92) * value;
	return real_t(1.055) * pow<real_t>(value, real_t(1) / real_t(2.4)) - real_t(0.055);
}

template<typename T>
inline color4<real_t> color4<T>::srgb2linear(const color4<byte_t>& color)
{
	return color4<real_t>(
		static_cast<real_t>(geometry::srgb2linear(color.r / 255.f)),
		static_cast<real_t>(geometry::srgb2linear(color.g / 255.f)),
		static_cast<real_t>(geometry::srgb2linear(color.b / 255.f)),
		static_cast<byte_t>(color.a / 255.f)
	);
}

template<typename T>
inline color4<byte_t> color4<T>::linear2srgb(const color4<real_t>& color)
{
	return color4<byte_t>(
		static_cast<byte_t>(saturate(geometry::linear2srgb(color.r) * 255.f)),
		static_cast<byte_t>(saturate(geometry::linear2srgb(color.g) * 255.f)),
		static_cast<byte_t>(saturate(geometry::linear2srgb(color.b) * 255.f)),
		static_cast<byte_t>(saturate(color.a * 255.f))
	);
}

template<typename T>
inline color4<T> color4<T>::lerp(const color4<T>& a, const color4<T>& b, real_t t)
{
	return geometry::lerp(a, b, t);
}

template <typename T>
inline bool operator==(const color4<T> &lhs, const color4<T> &rhs)
{
	return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a;
}

template <typename T>
inline bool operator!=(const color4<T> &lhs, const color4<T> &rhs)
{
	return !(lhs == rhs);
}

template <typename T>
inline color4<T> operator*(const color4<T> &lhs, const color4<T> &rhs)
{
	color4<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline color4<T> operator*(const color4<T> &lhs, real_t rhs)
{
	color4<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline color4<T> operator*(T lhs, const color4<T> &rhs)
{
	color4<T> out(rhs);
	out *= lhs;
	return out;
}

template <typename T>
color4<T> & operator*=(color4<T> & lhs, const color4<T> & rhs)
{
	lhs.r *= rhs.r;
	lhs.g *= rhs.g;
	lhs.b *= rhs.b;
	lhs.a *= rhs.a;
	return lhs;
}

template <typename T>
color4<T> & operator*=(color4<T> & lhs, real_t rhs)
{
	lhs.r = static_cast<T>(lhs.r * rhs);
	lhs.g = static_cast<T>(lhs.g * rhs);
	lhs.b = static_cast<T>(lhs.b * rhs);
	lhs.a = static_cast<T>(lhs.a * rhs);
	return lhs;
}

template <typename T>
inline color4<T> operator/(const color4<T> &lhs, real_t rhs)
{
	return color4<T>(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs, lhs.a / rhs);
}

template <typename T>
color4<T> & operator/=(color4<T> & lhs, real_t rhs)
{
	lhs.r = static_cast<T>(lhs.r / rhs);
	lhs.g = static_cast<T>(lhs.g / rhs);
	lhs.b = static_cast<T>(lhs.b / rhs);
	lhs.a = static_cast<T>(lhs.a / rhs);
	return lhs;
}

template <typename T>
inline color4<T> operator+(const color4<T> &lhs, const color4<T> &rhs)
{
	return color4<T>(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a);
}

template <typename T>
inline color4<T> &operator+=(color4<T> &lhs, const color4<T> &rhs)
{
	lhs.r += rhs.r; lhs.g += rhs.g; lhs.b += rhs.b; lhs.a += rhs.a; return lhs;
}

template <typename T>
inline color4<T> operator-(const color4<T> &lhs, const color4<T> &rhs)
{
	return color4<T>(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a);
}

template <typename T>
inline color4<T> &operator-=(color4<T> &lhs, const color4<T> &rhs)
{
	lhs.r -= rhs.r; lhs.g -= rhs.g; lhs.b -= rhs.b; lhs.a -= rhs.a; return lhs;
}

template <typename T>
inline color4<T> operator-(const color4<T> &vec)
{
	return color4<T>(-vec.r, -vec.g, -vec.b, -vec.a);
}

}
