#ifndef _VIEWPORT_H_
#define _VIEWPORT_H_

struct Viewport
{

	float X; float Y; float Width; float Height; float MinDepth; float MaxDepth;

	Viewport()
	{
		X = Y = Width = Height = MinDepth = MaxDepth = 0;
	}

	Viewport( float _X, float _Y, float _Width, float _Height, float _MinDepth, float _MaxDepth ) :
		X ( _X ), Y ( _Y ), Width ( _Width ), Height ( _Height ), MinDepth ( _MinDepth ), MaxDepth ( _MaxDepth )
	{
	}

};

#endif
