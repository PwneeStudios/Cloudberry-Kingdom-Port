#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "MouseState.h"

struct Mouse
{

	static void SetPosition( int x, int y );

	static MouseState GetState();

};

#endif
