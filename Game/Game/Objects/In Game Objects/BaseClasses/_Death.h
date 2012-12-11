#ifndef _DEATH
#define _DEATH

#include <global_header.h>



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
