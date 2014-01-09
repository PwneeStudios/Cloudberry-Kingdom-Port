#include <small_header.h>
#include "Game/Level/Make/Parameters/StyleData/SingleData.h"

#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"


namespace CloudberryKingdom
{

	SingleData::SingleData( const boost::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
		InitializeInstanceFields();
	}

	void SingleData::Randomize()
	{
		StyleData::Randomize();
	}

	void SingleData::InitializeInstanceFields()
	{
		InitialDoorYRange = Vector2( -600, 200 );
	}

}
