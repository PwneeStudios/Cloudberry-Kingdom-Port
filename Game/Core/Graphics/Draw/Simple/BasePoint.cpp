#include <small_header.h>
#include "Core/Graphics/Draw/Simple/BasePoint.h"



namespace CloudberryKingdom
{
	BasePoint::BasePoint()
	{
	}

	BasePoint::BasePoint( float e1x, float e1y, float e2x, float e2y, float ox, float oy )
	{
		e1 = Vector2( e1x, e1y );
		e2 = Vector2( e2x, e2y );
		Origin = Vector2( ox, oy );
	}

	void BasePoint::Init()
	{
		Origin = Vector2();
		e1 = Vector2( 1, 0 );
		e2 = Vector2( 0, 1 );
	}

	Vector2 BasePoint::GetScale()
	{
		return Vector2( e1.X, e2.Y );
	}

	void BasePoint::SetScale( Vector2 scale )
	{
		e1.X = scale.X;
		e2.Y = scale.Y;
	}
}
