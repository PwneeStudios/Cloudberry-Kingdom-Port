#include "UpData.h"
#include "Core/Tools/Random.h"

namespace CloudberryKingdom
{

	VerticalData::VerticalData( const std::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
	}

	void UpData::CalculateKeepUnused( float JumpLevel )
	{
		// Extra fill: keep unused
		//if (Rnd.RndFloat(0, 1) < ChanceToHaveUnused)
	{
			float MaxChance = .075f;
			float chance = MaxChance - .1f * ( MaxChance - 0 ) * JumpLevel;
			ChanceToKeepUnused = Rnd->RndFloat( 0, chance );
		}
	}

	UpData::UpData( const std::shared_ptr<Rand> &Rnd ) : VerticalData( Rnd )
	{
		VisualStyle = VisualStyles_CASTLE;
		BlockFillType = _BlockFillType_TOP_ONLY;
	}

	void UpData::Randomize()
	{
		VerticalData::Randomize();
	}
}
