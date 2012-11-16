#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	OneScreenData::OneScreenData( const std::shared_ptr<Rand> &Rnd ) : StyleData( Rnd )
	{
		InitializeInstanceFields();
	}

	void OneScreenData::Randomize()
	{
		StyleData::Randomize();
	}

	void OneScreenData::InitializeInstanceFields()
	{
		CamShift = Vector2::Zero;
	}
}
