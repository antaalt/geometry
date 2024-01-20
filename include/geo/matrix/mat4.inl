#include <geo/matrix/mat4.h>
#include <geo/matrix/mat3.h>
#include <geo/matrix/quat.h>
#include <geo/vector/norm3.h>
#include <geo/vector/point3.h>
#include <geo/vector/vec3.h>

namespace geometry {


template <typename T>
inline col4<T>::col4()
{
}

template <typename T>
inline col4<T>::col4(T value) :
	x(value), y(value), z(value), w(value)
{
}

template <typename T>
inline col4<T>::col4(T x, T y, T z, T w) :
	x(x), y(y), z(z), w(w)
{
}

template <typename T>
template <typename U>
inline col4<T>::col4(U x, U y, U z, U w) :
	x((T)x), y((T)y), z((T)z), w((T)w)
{

}

template <typename T>
inline col4<T>::col4(norm3<T> vec, T w) :
	x(vec.x), y(vec.y), z(vec.z), w(w)
{
}

template <typename T>
inline col4<T>::col4(vec3<T> vec, T w) :
	x(vec.x), y(vec.y), z(vec.z), w(w)
{
}

template <typename T>
inline col4<T>::col4(vec4<T> vec) :
	x(vec.x), y(vec.y), z(vec.z), w(vec.w)
{
}

template <typename T>
inline col4<T>::col4(point3<T> vec, T w) :
	x(vec.x), y(vec.y), z(vec.z), w(w)
{
}

template <typename T>
inline T & col4<T>::operator[](size_t index)
{
	return data[index];
}

template <typename T>
inline const T & col4<T>::operator[](size_t index) const
{
	return data[index];
}

template <typename T>
inline mat4<T>::mat4()
{
}

template <typename T>
inline mat4<T>::mat4(T value) :
	cols{ col4<T>(value), col4<T>(value), col4<T>(value), col4<T>(value) }
{
}

template <typename T>
inline mat4<T>::mat4(col4<T> x, col4<T> y, col4<T> z, col4<T> w) :
	cols{ x, y, z, w }
{
}

template <typename T>
inline mat4<T>::mat4(const quat<T> & quat)
{
	T sqw = quat.w*quat.w;
	T sqx = quat.x*quat.x;
	T sqy = quat.y*quat.y;
	T sqz = quat.z*quat.z;

	T invs = T(1) / (sqx + sqy + sqz + sqw);

	cols[0] = col4<T>(
		(sqx - sqy - sqz + sqw)*invs,
		T(2) * (quat.x*quat.y + quat.z*quat.w)*invs,
		T(2) * (quat.x*quat.z - quat.y*quat.w)*invs,
		T(0)
	);
	cols[1] = col4<T>(
		T(2) * (quat.x*quat.y - quat.z*quat.w)*invs,
		(-sqx + sqy - sqz + sqw)*invs,
		T(2) * (quat.y*quat.z + quat.x*quat.w)*invs,
		T(0)
	);
	cols[2] = col4<T>(
		T(2) * (quat.x*quat.z + quat.y*quat.w)*invs,
		T(2) * (quat.y*quat.z - quat.x*quat.w)*invs,
		(-sqx - sqy + sqz + sqw)*invs,
		T(0)
	);
	cols[3] = col4<T>(
		T(0),
		T(0),
		T(0),
		T(1)
	);
}

template <typename T>
inline mat4<T>::mat4(const mat3<T>& matrix) :
	cols{
		col4<T>{ matrix[0].x, matrix[0].y, matrix[0].z, T(0) },
		col4<T>{ matrix[1].x, matrix[1].y, matrix[1].z, T(0) },
		col4<T>{ matrix[2].x, matrix[2].y, matrix[2].z, T(0) },
		col4<T>{ T(0), T(0), T(0), T(1) },
	}
{
}

template <typename T>
inline col4<T> & mat4<T>::operator[](size_t index)
{
	return cols[index];
}

template <typename T>
inline const col4<T> & mat4<T>::operator[](size_t index) const
{
	return cols[index];
}

template <typename T>
inline mat4<T> operator*(const mat4<T>& lhs, const mat4<T> &rhs)
{
	mat4<T> out(lhs);
	out *= rhs;
	return out;
}

template <typename T>
inline mat4<T> &operator*=(mat4<T>& lhs, const mat4<T> &rhs)
{
	mat4<T> out(0.f);
	for (int iCol = 0; iCol < 4; iCol++)
		for (int iRow = 0; iRow < 4; iRow++)
			for (int k = 0; k < 4; k++)
				out[iCol][iRow] += lhs[k][iRow] * rhs[iCol][k];
	return (lhs = out);
}

template <typename T>
inline point3<T> operator*(const mat4<T>& lhs, const point3<T> &rhs)
{
	return lhs.multiplyPoint(rhs);
}

template <typename T>
inline vec3<T> operator*(const mat4<T>& lhs, const vec3<T> &rhs)
{
	return lhs.multiplyVector(rhs);
}

template<typename T>
vec4<T> operator*(const mat4<T>& lhs, const vec4<T>& rhs)
{
	return vec4<T>(
		lhs[0].x * rhs.x + lhs[1].x * rhs.y + lhs[2].x * rhs.z + lhs[3].x * rhs.w,
		lhs[0].y * rhs.x + lhs[1].y * rhs.y + lhs[2].y * rhs.z + lhs[3].y * rhs.w,
		lhs[0].z * rhs.x + lhs[1].z * rhs.y + lhs[2].z * rhs.z + lhs[3].z * rhs.w,
		lhs[0].w * rhs.x + lhs[1].w * rhs.y + lhs[2].w * rhs.z + lhs[3].w * rhs.w
	);
}

template <typename T>
inline mat4<T> mat4<T>::identity()
{
	return mat4<T>(
		col4<T>(1.f, 0.f, 0.f, 0.f),
		col4<T>(0.f, 1.f, 0.f, 0.f),
		col4<T>(0.f, 0.f, 1.f, 0.f),
		col4<T>(0.f, 0.f, 0.f, 1.f)
	);
}

template <typename T>
inline mat4<T> mat4<T>::rotate(const vec3<T> &axis, angle<T> angle)
{
	// NOTE: Element 0,1 is wrong in Foley and Van Dam, Pg 227!
	T sintheta = sin(angle);
	T costheta = cos(angle);
	vec3<T> an = vec3<T>::normalize(axis);
	T ux = an.x;
	T uy = an.y;
	T uz = an.z;
	return mat4(
		col4<T>(
			ux*ux + costheta*(1 - ux*ux),
			ux*uy*(T(1) - costheta) - uz*sintheta,
			uz*ux*(T(1) - costheta) + uy*sintheta,
			T(0)
		),
		col4<T>(
			ux*uy*(T(1) - costheta) + uz*sintheta,
			uy*uy + costheta*(T(1) - uy*uy),
			uy*uz*(T(1) - costheta) - ux*sintheta,
			T(0)
		),
		col4<T>(
			uz*ux*(T(1) - costheta) - uy*sintheta,
			uy*uz*(T(1) - costheta) + ux*sintheta,
			uz*uz + costheta*(T(1) - uz*uz),
			T(0)
		),
		col4<T>(T(0), T(0), T(0), T(1))
	);
}

template <typename T>
inline mat4<T> mat4<T>::rotate(const quat<T>& quat)
{
	return mat4<T>(quat);
}

template <typename T>
inline mat4<T> mat4<T>::translate(const point3<T>& translation)
{
	return mat4<T>(
		col4<T>(T(1), T(0), T(0), T(0)),
		col4<T>(T(0), T(1), T(0), T(0)),
		col4<T>(T(0), T(0), T(1), T(0)),
		col4<T>(translation, T(1))
	);
}

template <typename T>
inline mat4<T> mat4<T>::translate(const vec3<T> &translation)
{
	return mat4<T>(
		col4<T>(T(1), T(0), T(0), T(0)),
		col4<T>(T(0), T(1), T(0), T(0)),
		col4<T>(T(0), T(0), T(1), T(0)),
		col4<T>(translation, T(1))
	);
}

template <typename T>
inline mat4<T> mat4<T>::translate(const mat4<T>& src, const vec3<T>& translation)
{
	mat4 dst(src);
	dst.cols[3].x += translation.x;
	dst.cols[3].y += translation.y;
	dst.cols[3].z += translation.z;
	return dst;
}

template <typename T>
inline mat4<T> mat4<T>::scale(const vec3<T> &scale)
{
	return mat4<T>(
		col4<T>(scale.x, T(0), T(0), T(0)),
		col4<T>(T(0), scale.y, T(0), T(0)),
		col4<T>(T(0), T(0), scale.z, T(0)),
		col4<T>(T(0), T(0), T(0), T(1))
	);
}

template <typename T>
inline mat4<T> mat4<T>::TRS(const vec3<T> & t, const quat<T> & r, const vec3<T> & s)
{
	return translate(t) * rotate(r) * scale(s);
}

template <typename T>
inline mat4<T> mat4<T>::inverse(const mat4 &mat)
{
	T A2323 = mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2];
	T A1323 = mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1];
	T A1223 = mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1];
	T A0323 = mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0];
	T A0223 = mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0];
	T A0123 = mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0];
	T A2313 = mat[1][2] * mat[3][3] - mat[1][3] * mat[3][2];
	T A1313 = mat[1][1] * mat[3][3] - mat[1][3] * mat[3][1];
	T A1213 = mat[1][1] * mat[3][2] - mat[1][2] * mat[3][1];
	T A2312 = mat[1][2] * mat[2][3] - mat[1][3] * mat[2][2];
	T A1312 = mat[1][1] * mat[2][3] - mat[1][3] * mat[2][1];
	T A1212 = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
	T A0313 = mat[1][0] * mat[3][3] - mat[1][3] * mat[3][0];
	T A0213 = mat[1][0] * mat[3][2] - mat[1][2] * mat[3][0];
	T A0312 = mat[1][0] * mat[2][3] - mat[1][3] * mat[2][0];
	T A0212 = mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0];
	T A0113 = mat[1][0] * mat[3][1] - mat[1][1] * mat[3][0];
	T A0112 = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];

	T det = 1.f / mat.det();

	return mat4(
		col4<T>(
			det *   (mat[1][1] * A2323 - mat[1][2] * A1323 + mat[1][3] * A1223),
			det * -(mat[0][1] * A2323 - mat[0][2] * A1323 + mat[0][3] * A1223),
			det *   (mat[0][1] * A2313 - mat[0][2] * A1313 + mat[0][3] * A1213),
			det * -(mat[0][1] * A2312 - mat[0][2] * A1312 + mat[0][3] * A1212)
		),
		col4<T>(
			det * -(mat[1][0] * A2323 - mat[1][2] * A0323 + mat[1][3] * A0223),
			det *   (mat[0][0] * A2323 - mat[0][2] * A0323 + mat[0][3] * A0223),
			det * -(mat[0][0] * A2313 - mat[0][2] * A0313 + mat[0][3] * A0213),
			det *   (mat[0][0] * A2312 - mat[0][2] * A0312 + mat[0][3] * A0212)
		),
		col4<T>(
			det *   (mat[1][0] * A1323 - mat[1][1] * A0323 + mat[1][3] * A0123),
			det * -(mat[0][0] * A1323 - mat[0][1] * A0323 + mat[0][3] * A0123),
			det *   (mat[0][0] * A1313 - mat[0][1] * A0313 + mat[0][3] * A0113),
			det * -(mat[0][0] * A1312 - mat[0][1] * A0312 + mat[0][3] * A0112)
		),
		col4<T>(
			det * -(mat[1][0] * A1223 - mat[1][1] * A0223 + mat[1][2] * A0123),
			det *   (mat[0][0] * A1223 - mat[0][1] * A0223 + mat[0][2] * A0123),
			det * -(mat[0][0] * A1213 - mat[0][1] * A0213 + mat[0][2] * A0113),
			det *   (mat[0][0] * A1212 - mat[0][1] * A0212 + mat[0][2] * A0112)
		)
	);
}
template <typename T>
inline mat4<T> mat4<T>::transpose(const mat4& mat)
{
	mat4<T> output;
	for (uint8_t x = 0; x < 4; x++)
		for (uint8_t y = 0; y < 4; y++)
			output[x][y] = mat[y][x];
	return output;
}

template <typename T>
inline mat4<T> mat4<T>::perspective(const angle<T> &fovY, real_t ratio, real_t zNear, real_t zFar)
{
	const T f = T(1) / tan(fovY / T(2));
	return mat4(
		col4<T>(f / ratio, T(0), T(0), T(0)),
		col4<T>(T(0), f, T(0), T(0)),
#if defined(GEOMETRY_RIGHT_HANDED)
#if defined(GEOMETRY_CLIP_SPACE_POSITIVE)
		col4<T>(T(0), T(0), zFar / (zNear - zFar), -T(1)),
		col4<T>(T(0), T(0), -(zFar * zNear) / (zFar - zNear), T(0))
#elif defined(GEOMETRY_CLIP_SPACE_NEGATIVE)
		col4<T>(T(0), T(0), -(zFar + zNear) / (zFar - zNear), -T(1)),
		col4<T>(T(0), T(0), -(T(2) * zFar * zNear) / (zFar - zNear), T(0))
#endif
#elif defined(GEOMETRY_LEFT_HANDED)
#if defined(GEOMETRY_CLIP_SPACE_POSITIVE)
		col4<T>(T(0), T(0), zFar / (zFar - zNear), T(1)),
		col4<T>(T(0), T(0), -(zFar * zNear) / (zFar - zNear), T(0))
#elif defined(GEOMETRY_CLIP_SPACE_NEGATIVE)
		col4<T>(T(0), T(0), (zFar + zNear) / (zFar - zNear), T(1)),
		col4<T>(T(0), T(0), -(T(2) * zFar * zNear) / (zFar - zNear), T(0))
#endif
#endif
	);
}

template <typename T>
inline mat4<T> mat4<T>::orthographic(real_t bottom, real_t top, real_t left, real_t right)
{
	return mat4(
		col4<T>(T(2) / (right - left), T(0), T(0), T(0)),
		col4<T>(T(0), T(2) / (top - bottom), T(0), T(0)),
		col4<T>(T(0), T(0), -T(1), T(0)),
		col4<T>(-(right + left) / (right - left), -(top + bottom) / (top - bottom), T(0), T(1))
	);
}

template <typename T>
inline mat4<T> mat4<T>::orthographic(real_t bottom, real_t top, real_t left, real_t right, real_t nearZ, real_t farZ)
{
	return mat4(
		col4<T>(T(2) / (right - left), T(0), T(0), T(0)),
		col4<T>(T(0), T(2) / (top - bottom), T(0), T(0)),
#if defined(GEOMETRY_RIGHT_HANDED)
#if defined(GEOMETRY_CLIP_SPACE_POSITIVE)
		col4<T>(T(0), T(0), -T(1) / (farZ - nearZ), T(0)),
		col4<T>(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -nearZ / (farZ - nearZ), T(1))
#elif defined(GEOMETRY_CLIP_SPACE_NEGATIVE)
		col4<T>(T(0), T(0), -T(2) / (farZ - nearZ), T(0)),
		col4<T>(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(farZ + nearZ) / (farZ - nearZ), T(1))
#endif
#elif defined(GEOMETRY_LEFT_HANDED)
#if defined(GEOMETRY_CLIP_SPACE_POSITIVE)
		col4<T>(T(0), T(0), T(1) / (farZ - nearZ), T(0)),
		col4<T>(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -nearZ / (farZ - nearZ), T(1))
#elif defined(GEOMETRY_CLIP_SPACE_NEGATIVE)
		col4<T>(T(0), T(0), T(2) / (farZ - nearZ), T(0)),
		col4<T>(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(farZ + nearZ) / (farZ - nearZ), T(1))
#endif
#endif
	);
}

template<typename T>
inline mat4<T> mat4<T>::lookAtView(const point3<T> & eye, const point3<T> & target, const norm3<T> & up)
{
	vec3<T> forward(vec3<T>::normalize(vec3<T>(target - eye)));
#if defined(GEOMETRY_RIGHT_HANDED)
	vec3<T> right(vec3<T>::normalize(vec3<T>::cross(forward, vec3<T>(up))));
	vec3<T> upCoordinate(vec3<T>::normalize(vec3<T>::cross(right, forward)));
#else
	vec3<T> right(vec3<T>::normalize(vec3<T>::cross(vec3<T>(up), forward)));
	vec3<T> upCoordinate(vec3<T>::normalize(vec3<T>::cross(forward, right)));
#endif
	return mat4<T>(
#if defined(GEOMETRY_RIGHT_HANDED)
		col4<T>(right.x, upCoordinate.x, -forward.x, T(0)),
		col4<T>(right.y, upCoordinate.y, -forward.y, T(0)),
		col4<T>(right.z, upCoordinate.z, -forward.z, T(0)),
#else
		col4<T>(right.x, upCoordinate.x, forward.x, T(0)),
		col4<T>(right.y, upCoordinate.y, forward.y, T(0)),
		col4<T>(right.z, upCoordinate.z, forward.z, T(0)),
#endif
		col4<T>(
			-vec3<T>::dot(right, vec3<T>(eye)),
			-vec3<T>::dot(upCoordinate, vec3<T>(eye)),
#if defined(GEOMETRY_LEFT_HANDED)
			-vec3<T>::dot(forward, vec3<T>(eye)),
#else
			vec3<T>::dot(forward, vec3<T>(eye)),
#endif
			T(1)
		)
	);
}

template<typename T>
inline mat4<T> mat4<T>::lookAt(const point3<T>& eye, const point3<T>& target, const norm3<T>& up)
{
	vec3<T> forward(vec3<T>::normalize(vec3<T>(target - eye)));
#if defined(GEOMETRY_RIGHT_HANDED)
	vec3<T> right(vec3<T>::normalize(vec3<T>::cross(forward, vec3<T>(up))));
	vec3<T> upCoordinate(vec3<T>::normalize(vec3<T>::cross(right, forward)));
#else
	vec3<T> right(vec3<T>::normalize(vec3<T>::cross(vec3<T>(up), forward)));
	vec3<T> upCoordinate(vec3<T>::normalize(vec3<T>::cross(forward, right)));
#endif
	return mat4<T>(
		col4<T>(right, T(0)),
		col4<T>(upCoordinate, T(0)),
#if defined(GEOMETRY_RIGHT_HANDED)
		col4<T>(-forward, T(0)),
#elif defined(GEOMETRY_LEFT_HANDED)
		col4<T>(forward, T(0)),
#endif
		col4<T>(eye, T(1))
	);
}

template<typename T>
inline mat4<T> mat4<T>::from2D(const mat3<T>& mat)
{
	return mat4<T>(
		col4<T>(mat[0][0], mat[0][1], T(0), mat[0][2]),
		col4<T>(mat[1][0], mat[1][1], T(0), mat[1][2]),
		col4<T>(T(0), T(0), T(1), T(0)),
		col4<T>(mat[2][0], mat[2][1], T(0), mat[2][2])
	);
}

template<typename T>
inline vec3<T> mat4<T>::extractScale(const mat4<T>& matrix)
{
	return vec3<T>(
		vec3<T>(matrix[0]).norm(),
		vec3<T>(matrix[1]).norm(),
		vec3<T>(matrix[2]).norm()
	);
}

template<typename T>
inline vec3<T> mat4<T>::extractTranslation(const mat4<T>& matrix)
{
	return vec3<T>(matrix[3]);
}

template<typename T>
inline quat<T> mat4<T>::extractRotation(const mat4<T>& matrix)
{
	// Does not take shear & projection into account, 
	// but as this lib do not let us change that, it does not matter
	vec3<T> scale = extractScale(matrix);
	mat3<T> rotation(
		vec3<T>(matrix[0]) / scale.x,
		vec3<T>(matrix[1]) / scale.y,
		vec3<T>(matrix[2]) / scale.z
	);
	return quat<T>(rotation);
}

template <typename T>
inline T mat4<T>::det() const
{
	return
		cols[0][3] * cols[1][2] * cols[2][1] * cols[3][0] - cols[0][2] * cols[1][3] * cols[2][1] * cols[3][0] -
		cols[0][3] * cols[1][1] * cols[2][2] * cols[3][0] + cols[0][1] * cols[1][3] * cols[2][2] * cols[3][0] +
		cols[0][2] * cols[1][1] * cols[2][3] * cols[3][0] - cols[0][1] * cols[1][2] * cols[2][3] * cols[3][0] -
		cols[0][3] * cols[1][2] * cols[2][0] * cols[3][1] + cols[0][2] * cols[1][3] * cols[2][0] * cols[3][1] +
		cols[0][3] * cols[1][0] * cols[2][2] * cols[3][1] - cols[0][0] * cols[1][3] * cols[2][2] * cols[3][1] -
		cols[0][2] * cols[1][0] * cols[2][3] * cols[3][1] + cols[0][0] * cols[1][2] * cols[2][3] * cols[3][1] +
		cols[0][3] * cols[1][1] * cols[2][0] * cols[3][2] - cols[0][1] * cols[1][3] * cols[2][0] * cols[3][2] -
		cols[0][3] * cols[1][0] * cols[2][1] * cols[3][2] + cols[0][0] * cols[1][3] * cols[2][1] * cols[3][2] +
		cols[0][1] * cols[1][0] * cols[2][3] * cols[3][2] - cols[0][0] * cols[1][1] * cols[2][3] * cols[3][2] -
		cols[0][2] * cols[1][1] * cols[2][0] * cols[3][3] + cols[0][1] * cols[1][2] * cols[2][0] * cols[3][3] +
		cols[0][2] * cols[1][0] * cols[2][1] * cols[3][3] - cols[0][0] * cols[1][2] * cols[2][1] * cols[3][3] -
		cols[0][1] * cols[1][0] * cols[2][2] * cols[3][3] + cols[0][0] * cols[1][1] * cols[2][2] * cols[3][3];
}

template <typename T>
inline point3<T> mat4<T>::multiplyPoint3x4(const point3<T>& point) const
{
	// Assume w component is 1.
	return point3<T>(
		cols[0].x * point.x + cols[1].x * point.y + cols[2].x * point.z + cols[3].x,
		cols[0].y * point.x + cols[1].y * point.y + cols[2].y * point.z + cols[3].y,
		cols[0].z * point.x + cols[1].z * point.y + cols[2].z * point.z + cols[3].z
	);
}

template <typename T>
inline point3<T> mat4<T>::multiplyPoint(const point3<T>& point) const
{
	T w = cols[0].w * point.x + cols[1].w * point.y + cols[2].w * point.z + cols[3].w;
	return point3<T>(
		(cols[0].x * point.x + cols[1].x * point.y + cols[2].x * point.z + cols[3].x) / w,
		(cols[0].y * point.x + cols[1].y * point.y + cols[2].y * point.z + cols[3].y) / w,
		(cols[0].z * point.x + cols[1].z * point.y + cols[2].z * point.z + cols[3].z) / w
	);
}

template <typename T>
inline vec3<T> mat4<T>::multiplyVector(const vec3<T>& point) const
{
	return vec3<T>(
		cols[0].x * point.x + cols[1].x * point.y + cols[2].x * point.z,
		cols[0].y * point.x + cols[1].y * point.y + cols[2].y * point.z,
		cols[0].z * point.x + cols[1].z * point.y + cols[2].z * point.z
	);
}

}
