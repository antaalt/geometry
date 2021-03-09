#pragma once

#include <geo/core/types.h>

namespace geometry {

template <typename T>
struct point3;
template <typename T>
struct vec3;

template <typename T = real_t>
struct aabbox
{
	aabbox();
	aabbox(const point3<T>& min, const point3<T>& max);

	// Reset the bounding box and make it invalid
	void reset();
	// Is the bounding box valid
	bool valid() const;

	// Get the extent (aka. size) of the bounding box
	vec3<T> extent() const;
	// Get the center of the bounding box
	point3<T> center() const;

	// Make the bounding box include a point
	void include(const point3<T>& vec);
	// Make the bounding box include a bounding box
	void include(const aabbox<T>& bbox);

	// Check if the bounding box contain a point
	bool contain(const point3<T>& point) const;
	// Check if the bounding box contain a whole bounding box
	bool contain(const aabbox<T>& bbox) const;
	// Check if the bounding box overlap a bounding box
	bool overlap(const aabbox<T>& bbox) const;

	point3<T> min, max;
};

template <typename T>
bool operator==(const aabbox<T>& lhs, const aabbox<T>& rhs);
template <typename T>
bool operator!=(const aabbox<T>& lhs, const aabbox<T>& rhs);

};