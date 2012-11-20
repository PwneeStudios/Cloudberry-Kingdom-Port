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

#endif
