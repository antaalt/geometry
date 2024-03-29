#include <geo/math/aabbox.h>

#include <limits>

namespace geometry {

template<typename T>
inline aabbox<T>::aabbox() :
	aabbox(
		point3<T>((std::numeric_limits<T>::max)()),
		point3<T>(-(std::numeric_limits<T>::max)())
	)
{
}

template<typename T>
inline aabbox<T>::aabbox(const point3<T>& min, const point3<T>& max) :
	min(min),
	max(max)
{
}

template<typename T>
inline void aabbox<T>::reset()
{
	min = point3<T>((std::numeric_limits<T>::max)());
	max = point3<T>(-(std::numeric_limits<T>::max)());
}

template<typename T>
inline bool aabbox<T>::valid() const
{
	return (min.x < max.x && min.y < max.y && min.z < max.z);
}

template<typename T>
inline vec3<T> aabbox<T>::extent() const
{
	return max - min;
}

template<typename T>
inline point3<T> aabbox<T>::center() const
{
	return (max + vec3<T>(min)) / 2.f;
}

template<typename T>
inline void aabbox<T>::include(real_t x, real_t y, real_t z)
{
	if (min.x > x) min.x = x;
	if (min.y > y) min.y = y;
	if (min.z > z) min.z = z;
	if (max.x < x) max.x = x;
	if (max.y < y) max.y = y;
	if (max.z < z) max.z = z;
}

template<typename T>
inline void aabbox<T>::include(const point3<T>& vec)
{
	include(vec.x, vec.y, vec.z);
}

template<typename T>
inline void aabbox<T>::include(const aabbox<T>& bbox)
{
	include(bbox.max);
	include(bbox.min);
}

template<typename T>
inline void aabbox<T>::include(const point3<T>& center, T radius)
{
	include(center + vec3<T>(radius));
	include(center - vec3<T>(radius));
}

template<typename T>
inline bool aabbox<T>::contain(const point3<T>& point) const
{
	return (
		point.x <= max.x &&
		point.y <= max.y &&
		point.z <= max.z &&
		point.x >= min.x &&
		point.y >= min.y &&
		point.z >= min.z
	);
}

template<typename T>
inline bool aabbox<T>::contain(const aabbox<T>& bbox) const
{
	return contain(bbox.min) && contain(bbox.max);
}

template<typename T>
inline bool aabbox<T>::contain(const point3<T>& center, T radius) const
{
	return contain(center + vec3<T>(radius)) && contain(center - vec3<T>(radius));
}

template<typename T>
inline bool aabbox<T>::overlap(const aabbox<T>& bbox) const
{
	return (bbox.min.x <= max.x &&
		bbox.min.y <= max.y &&
		bbox.min.z <= max.z) &&
		(bbox.max.x >= min.x &&
		bbox.max.y >= min.y &&
		bbox.max.z >= min.z);
}

template<typename T>
inline bool aabbox<T>::overlap(const point3<T>& center, T radius) const
{
	// works in n dimension
	// Jim Arvo, Graphics Gems 2
	float r2 = radius * radius;
	float dmin = 0;
	for (size_t i = 0; i < 3; i++)
	{
		if (center[i] < min[i])
			dmin += sqr<T>(center[i] - min[i]);
		else if (center[i] > max[i])
			dmin += sqr<T>(center[i] - max[i]);
	}
	return dmin <= r2;
}

template <typename T>
bool operator==(const aabbox<T>& lhs, const aabbox<T>& rhs)
{
	return lhs.min == rhs.min && lhs.max == rhs.max;
}

template <typename T>
bool operator!=(const aabbox<T>& lhs, const aabbox<T>& rhs)
{
	return lhs.min != rhs.min || lhs.max != rhs.max;
}

template<typename T>
aabbox<T> operator*(const mat4<T>& transform, const aabbox<T>& bbox)
{
	point3<T> points[8] = {
		point3<T>(bbox.min.x, bbox.min.y, bbox.min.z),
		point3<T>(bbox.min.x, bbox.max.y, bbox.min.z),
		point3<T>(bbox.min.x, bbox.min.y, bbox.max.z),
		point3<T>(bbox.min.x, bbox.max.y, bbox.max.z),
		point3<T>(bbox.max.x, bbox.min.y, bbox.min.z),
		point3<T>(bbox.max.x, bbox.max.y, bbox.min.z),
		point3<T>(bbox.max.x, bbox.min.y, bbox.max.z),
		point3<T>(bbox.max.x, bbox.max.y, bbox.max.z),
	};
	aabbox out;
	for (const point3<T>& point : points)
		out.include(transform.multiplyPoint(point));
	return out;
}

};