#ifndef LEVELGENDATA
#define LEVELGENDATA

#include "../Core/Tools/Set.h"
#include <cmath>
#include <stdexcept>
#include <tchar.h>

namespace CloudberryKingdom
{
	class LevelGenData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	enum DifficultyParam
	{
		DifficultyParam_BIG_BOX_X,
		DifficultyParam_BIG_BOX_Y,
		DifficultyParam_GENERAL_MIN_DIST,
		DifficultyParam_MIN_BOX_SIZE_X,
		DifficultyParam_MIN_BOX_SIZE_Y,
		DifficultyParam_MAX_BOX_SIZE_X,
		DifficultyParam_MAX_BOX_SIZE_Y,

		DifficultyParam_LONG_JUMP_START,
		DifficultyParam_MIN_FALL,
		DifficultyParam_MAX_FALL,
		DifficultyParam_MIN_DROP,
		DifficultyParam_MAX_DROP,
		DifficultyParam_TIME_TO_BOB_TARGET_SWITCH,
		DifficultyParam_JUMPING_SPEED_RETARD_FACTOR,
		DifficultyParam_RETARD_JUMP_LENGTH,
		DifficultyParam_DISTANCE_PAST,
		DifficultyParam_DISTANCE_PAST_NO_JUMP,
		DifficultyParam_EDGE_JUMP_DURATION,
		DifficultyParam_NO_EDGE_JUMP_DURATION,
		DifficultyParam_EDGE_SAFETY, // How close to the edge of a block the computer can land on
		DifficultyParam_APEX_WAIT, // How long after the apex of a jump should we wait before potentially landing on something?
		DifficultyParam_FILL_SPARSITY,
	};

	enum BehaviorParam
	{
		BehaviorParam_FALL_LENGTH_BASE,
		BehaviorParam_FALL_LENGTH_ADD,
		BehaviorParam_BACK_LENGTH_BASE,
		BehaviorParam_BACK_LENGTH_ADD,
		BehaviorParam_FORWARD_LENGTH_BASE,
		BehaviorParam_FORWARD_LENGTH_ADD,
		BehaviorParam_MOVE_WEIGHT,
		BehaviorParam_SIT_WEIGHT,
		BehaviorParam_MOVE_LENGTH_BASE,
		BehaviorParam_MOVE_LENGTH_ADD,
		BehaviorParam_SIT_LENGTH_BASE,
		BehaviorParam_SIT_LENGTH_ADD,
		BehaviorParam_JUMP_WEIGHT,
		BehaviorParam_NO_JUMP_WEIGHT,
		BehaviorParam_JUMP_LENGTH_BASE,
		BehaviorParam_JUMP_LENGTH_ADD,
		BehaviorParam_NO_JUMP_LENGTH_BASE,
		BehaviorParam_NO_JUMP_LENGTH_ADD,
		BehaviorParam_MOVE_TYPE_PERIOD,
		BehaviorParam_MOVE_TYPE_INNER_PERIOD
	};

	class RichLevelGenData
	{
	public:
		std::shared_ptr<LevelGenData> gen1, gen2;
		Vector2 p1, p2;

		void Set( DifficultyParam type, int val );
		int Get( DifficultyParam type );
		int Get( DifficultyParam type, Vector2 pos );


		void Set( BehaviorParam type, int val );
		int Get( BehaviorParam type );
		int Get( BehaviorParam type, Vector2 pos );
	};

	class LevelGenData
	{
	public:
		std::vector<int> Difficulty;
		std::vector<int> BehaviorParams;

		//public int Get(DifficultyParam type) { return Difficulty[(int)type]; }
		//public int Get(BehaviorParam type) { return Difficulty[(int)type]; }

		int &operator []( DifficultyParam type );

		int &operator []( BehaviorParam type );

		LevelGenData();
	};
}


#endif	//#ifndef LEVELGENDATA
