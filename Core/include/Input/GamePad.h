#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

#include <Input/GamePadState.h>

struct GamePad
{

	static void Initialize();
	static void Update();
	static void Shutdown();

	static GamePadState GetState( PlayerIndex index );
	static void SetVibration( PlayerIndex index, float left, float right );

};

#endif
