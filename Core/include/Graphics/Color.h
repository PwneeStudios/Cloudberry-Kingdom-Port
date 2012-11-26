/**
 * @file
 *
 * Color related functionality.
 */
#ifndef _COLOR_H_
#define _COLOR_H_

#include <Math/Vectors.h>

struct Color
{
	union
	{
		struct 
		{
			unsigned char R;
			unsigned char G;
			unsigned char B;
			unsigned char A;
		};

		unsigned int PackedValue;
	};

	Color() : R( 0 ), G( 0 ), B( 0 ), A( 0 )  { }
	Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) :
		R( r ), G( g ), B( b ), A( a ) { }
	Color( const Vector4 &c ) : R( static_cast< unsigned char >( c.X * 255.f ) ),
		G( static_cast< unsigned char >( c.Y * 255.f ) ),
		B( static_cast< unsigned char >( c.Z * 255.f ) ),
		A( static_cast< unsigned char >( c.W * 255.f ) ) { }

	Vector4 ToVector4() const
	{
		return Vector4( R / 255.f, G / 255.f, B / 255.f, A / 255.f );
	}

	static Color White;
};

#endif
