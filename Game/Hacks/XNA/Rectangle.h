#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

struct Rectangle
{



	int X, Y, Width, Height;

	Rectangle() : X( 0 ), Y( 0 ), Width( 0 ), Height( 0 ) { }
	Rectangle( int X, int Y, int Width, int Height ) :
		X( X ), Y( Y ), Width( Width ), Height( Height )
	{
	}

};

#endif
