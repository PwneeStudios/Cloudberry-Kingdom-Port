#include "Param.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Core/Tools/Random.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	VectorParam::VectorParam( const std::shared_ptr<PieceSeedData> &PieceSeed )
	{
		X = Param( PieceSeed );
		Y = Param( PieceSeed );
	}

	VectorParam::VectorParam( const std::shared_ptr<PieceSeedData> &PieceSeed, Vector2 v )
	{
		X = Param( PieceSeed );
		Y = Param( PieceSeed );

		if ( v != 0 )
			SetVal( v );
	}

	void VectorParam::SetVal( Vector2 v )
	{
		X.SetVal( v.X );
		Y.SetVal( v.Y );
	}

	Microsoft::Xna::Framework::Vector2 VectorParam::GetVal()
	{
		return Vector2( X.GetVal(), Y.GetVal() );
	}

	Microsoft::Xna::Framework::Vector2 VectorParam::GetVal( Vector2 Pos )
	{
		return Vector2( X.GetVal( Pos ), Y.GetVal( Pos ) );
	}

	float VectorParam::RndFloat( Vector2 Pos, const std::shared_ptr<Rand> &Rnd )
	{
		return Rnd->RndFloat( GetVal( Pos ) );
	}

	const float &Param::getVal() const
	{
		return val1;
	}

	void Param::setVal( const float &value )
	{
		val1 = value;
		val2_IsSet = false;
	}

	Param::Param( float val )
	{
		PieceSeed.reset();

		val1 = val2 = val;
		val1_IsSet = val2_IsSet = true;
	}

	Param::Param( const std::shared_ptr<PieceSeedData> &PieceSeed )
	{
		val1 = val2 = 0;
		val1_IsSet = val2_IsSet = false;

		this->PieceSeed = PieceSeed;
	}

	Param::Param( const std::shared_ptr<PieceSeedData> &PieceSeed, float v )
	{
		val1 = val2 = 0;
		val1_IsSet = val2_IsSet = false;

		this->PieceSeed = PieceSeed;

		SetVal( v );
	}

	void Param::SetVal( float v )
	{
		if ( PieceSeed->MyUpgrades1 != 0 )
		{
			val1 = v;
			val1_IsSet = true;
		}
		if ( PieceSeed->MyUpgrades2 != 0 && PieceSeed->Start != PieceSeed->End )
		{
			val2 = v;
			val2_IsSet = true;
		}
	}

	float Param::GetVal()
	{
		if ( PieceSeed == 0 )
			return val1;

		std::shared_ptr<RichLevelGenData> data = PieceSeed->MyGenData;

		if ( !val1_IsSet || data->gen1 == 0 )
			return 0;
		if ( !val2_IsSet || data->gen2 == 0 )
			return val1;

		return val1;
	}

	float Param::GetVal( Vector2 Pos )
	{
		if ( PieceSeed == 0 )
			return val1;

		std::shared_ptr<RichLevelGenData> data = PieceSeed->MyGenData;

		if ( !val1_IsSet || data->gen1 == 0 )
			return 0;
		if ( !val2_IsSet || data->gen2 == 0 )
			return val1;

		Vector2 tangent = data->p2 - data->p1;
		float t = Vector2::Dot( Pos - data->p1, tangent ) / tangent.LengthSquared();

		return ( 1 - t ) * val1 + t * val2;
	}
}
