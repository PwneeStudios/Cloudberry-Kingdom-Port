#include "LevelGenData.h"
#include "Game/Tools/Tools.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void RichLevelGenData::Set( DifficultyParam type, int val )
	{
		if ( gen1 == 0 )
			return;
		gen1[ type ] = val;

		if ( gen2 != 0 )
			gen2[ type ] = val;
	}

	int RichLevelGenData::Get( DifficultyParam type )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1[ type ];

		return __max( gen1[ type ], gen2[ type ] );
	}

	int RichLevelGenData::Get( DifficultyParam type, Vector2 pos )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1[ type ];

		Vector2 tangent = p2 - p1;
		float length = tangent.LengthSquared();

		if ( length < 100 )
			return gen1[ type ];

		float t = __max( 0, __min( 1, Vector2::Dot( pos - p1, tangent ) / length ) );

		return static_cast<int>( ( 1 - t ) * gen1[ type ] + t * gen2[ type ] );
	}

	void RichLevelGenData::Set( BehaviorParam type, int val )
	{
		gen2[ type ] = val;
	gen1[ type ] = gen2[ type ];
	}

	int RichLevelGenData::Get( BehaviorParam type )
	{
		if ( gen1 == 0 )
			return 0;
		if ( gen2 == 0 )
			return gen1[ type ];

		return __max( gen1[ type ], gen2[ type ] );
	}

	int RichLevelGenData::Get( BehaviorParam type, Vector2 pos )
	{
		if ( gen1 == 0 )
			throw ( std::exception( _T( "No gen data to retrieve!" ) ) );
		if ( gen2 == 0 )
			return gen1[ type ];

		Vector2 tangent = p2 - p1;
		float t = Vector2::Dot( pos, tangent ) / tangent.LengthSquared();
		t = __max( 0, __min( 1, t ) );

		int val = static_cast<int>( .5f + ( 1 - t ) * static_cast<float>( gen1[ type ] ) + t * static_cast<float>( gen2[ type ] ) );

		if ( val < 1 )
			throw ( std::exception( _T( "Nonpositive return!" ) ) );

		return val;
	}

	int &LevelGenData::operator []( DifficultyParam type )
	{
		return Difficulty[ static_cast<int>( type ) ];
	}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//	void LevelGenData::setdefault(const DifficultyParam &type, int value)
//	{
//		Difficulty[safe_cast<int>(type)] = value;
//	}

	int &LevelGenData::operator []( BehaviorParam type )
	{
		return BehaviorParams[ static_cast<int>( type ) ];
	}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//	void LevelGenData::setdefault(const BehaviorParam &type, int value)
//	{
//		BehaviorParams[safe_cast<int>(type)] = value;
//	}

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
