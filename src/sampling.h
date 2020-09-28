#pragma once

#include "angle.h"
#include "vec3.h"
#include "vec3.h"

namespace geometry {

template <typename T>
struct CylindricalCoordinate {
	CylindricalCoordinate(radian<T> phi, radian<T> theta, T r) : phi(phi), theta(theta), r(r) {}
	CylindricalCoordinate(vec3<T> vec) : phi(arctan(vec.y / vec.x)), theta(arccos(vec.z / vec.norm())), r(vec.norm()) {}
	
	explicit operator vec3<T>() const;
	explicit operator CylindricalCoordinate<T>() const;
};

template <typename T>
struct PolarCoordinate {
	PolarCoordinate(radian<T> theta, T r) : theta(theta), r(r) {}
	PolarCoordinate(vec2<T> vec) : theta(arccos(vec.z / vec.norm())), r(vec.norm()) {}
	
	explicit operator vec2<T>() const {
		return vec2<T>(
			r * cos(theta),
			r * sin(theta)
		);
	}
private:
	radian<T> theta;
	float r;
};

// https://en.wikipedia.org/wiki/Spherical_coordinate_system
template <typename T>
struct SphericalCoordinate {
	SphericalCoordinate(radian<T> phi, radian<T> theta, T r) : phi(phi), theta(theta), r(r) {}
	SphericalCoordinate(vec3<T> vec) : phi(arctan(vec.y / vec.x)), theta(arccos(vec.z / vec.norm())), r(vec.norm()) {}
	
	explicit operator vec3<T>() const { return toCartesian(cos(phi), cos(theta), sin(phi), sin(theta), r); }
	explicit operator CylindricalCoordinate<T>() const;
	
	static vec3<T> toCartesian(T cosPhi, T cosTheta, T sinPhi, T sinTheta, T r)
	{
		return vec3<T>(
			r * sinTheta * sinPhi,
			r * sinTheta * cosPhi,
			r * cosTheta
		);
	}
private:
	radian<T> phi;
	radian<T> theta;
	float r;
};

template <typename T>
vec3<T> reflect(const vec3<T> &wi, const norm3<T> &normal)
{
	vec3f n(normal);
	return wi - 2.f * vec3f::dot(wi, n) * n;
}

template <typename T>
bool refract(vec3<T> &wo, const vec3<T> &wi, const norm3<T> &normal, float eta)
{
	vec3f n(normal);
	float NdotV = vec3f::dot(wi, vec3f(n));
	float k = 1.f - eta * eta * (1.f - NdotV * NdotV);
	if (k < 0.f)
		return true;
	wo = vec3f::normalize(eta * wi - (eta*NdotV + geometry::sqrt(k)) * vec3f(n));
	return false;
}

namespace sample {

// Disk sampling projected on hemisphere. More efficient and give a cosine weighted distribution
// from Global Illuination Compendium item 35
// http://www.rorydriscoll.com/2009/01/07/better-sampling/
template <typename T>
vec3<T> unitHemisphere(T r1, T r2)
{
	PolarCoordinate<T> polar(2.0 * pi<T> * r2, sqrt(r1));
	return vec3<T>(vec2<T>(polar), sqrt(1.f - r1));
}

template <typename T>
vec3<T> unitSphere(T r1, T r2)
{
	SphericalCoordinate<T> spherical(2.f * pi<T> * r1, arccos(1.f - 2.f * r2), 1.f);
	return vec3<T>(spherical);
}

template <typename T>
vec2<T> unitDisk(T r1, T r2)
{
	PolarCoordinate<T> polar(2.0 * pi<T> * r2, sqrt(r1));
	return vec2<T>(polar);
}

template <typename T>
vec3<T> unitMicrofacet(T roughness, T r1, T r2)
{
	SphericalCoordinate<T> spherical(arctan(roughness * sqrt(r1) / sqrt(1.f - r1)), 2.f * pi<float> * r2, 1.f);
	return vec3<T>(spherical);
}

}

// Determine coordinate system for whole app
template <typename T>
vec3<T> localToWorld(vec3<T> local, vec3<T> N, vec3<T> X, vec3<T> Y)
{
	return vec3<T>::normalize(
		local.x * X +
		local.y * Y +
		local.z * N
	);
}

template <typename T>
void onb(const vec3<T> &normal, vec3<T> *tangent, vec3<T> *binormal)
{
	if (abs(normal.x) > abs(normal.z))
	{
		binormal->x = -normal.y;
		binormal->y =  normal.x;
		binormal->z =  0;
	}
	else
	{
		binormal->x =  0;
		binormal->y = -normal.z;
		binormal->z =  normal.y;
	}

	*binormal = normalize(*binormal);
	*tangent = cross(*binormal, normal);
}


}