#include <geo/math/aabbox.h>

#include <limits>

namespace geometry {

template<typename T>
inline aabbox<T>::aabbox() :
	aabbox(
		point3<T>(std::numeric_limits<T>::max()), 
		point3<T>(-std::numeric_limits<T>::max())
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
	min = point3<T>(std::numeric_limits<T>::max());
	max = point3<T>(-std::numeric_limits<T>::max());
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
inline void aabbox<T>::include(const point3<T>& vec)
{
	if (min.x > vec.x) min.x = vec.x;
	if (min.y > vec.y) min.y = vec.y;
	if (min.z > vec.z) min.z = vec.z;
	if (max.x < vec.x) max.x = vec.x;
	if (max.y < vec.y) max.y = vec.y;
	if (max.z < vec.z) max.z = vec.z;
}

template<typename T>
inline void aabbox<T>::include(const aabbox<T>& bbox)
{
	include(bbox.max);
	include(bbox.min);
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
inline bool aabbox<T>::overlap(const aabbox<T>& bbox) const
{
	return (bbox.min.x <= max.x &&
		bbox.min.y <= max.y &&
		bbox.min.z <= max.z) &&
		(bbox.max.x >= min.x &&
		bbox.max.y >= min.y &&
		bbox.max.z >= min.z);
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

};