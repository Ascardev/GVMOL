#ifndef _POINT3_H
#define _POINT3_H

#include <math.h>
#include "mathGlobal.h"

struct point4;

struct point3
{
	union
	{
		struct
		{
			float x, y, z;
		};
		float	v[3];
	};

	point3()
	{
	}

	point3(float X, float Y, float Z) :
		x(X), y(Y), z(Z)
	{
	}

	point3(const point4& in);

	static const point3 Spherical(float theta, float rho, float phi)
	{
		return point3(
			(float)(phi * cos(rho) * sin(theta)),
			(float)(phi * sin(rho)),
			(float)(phi * cos(rho) * cos(theta))
		);
	}

	void Assign(float X, float Y, float Z);

	float Mag() const;

	float MagSquared() const;

	void Normalize();

	const point3 Normalized() const;

	static float Dist(const point3& a, const point3& b)
	{
		point3 distVec(b.x - a.x, b.y - a.y, b.z - a.z);
		return distVec.Mag();
	}

	point3& operator += (const point3& in);
	point3& operator -= (const point3& in);
	point3& operator *= (const float& in);
	point3& operator /= (const float& in);
	point3  operator -  ();

	static const point3 Zero;
	static const point3 i;
	static const point3 j;
	static const point3 k;
};

inline point3& point3::operator += (const point3& in)
{
	x += in.x;
	y += in.y;
	z += in.z;
	return *this;
}

inline point3& point3::operator -= (const point3& in)
{
	x -= in.x;
	y -= in.y;
	z -= in.z;
	return *this;
}

inline point3& point3::operator *= (const float& in)
{
	x *= in;
	y *= in;
	z *= in;
	return *this;
}

inline point3& point3::operator /= (const float& in)
{
	float inv = 1.f / in;
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}

inline point3 point3::operator - ()
{
	return point3(
		-x,
		-y,
		-z
	);
}

inline const point3 operator+(point3 const& a, point3 const& b)
{
	return point3
	(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
};

inline const point3 operator-(point3 const& a, point3 const& b)
{
	return point3
	(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
};

inline const point3 operator*(point3 const& a, float const& b)
{
	return point3
	(
		a.x * b,
		a.y * b,
		a.z * b
	);
};

inline const point3 operator*(float  const& a, point3 const& b)
{
	return point3
	(
		a * b.x,
		a * b.y,
		a * b.z
	);
};

inline const point3 operator/(point3 const& a, float const& b)
{
	float inv = 1.f / b;
	return point3
	(
		a.x * inv,
		a.y * inv,
		a.z * inv
	);
};

inline const point3 operator^(point3 const& a, point3 const& b)
{
	return point3
	(
		(a.y * b.z - a.z * b.y),
		(a.z * b.x - a.x * b.z),
		(a.x * b.y - a.y * b.x)
	);
}

inline const float operator*(point3 const& a, point3 const& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline bool   operator==(point3 const& a, point3 const& b)
{
	if (fabs(a.x - b.x) < EPSILON)
	{
		if (fabs(a.y - b.y) < EPSILON)
		{
			if (fabs(a.z - b.z) < EPSILON)
			{
				return true;
			}
		}
	}
	return false;
};

inline void point3::Assign(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

inline float point3::Mag() const
{
	return (float)sqrt((*this) * (*this));
}

inline float point3::MagSquared() const
{
	return ((*this) * (*this));
}

inline void point3::Normalize()
{
	float invMag = 1.f / Mag();

	(*this) *= invMag;
}

inline const point3 point3::Normalized() const
{
	float length = Mag();
	if (length == 0.f)
		length = 1.f;
	float invMag = 1.f / length;
	return (*this) * invMag;
}

#endif
