#ifndef _SIGNEDINGAMER_H_
#define _SIGNEDINGAMER_H_

#include <enums.h>

// FIXME: SignedInGamer and SignedInEventArgs uses the Xbox XNA gamer concept.
struct SignedInGamer
{

	PlayerIndex MyPlayerIndex;

	SignedInGamer() :
		MyPlayerIndex( PlayerIndex_One )
	{
	}

};

#endif
