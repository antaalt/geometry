#pragma once

#include <geo/math/angle.h>
#include <geo/vector/vec3.h>

namespace geometry {

template <typename T>
void onb(const vec3<T>& normal, vec3<T>* tangent, vec3<T>* binormal);

template <typename T>
struct polar {
	polar();
	explicit polar(const vec2<T>& vec);
	explicit polar(radian<T> theta, T r);

	vec2<T> cartesian() const;
private:
	radian<T> theta;
	T r;
};

template <typename T>
struct spherical {
	spherical();
	spherical(const vec3<T>& vec);
	spherical(radian<T> phi, radian<T> theta, T r);

	vec3<T> cartesian() const;
private:
	radian<T> phi;
	radian<T> theta;
	T r;
};

template <typename T>
struct cylindrical {
	cylindrical();
	explicit cylindrical(const vec3<T>& vec);
	explicit cylindrical(radian<T> phi, T rho, T z);

	vec3<T> cartesian() const;
private:
	T rho;
	radian<T> phi;
	T z;
};

};