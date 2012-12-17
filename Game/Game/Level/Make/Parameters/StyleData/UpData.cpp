#include <global_header.h>

namespace CloudberryKingdom
{

	VerticalData::VerticalData( const boost::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
		VisualStyle = static_cast<VisualStyles>( 0 );
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

	UpData::UpData( const boost::shared_ptr<Rand> &Rnd ) : VerticalData( Rnd )
	{
		VisualStyle = VisualStyles_CASTLE;
		BlockFillType = _BlockFillType_TOP_ONLY;
	}

	void UpData::Randomize()
	{
		VerticalData::Randomize();
	}
}
