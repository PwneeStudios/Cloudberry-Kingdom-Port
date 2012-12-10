#ifndef _GAMEPADSTATE_H_
#define _GAMEPADSTATE_H_

#include "Hacks/XNA/GamePadButtons.h"
#include "Hacks/XNA/GamePadTriggers.h"
#include "Hacks/XNA/GamePadDPad.h"
#include "Hacks/XNA/GamePadThumbSticks.h"

class GamePadState
{
	
public:

	bool IsConnected;

	GamePadButtons Buttons;
	GamePadTriggers Triggers;
	GamePadDPad DPad;
	GamePadThumbSticks ThumbSticks;
};

#endif
