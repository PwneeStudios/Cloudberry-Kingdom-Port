#ifndef _MOUSESTATE_H_
#define _MOUSESTATE_H_

#include "InputEnums.h"

class MouseState
{

public:

	int X;
	int Y;
	int ScrollWheelValue;

	ButtonState LeftButton;
	ButtonState RightButton;

	MouseState() :
		X( 0 ),
		Y( 0 ),
		ScrollWheelValue( 0 ),
		LeftButton( ButtonState_Released ),
		RightButton( ButtonState_Released )
	{
	}

};

#endif
