#include <geo/math/coordinates.h>

namespace geometry {

template <typename T>
inline void onb(const vec3<T>& normal, vec3<T>* tangent, vec3<T>* binormal)
{
	if (abs(normal.x) > abs(normal.z))
	{
		binormal->x = -normal.y;
		binormal->y = normal.x;
		binormal->z = 0;
	}
	else
	{
		binormal->x = 0;
		binormal->y = -normal.z;
		binormal->z = normal.y;
	}

	*binormal = normalize(*binormal);
	*tangent = cross(*binormal, normal);
}

template <typename T>
inline polar<T>::polar()
{
}

template <typename T>
inline polar<T>::polar(const vec2<T>& vec) :
	theta(arccos(vec.z / vec.norm())),
	r(vec.norm())
{
}

template <typename T>
inline polar<T>::polar(radian<T> theta, T r) :
	theta(theta),
	r(r)
{
}

template <typename T>
inline vec2<T> polar<T>::cartesian() const
{
	return vec2<T>(
		r * cos(theta),
		r * sin(theta)
	);
}

template <typename T>
inline spherical<T>::spherical()
{
}

template <typename T>
inline spherical<T>::spherical(radian<T> phi, radian<T> theta, T r) :
	phi(phi),
	theta(theta),
	r(r)
{
}

template <typename T>
inline spherical<T>::spherical(const vec3<T>& vec) :
	phi(arctan(vec.y / vec.x)),
	theta(arccos(vec.z / vec.norm())),
	r(vec.norm())
{
}

template <typename T>
inline vec3<T> spherical<T>::cartesian() const
{
	const T cosPhi = cos(phi);
	const T cosTheta = cos(theta);
	const T sinPhi = sin(phi);
	const T sinTheta = sin(theta);
	return vec3<T>(
		r * sinTheta * sinPhi,
		r * sinTheta * cosPhi,
		r * cosTheta
	);
}

template <typename T>
inline cylindrical<T>::cylindrical()
{
}

template <typename T>
inline cylindrical<T>::cylindrical(const vec3<T>& vec) :
	rho(sqrt(vec.x * vec.x + vec.y * vec.y)),
	phi(),
	z(vec.z)
{
	if (vec.x = 0 & vec.y == 0)
		phi = 0;
	else if (x >= 0)
		phi = arcsin(vec.y / rho);
	else if (x > 0)
		phi = arctan(vec.y / vec.x);
	else if (x < 0)
		phi = -arcsin(vec.y / rho) + pi<T>;
}

template <typename T>
inline cylindrical<T>::cylindrical(radian<T> phi, T rho, T z) :
	rho(rho),
	phi(phi),
	z(z)
{
}

template <typename T>
inline vec3<T> cylindrical<T>::cartesian() const
{
	return vec3<T>(
		rho * cos(phi),
		rho * sin(phi),
		z
	);
}

}