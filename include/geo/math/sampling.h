#pragma once

#include <geo/math/angle.h>
#include <geo/math/coordinates.h>
#include <geo/vector/vec3.h>

namespace geometry {

template <typename T>
vec2<T> reflect(const vec2<T>& wi, const vec2<T>& normal)
{
	return wi - 2.f * vec2<T>::dot(wi, normal) * vec3<T>(normal);
}

template <typename T>
vec3<T> reflect(const vec3<T> &wi, const norm3<T> &normal)
{
	return wi - 2.f * vec3<T>::dot(wi, normal) * vec3<T>(normal);
}

template <typename T>
bool refract(vec3<T> &wo, const vec3<T> &wi, const norm3<T> &normal, float eta)
{
	float NdotV = vec3<T>::dot(wi, normal);
	float k = 1.f - eta * eta * (1.f - NdotV * NdotV);
	if (k < 0.f)
		return true;
	wo = vec3<T>::normalize(eta * wi - (eta*NdotV + sqrt(k)) * vec3<T>(normal));
	return false;
}

namespace sample {

// Disk sampling projected on hemisphere. More efficient and give a cosine weighted distribution
// from Global Illuination Compendium item 35
// http://www.rorydriscoll.com/2009/01/07/better-sampling/
template <typename T>
vec3<T> unitHemisphere(T r1, T r2)
{
	return vec3<T>(polar<T>(2.0 * pi<T> *r2, sqrt(r1)).cartesian(), sqrt(1.f - r1));
}

template <typename T>
vec3<T> unitSphere(T r1, T r2)
{
	return spherical<T>(2.f * pi<T> * r1, arccos(1.f - 2.f * r2), 1.f).cartesian();
}

template <typename T>
vec2<T> unitDisk(T r1, T r2)
{
	return polar<T>(2.0 * pi<T> *r2, sqrt(r1)).cartesian();
}

template <typename T>
vec3<T> unitMicrofacet(T roughness, T r1, T r2)
{
	return spherical<T>(arctan(roughness * sqrt(r1) / sqrt(1.f - r1)), 2.f * pi<float> * r2, 1.f).cartesian();
}

}


}