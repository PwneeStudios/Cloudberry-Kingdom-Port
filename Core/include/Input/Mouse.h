#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "MouseState.h"

class Mouse
{

public:

	static void SetPosition( int x, int y );

	static MouseState GetState();

};

#endif
