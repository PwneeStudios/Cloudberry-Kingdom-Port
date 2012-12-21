#ifndef _GAMEPADBUTTONS_H_
#define _GAMEPADBUTTONS_H_

#include "InputEnums.h"

struct GamePadButtons
{

	ButtonState A;
	ButtonState B;
	ButtonState Back;
	ButtonState BigButton;
	ButtonState LeftShoulder;
	ButtonState LeftStick;
	ButtonState RightShoulder;
	ButtonState RightStick;
	ButtonState Start;
	ButtonState X;
	ButtonState Y;

	GamePadButtons() :
		A( ButtonState_Released ),
		B( ButtonState_Released ),
		Back( ButtonState_Released ),
		BigButton( ButtonState_Released ),
		LeftShoulder( ButtonState_Released ),
		LeftStick( ButtonState_Released ),
		RightShoulder( ButtonState_Released ),
		RightStick( ButtonState_Released ),
		Start( ButtonState_Released ),
		X( ButtonState_Released ),
		Y( ButtonState_Released )
	{
	}

};

#endif
