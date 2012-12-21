#ifndef LEVELSEEDDATA
#define LEVELSEEDDATA

#include <Utility/Mutex.h>

namespace CloudberryKingdom
{

	struct LockableBool
	{
	
		Mutex MyMutex;

	
		bool _val;
	
		const bool &getval() const;
		void setval( const bool &value );

	
		void InitializeInstanceFields();

	
		LockableBool()
		{
			InitializeInstanceFields();
		}

	};

}

#endif	//#ifndef LEVELSEEDDATA
