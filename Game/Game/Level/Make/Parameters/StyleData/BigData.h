#ifndef BIGDATA
#define BIGDATA

#include "StyleData.h"

namespace CloudberryKingdom
{
	class Rand;
}


namespace CloudberryKingdom
{
	class BigData : public StyleData
	{
	public:
		BigData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef BIGDATA
