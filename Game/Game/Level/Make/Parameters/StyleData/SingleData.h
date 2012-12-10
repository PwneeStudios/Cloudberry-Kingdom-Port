#ifndef SINGLEDATA
#define SINGLEDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Rand;
}




namespace CloudberryKingdom
{
	struct SingleData : public StyleData
	{
	
		Vector2 InitialDoorYRange;

		SingleData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SINGLEDATA
