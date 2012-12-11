#ifndef ONESCREENDATA
#define ONESCREENDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct OneScreenData : public StyleData
	{
	
		Vector2 CamShift;

		OneScreenData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	
		void InitializeInstanceFields();
	};
}

#endif	//#ifndef ONESCREENDATA
