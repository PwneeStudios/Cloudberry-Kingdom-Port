#ifndef _DEATH
#define _DEATH

#include <small_header.h>

//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Obstacle.h"




namespace CloudberryKingdom
{

	struct _Death : public _Obstacle
	{
	
		BobDeathType DeathType;

	
		void InitializeInstanceFields();


		_Death()
		{
			InitializeInstanceFields();
		}

	};
}


#endif	//#ifndef _DEATH
