#include <geo/math/frustum.h>

namespace geometry {

template <typename T>
inline frustum<T> frustum<T>::fromProjection(const mat4<T>& projection)
{
	return frustum<T>::fromInverseProjection(mat4<T>::inverse(projection));
}

template <typename T>
inline frustum<T> frustum<T>::fromInverseProjection(const mat4<T>& inverseProjection)
{
#if defined(GEOMETRY_CLIP_SPACE_NEGATIVE)
	const T clipMinZ = static_cast<T>(-1);
#else
	const T clipMinZ = static_cast<T>(0);
#endif
	const T clipMaxZ = static_cast<T>(1);
	frustum<T> f;
	// https://gamedev.stackexchange.com/questions/183196/calculating-directional-shadow-map-using-camera-frustum
	f.corners[0] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(-1), static_cast<T>(-1), clipMinZ));
	f.corners[1] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(-1), static_cast<T>(-1), clipMaxZ));
	f.corners[2] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(1), static_cast<T>(-1), clipMinZ));
	f.corners[3] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(-1), static_cast<T>(1), clipMinZ));
	f.corners[4] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(1), static_cast<T>(-1), clipMaxZ));
	f.corners[5] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(-1), static_cast<T>(1), clipMaxZ));
	f.corners[6] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(1), static_cast<T>(1), clipMinZ));
	f.corners[7] = inverseProjection.multiplyPoint(point3<T>(static_cast<T>(1), static_cast<T>(1), clipMaxZ));
	return f;
}

template <typename T>
inline point3<T> frustum<T>::center() const
{
	point3<T> c = point3<T>(0.f);
	for (size_t i = 0; i < 8; i++)
		for (size_t id = 0; id < 3; id++)
			c.data[id] += corners[i].data[id];
	return c / static_cast<T>(8);
}

template<typename T>
inline bool frustum<T>::operator==(const frustum<T>& rhs) const
{
	for (size_t i = 0; i < 8; i++)
		if (corners[i] != rhs.corners[i])
			return false;
	return true;
}

template<typename T>
inline bool frustum<T>::operator!=(const frustum<T>& rhs) const
{
	for (size_t i = 0; i < 8; i++)
		if (corners[i] != rhs.corners[i])
			return true;
	return false;
}

}