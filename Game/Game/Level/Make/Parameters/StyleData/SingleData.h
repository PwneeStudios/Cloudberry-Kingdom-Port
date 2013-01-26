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
	
		virtual ~SingleData() { }

		Vector2 InitialDoorYRange;

		SingleData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SINGLEDATA
