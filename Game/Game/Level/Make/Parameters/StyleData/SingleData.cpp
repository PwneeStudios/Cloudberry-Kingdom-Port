#include <global_header.h>



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
