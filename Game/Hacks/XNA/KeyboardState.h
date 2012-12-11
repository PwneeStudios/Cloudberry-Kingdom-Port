#ifndef _KEYBOARDSTATE_H_
#define _KEYBOARDSTATE_H_

struct KeyboardState
{
	


	bool IsKeyDown( Keys key )
	{
		return false;
	}

	std::vector<Keys> GetPressedKeys()
	{
		return std::vector<Keys>();
	}

};

#endif
