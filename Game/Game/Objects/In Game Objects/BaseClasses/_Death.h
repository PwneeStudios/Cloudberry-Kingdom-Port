#ifndef _DEATH
#define _DEATH

#include <global_header.h>








namespace CloudberryKingdom
{
	class _Death : public _Obstacle
	{
	protected:
		Bob::BobDeathType DeathType;

	private:
		void InitializeInstanceFields();

public:
		_Death()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef _DEATH
