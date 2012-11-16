#include "BigData.h"
#include "Core/Tools/Random.h"

namespace CloudberryKingdom
{

	BigData::BigData( const std::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
	}

	void BigData::Randomize()
	{
		StyleData::Randomize();
	}
}
