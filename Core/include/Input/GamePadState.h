#ifndef _GAMEPADSTATE_H_
#define _GAMEPADSTATE_H_

#include "GamePadButtons.h"
#include "GamePadTriggers.h"
#include "GamePadDPad.h"
#include "GamePadThumbSticks.h"

struct GamePadState
{
	bool IsConnected;

	GamePadButtons Buttons;
	GamePadTriggers Triggers;
	GamePadDPad DPad;
	GamePadThumbSticks ThumbSticks;

	GamePadState() : IsConnected( false ) { }
};

#endif
