#include "SingleData.h"
#include "Core/Tools/Random.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	SingleData::SingleData( const std::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
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
