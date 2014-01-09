#include <small_header.h>
#include "Game/Level/Make/Parameters/StyleData/BigData.h"

#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"


namespace CloudberryKingdom
{

	BigData::BigData( const boost::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
	}

	void BigData::Randomize()
	{
		StyleData::Randomize();
	}

}
