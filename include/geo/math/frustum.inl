#include <geo/math/frustum.h>

namespace geometry {

template<typename T>
inline bool frustum<T>::planes::intersect(const aabbox<T>& bound) const
{
	// https://www.iquilezles.org/www/articles/frustumcorrect/frustumcorrect.htm
	for (int i = 0; i < 6; i++)
	{
		// Check the box outside or inside of frustum
		int out = 0;
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.min.x, bound.min.y, bound.min.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.max.x, bound.min.y, bound.min.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.min.x, bound.max.y, bound.min.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.max.x, bound.max.y, bound.min.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.min.x, bound.min.y, bound.max.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.max.x, bound.min.y, bound.max.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.min.x, bound.max.y, bound.max.z, 1.0)) < 0.0) ? 1 : 0);
		out += ((vec4<T>::dot(planes[i], vec4<T>(bound.max.x, bound.max.y, bound.max.z, 1.0)) < 0.0) ? 1 : 0);
		if (out == 8) return false;
	}
	return true;
}

template<typename T>
inline typename frustum<T>::planes frustum<T>::extract(const mat4<T>& projection)
{
	planes p;
#if defined(GEOMETRY_LEFT_HANDED)
	// left
	p.planes[0].x = projection[0][3] + projection[0][0];
	p.planes[0].y = projection[1][3] + projection[1][0];
	p.planes[0].z = projection[2][3] + projection[2][0];
	p.planes[0].w = projection[3][3] + projection[3][0];
	// right
	p.planes[1].x = projection[0][3] - projection[0][0];
	p.planes[1].y = projection[1][3] - projection[1][0];
	p.planes[1].z = projection[2][3] - projection[2][0];
	p.planes[1].w = projection[3][3] - projection[3][0];
	// bottom
	p.planes[2].x = projection[0][3] + projection[0][1];
	p.planes[2].y = projection[1][3] + projection[1][1];
	p.planes[2].z = projection[2][3] + projection[2][1];
	p.planes[2].w = projection[3][3] + projection[3][1];
	// top
	p.planes[3].x = projection[0][3] - projection[0][1];
	p.planes[3].y = projection[1][3] - projection[1][1];
	p.planes[3].z = projection[2][3] - projection[2][1];
	p.planes[3].w = projection[3][3] - projection[3][1];
	// near
	p.planes[4].x = projection[0][2];
	p.planes[4].y = projection[1][2];
	p.planes[4].z = projection[2][2];
	p.planes[4].w = projection[3][2];
	// far
	p.planes[5].x = projection[0][3] - projection[0][2];
	p.planes[5].y = projection[1][3] - projection[1][2];
	p.planes[5].z = projection[2][3] - projection[2][2];
	p.planes[5].w = projection[3][3] - projection[3][2];
#else
	// left
	p.planes[0].x = projection[0][3] + projection[0][0];
	p.planes[0].y = projection[1][3] + projection[1][0];
	p.planes[0].z = projection[2][3] + projection[2][0];
	p.planes[0].w = projection[3][3] + projection[3][0];
	// right
	p.planes[1].x = projection[0][3] - projection[0][0];
	p.planes[1].y = projection[1][3] - projection[1][0];
	p.planes[1].z = projection[2][3] - projection[2][0];
	p.planes[1].w = projection[3][3] - projection[3][0];
	// bottom
	p.planes[2].x = projection[0][3] + projection[0][1];
	p.planes[2].y = projection[1][3] + projection[1][1];
	p.planes[2].z = projection[2][3] + projection[2][1];
	p.planes[2].w = projection[3][3] + projection[3][1];
	// top
	p.planes[3].x = projection[0][3] - projection[0][1];
	p.planes[3].y = projection[1][3] - projection[1][1];
	p.planes[3].z = projection[2][3] - projection[2][1];
	p.planes[3].w = projection[3][3] - projection[3][1];
	// near
	p.planes[4].x = projection[0][3] + projection[0][2];
	p.planes[4].y = projection[1][3] + projection[1][2];
	p.planes[4].z = projection[2][3] + projection[2][2];
	p.planes[4].w = projection[3][3] + projection[3][2];
	// far
	p.planes[5].x = projection[0][3] - projection[0][2];
	p.planes[5].y = projection[1][3] - projection[1][2];
	p.planes[5].z = projection[2][3] - projection[2][2];
	p.planes[5].w = projection[3][3] - projection[3][2];
#endif
	return p;
}

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

template <typename T>
inline float frustum<T>::radius() const
{
	float radius = 0.f;
	point3<T> c = center();
	for (uint32_t i = 0; i < 8; i++) {
		float distance = (corners[i] - c).norm();
		radius = max(radius, distance);
	}
	return ceil(radius * 16.f) / 16.f;
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
