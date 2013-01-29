#ifndef INTVECTOR2
#define INTVECTOR2

namespace CloudberryKingdom
{

	struct IntVector2
	{
	
		int X, Y;

		IntVector2()
		{
			X = Y = 0;
		}

		IntVector2( int X, int Y );
		IntVector2( float X, float Y );
		IntVector2( Vector2 v );

		IntVector2 operator + ( IntVector2 B );
		IntVector2 operator *( IntVector2 B );
		IntVector2 operator *( Vector2 B );

		IntVector2 operator *( float a );

		operator Vector2();
	};

}


#endif	//#ifndef INTVECTOR2
