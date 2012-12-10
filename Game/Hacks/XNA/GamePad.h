#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

class GamePad
{

public:

	static GamePadState GetState( PlayerIndex index )
	{
		return GamePadState();
	}

	static void SetVibration( PlayerIndex index, float left, float right )
	{
	}

};

#endif
