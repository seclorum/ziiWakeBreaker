#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "Math.h"

//basic 3d vector3 class
class Vector3
{
public:
	union
	{
		struct
		{
			int32 x,y,z;
		};
		int32 v[3];
	};

	Vector3(){}
	Vector3(int32 X,int32 Y,int32 Z) : x(X), y(Y), z(Z)
	{}
	~Vector3(){}

	Vector3& operator =  ( const Vector3& in );
	Vector3& operator += ( const Vector3& in );
	Vector3& operator -= ( const Vector3& in );
	Vector3& operator *= ( const Vector3& in );
	Vector3& operator *= ( const int32& in );
	Vector3& operator += ( const int32& in );
	Vector3& operator /= ( const Vector3& in );
	Vector3& operator /= ( const int32& in );

	void Set(const int32& X,const int32& Y, const int32& Z)
	{
		x = X; y = Y; z = Z;
	}

	
};



//--------------------------------------------------------
inline Vector3& Vector3::operator+=(const Vector3& in)
{
	x += in.x;
	y += in.y;
	z += in.z;
	
	return *this;
}
//--------------------------------------------------------
inline Vector3& Vector3::operator -=(const Vector3& in)
{
	x -= in.x;
	y -= in.y;
	z -= in.z;

	return *this;
}
//---------------------------------------------------------------
inline Vector3& Vector3::operator =(const Vector3& in)
{
	x = in.x;
	y = in.y;
	z = in.z;
	return *this;
}
//---------------------------------------------------------------
inline Vector3& Vector3::operator*=(const Vector3& in)
{
	x = MULX(x,in.x);
	y = MULX(y,in.y);
	z = MULX(z,in.z);
	return *this;
}
//---------------------------------------------------------------
inline Vector3& Vector3::operator*=(const int32& in)
{
	x = MULX(x,in );
	y = MULX(y,in );
	z = MULX(z,in );
	return *this;
}
//------------------------------------------------
inline Vector3& Vector3::operator+=(const int32& in)
{
	x += in;
	y += in;
	z += in;
	return *this;
}
//------------------------------------------------------
inline Vector3& Vector3::operator/=( const Vector3& in )
{
	x = DIVX(x,in.x);
	y = DIVX(y,in.y);
	z = DIVX(z,in.z);
	return *this;
}
//-------------------------------------------------------
inline Vector3& Vector3::operator/=( const int32& in )
{
	x = DIVX(x,in);
	y = DIVX(y,in);
	z = DIVX(z,in);
	return *this;
}

inline const Vector3 operator-(const Vector3 &a,const Vector3 &b)
{
	return Vector3
	(
		(a.x - b.x),
		(a.y - b.y),
		(a.z - b.z)
	);
}

inline const Vector3 operator*(const Vector3 &a,const Vector3 &b)
{
	return Vector3
	(
		(MULX(a.x,b.x)),
		(MULX(a.y,b.y)),
		(MULX(a.z,b.z))
	);
}
//Cross product
inline const Vector3 operator^(Vector3 const &a, Vector3 const &b)
{
	return Vector3
	(
		(MULX(a.y,b.z) - MULX(a.z,b.y)),
		(MULX(a.z,b.x) - MULX(a.x,b.z)),
		(MULX(a.x,b.y) - MULX(a.y,b.x))
	);
}
#endif
