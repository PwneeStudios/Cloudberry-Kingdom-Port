#include <global_header.h>

namespace CloudberryKingdom
{

	void RichLevelGenData::Set_Difficulty( int type, int val )
	{
		if ( gen1 == 0 )
			return;
		gen1->Set_Difficulty( type, val );

		if ( gen2 != 0 )
			gen2->Set_Difficulty( type, val );
	}

	int RichLevelGenData::Get_Difficulty( int type )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1->Get_Difficulty( type );

		return __max( gen1->Get_Difficulty( type ), gen2->Get_Difficulty( type ) );
	}

	int RichLevelGenData::Get_Difficulty( int type, Vector2 pos )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1->Get_Difficulty( type );

		Vector2 tangent = p2 - p1;
		float length = tangent.LengthSquared();

		if ( length < 100 )
			return gen1->Get_Difficulty( type );

		float t = __max( 0, __min( 1, Vector2::Dot( pos - p1, tangent ) / length ) );

		return static_cast<int>( ( 1 - t ) * gen1->Get_Difficulty( type ) + t * gen2->Get_Difficulty( type ) );
	}

	void RichLevelGenData::Set_Behavior( int type, int val )
	{
		gen2->Set_Behavior( type, val );
		gen1->Set_Behavior( type, val );
	}

	int RichLevelGenData::Get_Behavior( int type )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1->Get_Behavior( type );

		return __max( gen1->Get_Behavior( type ), gen2->Get_Behavior( type ) );
	}

	int RichLevelGenData::Get_Behavior( int type, Vector2 pos )
	{
		// FIXME: Implement exceptions?
		//if ( gen1 == 0 )
		//	throw ( std::exception( _T( "No gen data to retrieve!" ) ) );
		if ( gen2 == 0 )
			return gen1->Get_Behavior( type );

		Vector2 tangent = p2 - p1;
		float t = Vector2::Dot( pos, tangent ) / tangent.LengthSquared();
		t = __max( 0, __min( 1, t ) );

		int val = static_cast<int>( .5f + ( 1 - t ) * static_cast<float>( gen1->Get_Behavior( type ) ) + t * static_cast<float>( gen2->Get_Behavior( type ) ) );

		// FIXME: Implement exceptions?
		//if ( val < 1 )
		//	throw ( std::exception( _T( "Nonpositive return!" ) ) );

		return val;
	}

	void LevelGenData::Set_Difficulty( int type, int val )
	{
		Difficulty[ type ] = val;
	}

	void LevelGenData::Set_Behavior( int type, int val )
	{
		BehaviorParams[ type ] = val;
	}

	int LevelGenData::Get_Difficulty( int type )
	{
		return Difficulty[ type ];
	}

	int LevelGenData::Get_Behavior( int type )
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


		const int tempVector[] = { 4, 5, 20, 20, 5, 10, 2, 2, 2, 2, 2, 20, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 };
		BehaviorParams = std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}
}
