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
	Color( unsigned char r, unsigned char g, unsigned char b ) :
		R( r ), G( g ), B( b ), A( 255 ) { }
	Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) :
		R( r ), G( g ), B( b ), A( a ) { }
	explicit Color( const Vector4 &c ) :
		R( static_cast< unsigned char >( c.X * 255.f ) ),
		G( static_cast< unsigned char >( c.Y * 255.f ) ),
		B( static_cast< unsigned char >( c.Z * 255.f ) ),
		A( static_cast< unsigned char >( c.W * 255.f ) ) { }
	explicit Color( const Vector3 &c ) :
		R( static_cast< unsigned char >( c.X * 255.f ) ),
		G( static_cast< unsigned char >( c.Y * 255.f ) ),
		B( static_cast< unsigned char >( c.Z * 255.f ) ),
		A( 255 ) { }
	Color( float r, float g, float b ) :
		R( static_cast< unsigned char >( r * 255.f ) ),
		G( static_cast< unsigned char >( g * 255.f ) ),
		B( static_cast< unsigned char >( b * 255.f ) ),
		A( 255 ) { }
	Color( float r, float g, float b, float a ) :
		R( static_cast< unsigned char >( r * 255.f ) ),
		G( static_cast< unsigned char >( g * 255.f ) ),
		B( static_cast< unsigned char >( b * 255.f ) ),
		A( static_cast< unsigned char >( a * 255.f ) ) { }

	Vector4 ToVector4() const
	{
		return Vector4( R / 255.f, G / 255.f, B / 255.f, A / 255.f );
	}

	Vector3 ToVector3() const
	{
		return Vector3( R / 255.f, G / 255.f, B / 255.f );
	}

	Color operator * ( float s ) const
	{
		Vector4 c = ToVector4();
		return Color( c * s );
	}

	bool operator == ( const Color &c ) const
	{
		return R == c.R && G == c.G && B == c.B && A == c.A;
	}
	
	bool operator != ( const Color &c ) const
	{
		return !( *this == c );
	}


	static Color Azure;
	static Color Black;
	static Color Blue;
	static Color BlueViolet;
	static Color Brown;
	static Color Cyan;
	static Color DarkBlue;
	static Color ForestGreen;
	static Color Fuchsia;
	static Color Gainsboro;
	static Color Gold;
	static Color Gray;
	static Color Green;
	static Color HotPink;
	static Color Indigo;
	static Color LightSeaGreen;
	static Color LimeGreen;
	static Color PowderBlue;
	static Color Purple;
	static Color Red;
	static Color Silver;
	static Color SkyBlue;
	static Color Transparent;
	static Color White;
	static Color WhiteSmoke;
	static Color Yellow;
};

Color bColor( unsigned char R, unsigned char G, unsigned char B )
{
	return Color(R, G, B, 255);
}

Color bColor( unsigned char R, unsigned char G, unsigned char B, unsigned char A )
{
	return Color(R, G, B, A);
}


#endif
