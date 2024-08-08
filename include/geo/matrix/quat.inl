#include <geo/matrix/quat.h>

namespace geometry {

template <typename T>
inline quat<T>::quat()
{
}

template <typename T>
template <typename U>
inline quat<T>::quat(U x, U y, U z, U w) :
	x((T)x), y((T)y), z((T)z), w((T)w)
{
}

template <typename T>
inline quat<T>::quat(T x, T y, T z, T w) :
	x(x), y(y), z(z), w(w)
{
}

template<typename T>
inline quat<T>::quat(const mat3<T>& m)
{
	// Converting a Rotation Matrix to a Quaternion - Mike Day, Insomniac Games
	// This assume a pure rotation matrix (without shear and such)
	T t;
	if (m[2][2] < 0) 
	{ 
		if (m[0][0] > m[1][1]) 
		{
			t = T(1) + m[0][0] - m[1][1] - m[2][2];
			x = t;
			y = m[1][0] + m[0][1];
			z = m[0][2] + m[2][0];
			w = m[2][1] - m[1][2];
		}
		else 
		{ 
			t = T(1) - m[0][0] + m[1][1] - m[2][2];
			x = m[1][0] + m[0][1];
			y = t;
			z = m[2][1] + m[1][2];
			w = m[0][2] - m[2][0];
		} 
	}
	else 
	{ 
		if (m[0][0] < -m[1][1]) 
		{ 
			t = T(1) - m[0][0] - m[1][1] + m[2][2];
			x = m[0][2] + m[2][0];
			y = m[2][1] + m[1][2];
			z = t;
			w = m[1][0] - m[0][1];
		} 
		else 
		{ 
			t = T(1) + m[0][0] + m[1][1] + m[2][2];
			x = m[2][1] - m[1][2];
			y = m[0][2] - m[2][0];
			z = m[1][0] - m[0][1];
			w = t;
		} 
	}
	*this *= T(0.5) / sqrt(t);
}

template <typename T>
inline T & quat<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T & quat<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
inline T quat<T>::norm() const
{
	return sqrt(x*x + y*y + z*z + w*w);
}

template <typename T>
inline quat<T> quat<T>::identity()
{
	return quat(0.f, 0.f, 0.f, 1.f);
}

template <typename T>
inline quat<T> quat<T>::inverse(const quat<T>& quaternion)
{
	quat<T> out;
	T n = quaternion.norm();
	out = conjuguate(quaternion);
	out.x /= n;
	out.y /= n;
	out.z /= n;
	out.w /= n;
	return out;
}

template <typename T>
inline quat<T> quat<T>::conjuguate(const quat & quaternion)
{
	return quat(
		-quaternion.x,
		-quaternion.y,
		-quaternion.z,
		quaternion.w
	);
}

template <typename T>
inline quat<T> quat<T>::normalize(const quat & quaternion)
{
	T n = quaternion.norm();
	return quat(
		quaternion.x / n,
		quaternion.y / n,
		quaternion.z / n,
		quaternion.w / n
	);
}

template <typename T>
inline quat<T> quat<T>::axis(const vec3<T> & axis, const angle<T> & angle)
{
	T sinHalfAngle = sin(angle / T(2));
	return quat(
		axis.x * sinHalfAngle,
		axis.y * sinHalfAngle,
		axis.z * sinHalfAngle,
		cos(angle / T(2))
	);
}

template <typename T>
inline quat<T> quat<T>::euler(angle<T> yaw, angle<T> pitch, angle<T> roll)
{
	T cr, sr, cp, sp, cy, sy;
	sincos(roll * T(0.5), sr, cr);
	sincos(pitch * T(0.5), sp, cp);
	sincos(yaw * T(0.5), sy, cy);
	return quat<T>(
			cr * cp * cy + sr * sp * sy,
			sr * cp * cy - cr * sp * sy,
			cr * sp * cy + sr * cp * sy,
			cr * cp * sy - sr * sp * cy
	);
}

template<typename T>
inline real_t quat<T>::dot(const quat& lhs, const quat& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

template<typename T>
inline quat<T> quat<T>::slerp(const quat& from, const quat& to, real_t t)
{
	// Only unit quaternion are valid rotations. Avoid UB.
	quat fromNormalized = quat::normalize(from);
	quat toNormalized = quat::normalize(to);
	T cosHalfTheta = quat::dot(fromNormalized, toNormalized);
	// Follow shortest path.
	if (cosHalfTheta < T(0))
	{
		toNormalized = -toNormalized;
		cosHalfTheta = -cosHalfTheta;
	}
	if (cosHalfTheta > T(0.999))
	{
		// If the inputs are too close, simply lerp & normalize.
		return quat::normalize(geometry::lerp(fromNormalized, toNormalized, t));
	}
	angle<T> halfTheta = geometry::arccos(cosHalfTheta);
	float sinHalfTheta = geometry::sin(halfTheta);
	return (fromNormalized * geometry::sin((real_t(1) - t) * halfTheta) + toNormalized * geometry::sin(t * halfTheta)) / sinHalfTheta;
}


template <typename T>
inline bool operator==(const quat<T>& lhs, const quat<T>& rhs)
{
	return !operator!=(lhs, rhs);
}

template <typename T>
inline bool operator!=(const quat<T>& lhs, const quat<T>& rhs)
{
	for (uint32_t i = 0; i < 4; i++)
		if (lhs.data[i] != rhs.data[i])
			return true;
	return false;
}

template <typename T>
inline quat<T> operator*(const quat<T>& lhs, real_t scalar)
{
	quat out(lhs);
	out *= scalar;
	return out;
}

template <typename T>
inline quat<T> operator*(real_t scalar, const quat<T>& rhs)
{
	quat out(rhs);
	out *= scalar;
	return out;
}

template <typename T>
inline quat<T> & operator*=(quat<T>& lhs, real_t scalar)
{
	lhs.x *= scalar;
	lhs.y *= scalar;
	lhs.z *= scalar;
	lhs.w *= scalar;
	return lhs;
}

template <typename T>
quat<T> operator/(const quat<T>& lhs, real_t scalar)
{
	quat out(lhs);
	out /= scalar;
	return out;
}

template <typename T>
quat<T>& operator/=(quat<T>& lhs, real_t scalar)
{
	lhs.x /= scalar;
	lhs.y /= scalar;
	lhs.z /= scalar;
	lhs.w /= scalar;
	return lhs;
}

template <typename T>
inline quat<T> operator*(const quat<T>& lhs, const quat<T>& rhs)
{
	quat out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline quat<T> & operator*=(quat<T>& lhs, const quat<T>& rhs)
{
	lhs.x =  lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y + lhs.w * rhs.x;
	lhs.y = -lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x + lhs.w * rhs.y;
	lhs.z =  lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w + lhs.w * rhs.z;
	lhs.w = -lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z + lhs.w * rhs.w;
	return lhs;
}

template <typename T>
inline quat<T> operator+(const quat<T>& lhs, const quat<T>& rhs)
{
	quat out(lhs);
	out += rhs;
	return out;
}

template <typename T>
inline quat<T> & operator+=(quat<T>& lhs, const quat<T> & rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	lhs.w += rhs.w;
	return lhs;
}

template <typename T>
inline quat<T> operator-(const quat<T>& lhs, const quat<T>& rhs)
{
	quat out(lhs);
	out -= rhs;
	return out;
}

template <typename T>
inline quat<T> & operator-=(quat<T>& lhs, const quat<T>& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	lhs.w -= rhs.w;
	return lhs;
}

template <typename T>
quat<T> operator-(const quat<T>& q)
{
	return quat(
		-q.x,
		-q.y,
		-q.z,
		-q.w
	);
}

template <typename T>
inline vec3<T> operator*(const quat<T>& lhs, const vec3<T> & rhs)
{
	quat pcq = quat(rhs.x, rhs.y, rhs.z, 0.f) * quat(-lhs.x, -lhs.y, -lhs.z, lhs.w);
	quat q = lhs * pcq;
	return vec3<T>(q.x, q.y, q.z);
}

}
