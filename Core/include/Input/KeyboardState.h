#ifndef _KEYBOARDSTATE_H_
#define _KEYBOARDSTATE_H_

#include "InputEnums.h"

#include <vector>
#include <string.h>

class KeyboardState
{
	
	bool keyState_[ 256 ];

	friend class Keyboard;

public:

	KeyboardState()
	{
		memset( keyState_, 0, sizeof( keyState_ ) );
	}

	bool IsKeyDown( Keys key )
	{
		return keyState_[ key ];
	}

	std::vector<Keys> GetPressedKeys()
	{
		std::vector<Keys> keyVec;

		for( size_t i = 0; i < 256; ++i )
		{
			if( keyState_[ i ] )
				keyVec.push_back( static_cast< Keys >( i ) );
		}

		return keyVec;
	}

};

#endif
