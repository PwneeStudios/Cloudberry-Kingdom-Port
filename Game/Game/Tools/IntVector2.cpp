#include "IntVector2.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	IntVector2::IntVector2( int X, int Y )
	{
		this->X = X;
		this->Y = Y;
	}

	IntVector2::IntVector2( float X, float Y )
	{
		this->X = static_cast<int>( X );
		this->Y = static_cast<int>( Y );
	}

	IntVector2::IntVector2( Vector2 v )
	{
		X = static_cast<int>( v.X );
		Y = static_cast<int>( v.Y );
	}

	IntVector2 IntVector2::operator + ( IntVector2 B )
	{
		return IntVector2( this->X + B.X, this->Y + B.Y );
	}

	IntVector2 IntVector2::operator *( IntVector2 B )
	{
		return IntVector2( this->X * B.X, this->Y * B.Y );
	}

	IntVector2 IntVector2::operator *( Vector2 B )
	{
		return IntVector2( this->X * B.X, this->Y * B.Y );
	}

	IntVector2 IntVector2::operator *( float a )
	{
		return IntVector2( this->X * a, this->Y * a );
	}

	IntVector2::operator Vector2()
	{
		return Vector2( this->X, this->Y );
	}
}
