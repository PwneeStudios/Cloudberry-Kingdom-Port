#include <small_header.h>
#include "Game/Level/Make/Parameters/StyleData/OneScreenData.h"

#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"


namespace CloudberryKingdom
{

	OneScreenData::OneScreenData( const boost::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
		InitializeInstanceFields();
	}

	void OneScreenData::Randomize()
	{
		StyleData::Randomize();
	}

	void OneScreenData::InitializeInstanceFields()
	{
		CamShift = Vector2();
	}

}
