#ifndef _VECTORS_H_
#define _VECTORS_H_

#include <cmath>

/**
 * 2-vector.
 */
class Vector2
{

	float x_;
	float y_;

public:

	Vector2() : x_( 0 ), y_( 0 ) { }
	Vector2( const Vector2 &other ) : x_( other.x_ ), y_( other.y_ ) { }
	Vector2( float x, float y ) : x_( x ), y_( y ) { }
	Vector2( float x ) : x_( x ), y_( x ) { }

	float x() const { return x_; }
	float y() const { return y_; }

	float LengthSq() const { return x_ * x_ + y_ * y_; }
	
	float Length() const { return sqrtf( LengthSq() ); }
	
	void Normalize()
	{
		float length = Length();
		x_ /= length;
		y_ /= length;
	}

	Vector2 Normalized() const
	{
		float length;
		return Vector2( x_ / length, y_ / length );
	}

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
