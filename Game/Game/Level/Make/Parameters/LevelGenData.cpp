#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	void RichLevelGenData::Set( DifficultyParam type, int val )
	{
		if ( gen1 == 0 )
			return;
		gen1->Set( type, val );

		if ( gen2 != 0 )
			gen2->Set( type, val );
	}

	int RichLevelGenData::Get( DifficultyParam type )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1->Get( type );

		return __max( gen1->Get( type ), gen2->Get( type ) );
	}

	int RichLevelGenData::Get( DifficultyParam type, Vector2 pos )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1->Get( type );

		Vector2 tangent = p2 - p1;
		float length = tangent.LengthSquared();

		if ( length < 100 )
			return gen1->Get( type );

		float t = __max( 0, __min( 1, Vector2::Dot( pos - p1, tangent ) / length ) );

		return static_cast<int>( ( 1 - t ) * gen1->Get( type ) + t * gen2->Get( type ) );
	}

	void RichLevelGenData::Set( BehaviorParam type, int val )
	{
		gen2->Set( type, val );
		gen1->Set( type, val );
	}

	int RichLevelGenData::Get( BehaviorParam type )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1->Get( type );

		return __max( gen1->Get( type ), gen2->Get( type ) );
	}

	int RichLevelGenData::Get( BehaviorParam type, Vector2 pos )
	{
		// FIXME: Implement exceptions?
		//if ( gen1 == 0 )
		//	throw ( std::exception( std::wstring( L"No gen data to retrieve!" ) ) );
		if ( gen2 == 0 )
			return gen1->Get( type );

		Vector2 tangent = p2 - p1;
		float t = Vector2::Dot( pos, tangent ) / tangent.LengthSquared();
		t = __max( 0, __min( 1, t ) );

		int val = static_cast<int>( .5f + ( 1 - t ) * static_cast<float>( gen1->Get( type ) ) + t * static_cast<float>( gen2->Get( type ) ) );

		// FIXME: Implement exceptions?
		//if ( val < 1 )
		//	throw ( std::exception( std::wstring( L"Nonpositive return!" ) ) );

		return val;
	}

	void LevelGenData::Set( DifficultyParam type, int val )
	{
		Difficulty[ type ] = val;
	}

	void LevelGenData::Set( BehaviorParam type, int val )
	{
		BehaviorParams[ type ] = val;
	}

	int LevelGenData::Get( DifficultyParam type )
	{
		return Difficulty[ type ];
	}

	int LevelGenData::Get( BehaviorParam type )
	{
		return BehaviorParams[ type ];
	}

	LevelGenData::LevelGenData()
	{
		Difficulty = std::vector<int>( Tools::DifficultyTypes );
		Difficulty[ static_cast<int>( DifficultyParam_LONG_JUMP_START ) ] = 165;
		Difficulty[ static_cast<int>( DifficultyParam_MIN_FALL ) ] = 5;
		Difficulty[ static_cast<int>( DifficultyParam_MAX_FALL ) ] = 10;
		Difficulty[ static_cast<int>( DifficultyParam_MIN_DROP ) ] = 200;
		Difficulty[ static_cast<int>( DifficultyParam_MAX_DROP ) ] = 900;

		int tempVector[] = { 4, 5, 20, 20, 5, 10, 2, 2, 2, 2, 2, 20, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		BehaviorParams = VecFromArray( tempVector );
	}
}
