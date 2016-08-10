#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include "KeyboardState.h"

class Keyboard
{

	static KeyboardState currentState_;

public:

	static void Update();

	static KeyboardState GetState();

};

#endif
