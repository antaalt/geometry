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
	explicit polar(angle<T> theta, T r);

	vec2<T> cartesian() const;
private:
	angle<T> theta;
	T r;
};

template <typename T>
struct spherical {
	spherical();
	spherical(const vec3<T>& vec);
	spherical(angle<T> phi, angle<T> theta, T r);

	vec3<T> cartesian() const;
private:
	angle<T> phi;
	angle<T> theta;
	T r;
};

template <typename T>
struct cylindrical {
	cylindrical();
	explicit cylindrical(const vec3<T>& vec);
	explicit cylindrical(angle<T> phi, T rho, T z);

	vec3<T> cartesian() const;
private:
	T rho;
	angle<T> phi;
	T z;
};

};