#ifndef _VECTORS_H_
#define _VECTORS_H_

#include <cmath>

/**
 * 2-vector.
 */
class Vector2
{

public:

	float X;
	float Y;

	Vector2() : X( 0 ), Y( 0 ) { }
	Vector2( const Vector2 &other ) : X( other.X ), Y( other.Y ) { }
	Vector2( float x, float y ) : X( x ), Y( y ) { }
	Vector2( float x ) : X( x ), Y( x ) { }

	float x() const { return X; }
	float y() const { return Y; }

	float LengthSq() const { return X * X + Y * Y; }
	
	float Length() const { return sqrtf( LengthSq() ); }
	
	void Normalize()
	{
		float length = Length();
		X /= length;
		Y /= length;
	}

	Vector2 Normalized() const
	{
		float length;
		return Vector2( X / length, Y / length );
	}

	Vector2 &operator += ( const Vector2 &a )
	{
		X += a.x();
		Y += a.y();
		return *this;
	}

	Vector2 operator + ( const Vector2 &a ) const
	{
		return Vector2( X + a.X, Y + a.Y );
	}

	Vector2 operator * ( float k ) const
	{
		return Vector2( X * k, Y * k );
	}

	static Vector2 Lerp( const Vector2 &a, const Vector2 &b, float t )
	{
		return a * ( 1 - t ) + b * t;
	}

};

class Vector3
{

	float X;
	float Y;
	float Z;

	Vector3() : X(0), Y(0), Z(0) { }
	Vector3( const Vector3 &other ) : X( other.X ), Y( other.Y ), Z( other.Z ) { }
	Vector3( float x, float y, float z ) : X(x), Y(y), Z(z) { }
	Vector3( float x ) : X(x), Y(x), Z(x) { }
};

class Vector4
{

	float x_;
	float y_;
	float z_;
	float w_;

public:

	Vector4() : x_( 0 ), y_( 0 ), z_( 0 ), w_( 0 ) { }
	Vector4( const Vector4 &other) : x_( other.x_ ), y_( other.y_ ),
		z_( other.z_ ), w_( other.w_ ) { }
	Vector4( float x ) : x_( x ), y_( x ), z_( x ), w_( x ) { }
	Vector4( float x, float y, float z, float w ) :
		x_( x ), y_( y ), z_( z ), w_( w ) { }

	float x() const { return x_; }
	float y() const { return y_; }
	float z() const { return z_; }
	float w() const { return w_; }

	float r() const { return x_; }
	float g() const { return y_; }
	float b() const { return z_; }
	float a() const { return w_; }

};

class Matrix
{
	float M11, M12, M13, M14;
	float M21, M22, M23, M24;
	float M31, M32, M33, M34;
	float M41, M42, M43, M44;
};

#endif
