#ifndef BIGDATA
#define BIGDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Rand;
}


namespace CloudberryKingdom
{
	struct BigData : public StyleData
	{
	
		virtual ~BigData() { }

		BigData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef BIGDATA
