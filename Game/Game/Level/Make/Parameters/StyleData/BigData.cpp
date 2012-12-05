#include <global_header.h>

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
