#include <geo/math/sampling.h>

namespace geometry {

template <typename T>
inline vec2<T> reflect(const vec2<T>& wi, const vec2<T>& normal)
{
	return wi - 2.f * vec2<T>::dot(wi, normal) * normal;
}

template <typename T>
inline vec3<T> reflect(const vec3<T>& wi, const norm3<T>& normal)
{
	return wi - 2.f * vec3<T>::dot(wi, normal) * vec3<T>(normal);
}

template <typename T>
inline bool refract(vec3<T>& wo, const vec3<T>& wi, const norm3<T>& normal, real_t eta)
{
	T NdotV = vec3<T>::dot(wi, normal);
	T k = T(1) - eta * eta * (T(1) - NdotV * NdotV);
	if (k < T(0))
		return true;
	wo = vec3<T>::normalize(eta * wi - (eta * NdotV + sqrt(k)) * vec3<T>(normal));
	return false;
}

}
