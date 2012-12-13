#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include "GamePadState.h"

struct GamePad
{

	static GamePadState GetState( PlayerIndex index );
	static void SetVibration( PlayerIndex index, float left, float right );

};

#endif
