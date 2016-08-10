#ifndef _GAMEPADDPAD_H_
#define _GAMEPADDPAD_H_

#include "InputEnums.h"

struct GamePadDPad
{

	ButtonState Down;
	ButtonState Left;
	ButtonState Right;
	ButtonState Up;

	GamePadDPad() :
		Down( ButtonState_Released ),
		Left( ButtonState_Released ),
		Right( ButtonState_Released ),
		Up( ButtonState_Released )
	{
	}

};

#endif
