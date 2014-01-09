#include <small_header.h>
#include "Game/Objects/In Game Objects/BaseClasses/_Death.h"

#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Obstacle.h"


namespace CloudberryKingdom
{

	void _Death::InitializeInstanceFields()
	{
		DeathType = BobDeathType_NONE;
	}

}
