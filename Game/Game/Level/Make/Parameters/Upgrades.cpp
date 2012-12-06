#include <global_header.h>

namespace CloudberryKingdom
{

	Upgrades::Upgrades()
	{
		Initialize();
	}

	Upgrades::Upgrades( const std::shared_ptr<Upgrades> &u )
	{
		Initialize();
		CopyFrom( u );
	}

	void Upgrades::Initialize()
	{
		UpgradeLevels = std::vector<float>( Tools::UpgradeTypes );
	}

	void Upgrades::CopyFrom( const std::shared_ptr<Upgrades> &u )
	{
		//u->UpgradeLevels.CopyTo( UpgradeLevels, 0 );
		CopyFromTo( u->UpgradeLevels, UpgradeLevels);
	}

	float &Upgrades::Get( int upgrade )
	{
		return UpgradeLevels[ upgrade ];
	}

//C# TO C++ CONVERTER TODO TASK: You cannot specify separate 'set' logic for indexers in native C++:
//	void Upgrades::setdefault(const Upgrade &upgrade, float value)
//	{
//		UpgradeLevels[safe_cast<int>(upgrade)] = value;
//	}

	void Upgrades::Zero()
	{
		for ( int i = 0; i < static_cast<int>( UpgradeLevels.size() ); i++ )
			UpgradeLevels[ i ] = 0;
	}

	int Upgrades::MaxBobWidth = 360;

	void Upgrades::CalcGenData( const std::shared_ptr<LevelGenData> &GenData, const std::shared_ptr<StyleData> &Style )
	{
		Style->Calculate( shared_from_this() );

		float JumpLevel = Get( Upgrade_JUMP );
		JumpLevel = 3.75f + .625f * JumpLevel;

		// Jump
		GenData->Set( DifficultyParam_FILL_SPARSITY, 100);
		int Min = static_cast<int>( DifficultyHelper::InterpRestrict19( 180, 40, Get( Upgrade_JUMP ) ) );
		GenData->Set( DifficultyParam_MIN_BOX_SIZE_X, Min );

		if ( Min < 50 )
			GenData->Set( DifficultyParam_MIN_BOX_SIZE_X, 10 );
		GenData->Set( DifficultyParam_MAX_BOX_SIZE_X, static_cast<int>( DifficultyHelper::Interp( 420.f, Min + 1.f, Get( Upgrade_JUMP ) ) ) );
			//(int)Math.Max(Min + 1, 380 - 50 * this[Upgrade.Jump]);
			//(int)DifficultyHelper.Interp(460, Min + 1, this[Upgrade.Jump]);
		GenData->Set( DifficultyParam_MIN_BOX_SIZE_Y, 2000 );
		GenData->Set( DifficultyParam_MAX_BOX_SIZE_Y, 2000 );

		GenData->Set( DifficultyParam_TIME_TO_BOB_TARGET_SWITCH, static_cast<int>( __max( 10, 700 - 150 * JumpLevel ) ) );

		GenData->Set( DifficultyParam_JUMPING_SPEED_RETARD_FACTOR, static_cast<int>( __min( 100, 66 + 3.4f * JumpLevel ) ) );
						//(int)Math.Min(100, 76f + 3f * JumpLevel);
		GenData->Set( DifficultyParam_RETARD_JUMP_LENGTH, static_cast<int>( DifficultyHelper::Interp159( 9, 6, -1, JumpLevel ) ) );
		GenData->Set( DifficultyParam_DISTANCE_PAST, static_cast<int>( __min( 10, 5 - 115 + .1f * 115 * JumpLevel ) ) );
		GenData->Set( DifficultyParam_DISTANCE_PAST_NO_JUMP, static_cast<int>( __min( 800,.1f * 700 * JumpLevel ) ) );
		GenData->Set( DifficultyParam_EDGE_JUMP_DURATION, static_cast<int>( __min( 800,.1f * 300 * JumpLevel ) ) );
		GenData->Set( DifficultyParam_NO_EDGE_JUMP_DURATION, static_cast<int>( __max( 0, 300 - .1f * 300 * JumpLevel ) ) );

		GenData->Set( DifficultyParam_EDGE_SAFETY, static_cast<int>( __max( 1, 20 - 2 * Get( Upgrade_JUMP ) ) ) );

		GenData->Set( DifficultyParam_APEX_WAIT, static_cast<int>( __max( 2, 8 - .95f * Get( Upgrade_JUMP ) ) ) );
			//(int)Math.Max(2, 12f - 1.1f * this[Upgrade.Jump]);




		GenData->Set( BehaviorParam_FORWARD_LENGTH_BASE, 60 );
		GenData->Set( BehaviorParam_FORWARD_LENGTH_ADD, 100 );
		GenData->Set( BehaviorParam_BACK_LENGTH_BASE, 3 );
		GenData->Set( BehaviorParam_BACK_LENGTH_ADD, 15 );
		if ( Style->ReverseType == StyleData::_ReverseType_NONE )
		{
			GenData->Set( BehaviorParam_BACK_LENGTH_BASE, 1 );
			GenData->Set( BehaviorParam_BACK_LENGTH_ADD, 1 );
		}
		if ( Style->ReverseType == StyleData::_ReverseType_NORMAL2 )
		{
			GenData->Set( BehaviorParam_BACK_LENGTH_BASE, 6 );
			GenData->Set( BehaviorParam_BACK_LENGTH_ADD, 12 );
		}
		if ( Style->ReverseType == StyleData::_ReverseType_NORMAL3 )
		{
			GenData->Set( BehaviorParam_BACK_LENGTH_BASE, 10 );
			GenData->Set( BehaviorParam_BACK_LENGTH_ADD, 18 );
		}



		// Decrease reverse for higher jump levels
		float backbase = static_cast<float>( GenData->Get( BehaviorParam_BACK_LENGTH_BASE ) );
		backbase = static_cast<float>( static_cast<int>( backbase * __max( 0.1f, 12.f - JumpLevel ) / 10.f ) );
		backbase = __max( 1, backbase );
		GenData->Set( BehaviorParam_BACK_LENGTH_BASE, static_cast<int>( backbase ) );

		float backadd = static_cast<float>( GenData->Get( BehaviorParam_BACK_LENGTH_ADD ) );
		backadd = static_cast<float>( static_cast<int>( backadd * __max( 0.1f, 12.f - JumpLevel ) / 10.f ) );
		backadd = __max( 1, backadd );
		GenData->Set( BehaviorParam_BACK_LENGTH_ADD, static_cast<int>( backadd ) );

		GenData->Set( BehaviorParam_FALL_LENGTH_BASE, 15 );
		GenData->Set( BehaviorParam_FALL_LENGTH_ADD, 60 );
		GenData->Set( BehaviorParam_JUMP_LENGTH_BASE, 15 );
		GenData->Set( BehaviorParam_JUMP_LENGTH_ADD, 60 );
		Style->JumpType = StyleData::_JumpType_ALWAYS;
		if ( Style->JumpType == StyleData::_JumpType_ALWAYS )
		{
			GenData->Set( BehaviorParam_FALL_LENGTH_BASE, 1 );
			GenData->Set( BehaviorParam_FALL_LENGTH_ADD, 10 );
		}
		if ( Style->JumpType == StyleData::_JumpType_ALOT )
		{
			GenData->Set( BehaviorParam_FALL_LENGTH_BASE, 10 );
			GenData->Set( BehaviorParam_FALL_LENGTH_ADD, 35 );
		}
		if ( Style->JumpType == StyleData::_JumpType_NORMAL2 )
		{
			GenData->Set( BehaviorParam_FALL_LENGTH_BASE, 1 );
			GenData->Set( BehaviorParam_FALL_LENGTH_ADD, 85 );
		}

		GenData->Set( BehaviorParam_MOVE_WEIGHT, static_cast<int>( 50 + 1 * JumpLevel ) );
		GenData->Set( BehaviorParam_MOVE_LENGTH_BASE, 20 );
		GenData->Set( BehaviorParam_MOVE_LENGTH_ADD, 20 );
		GenData->Set( BehaviorParam_SIT_WEIGHT, static_cast<int>( __max( 10, 20 - 4 * JumpLevel ) ) );
		GenData->Set( BehaviorParam_SIT_LENGTH_BASE, static_cast<int>( __max( 3, 10 - 1 * JumpLevel ) ) );
		GenData->Set( BehaviorParam_SIT_LENGTH_ADD, static_cast<int>( __max( 25, 8 - 1 * JumpLevel ) ) );
		if ( Style->PauseType == StyleData::_PauseType_NONE )
		{
			GenData->Set( BehaviorParam_SIT_WEIGHT, 1 );
			GenData->Set( BehaviorParam_SIT_LENGTH_BASE, 1 );
			GenData->Set( BehaviorParam_SIT_LENGTH_ADD, 1 );
		}
		if ( Style->PauseType == StyleData::_PauseType_LIMITED )
		{
			GenData->Set( BehaviorParam_SIT_WEIGHT, static_cast<int>( __max( 6, 20 - 5 * JumpLevel ) ) );
			GenData->Set( BehaviorParam_SIT_LENGTH_BASE, static_cast<int>( __max( 2, 10 - 1 * JumpLevel ) ) );
			GenData->Set( BehaviorParam_SIT_LENGTH_ADD, static_cast<int>( __max( 15, 8 - 1 * JumpLevel ) ) );
		}
		if ( Style->PauseType == StyleData::_PauseType_NORMAL2 )
		{
			GenData->Set( BehaviorParam_SIT_WEIGHT, static_cast<int>( __max( 7, 20 - 5 * JumpLevel ) ) );
			GenData->Set( BehaviorParam_SIT_LENGTH_BASE, static_cast<int>( __max( 15, 10 - 1 * JumpLevel ) ) );
			GenData->Set( BehaviorParam_SIT_LENGTH_ADD, static_cast<int>( __max( 45, 8 - 1 * JumpLevel ) ) );
		}

		switch ( Style->MoveTypePeriod )
		{
			case StyleData::_MoveTypePeriod_INF:
				GenData->Set( BehaviorParam_MOVE_TYPE_PERIOD, 300 );
				break;
			case StyleData::_MoveTypePeriod_NORMAL1:
				GenData->Set( BehaviorParam_MOVE_TYPE_PERIOD, 80 );
				break;
			case StyleData::_MoveTypePeriod_NORMAL2:
				GenData->Set( BehaviorParam_MOVE_TYPE_PERIOD, 150 );
				break;
			case StyleData::_MoveTypePeriod_SHORT:
				GenData->Set( BehaviorParam_MOVE_TYPE_PERIOD, 40 );
				break;
		}

		switch ( Style->MoveTypeInnerPeriod )
		{
			case StyleData::_MoveTypeInnerPeriod_LONG:
				GenData->Set( BehaviorParam_MOVE_TYPE_INNER_PERIOD, 65 );
				break;
			case StyleData::_MoveTypeInnerPeriod_NORMAL:
				GenData->Set( BehaviorParam_MOVE_TYPE_INNER_PERIOD, 40 );
				break;
			case StyleData::_MoveTypeInnerPeriod_SHORT:
				GenData->Set( BehaviorParam_MOVE_TYPE_INNER_PERIOD, 24 );
				break;
		}

		// General
		GenData->Set( DifficultyParam_GENERAL_MIN_DIST, __max( 40, 460 - 55 * static_cast<int>( Get( Upgrade_GENERAL ) ) ) );

		GenData->Set( DifficultyParam_BIG_BOX_X, __max( 0, MaxBobWidth - 40 * static_cast<int>( Get( Upgrade_GENERAL ) ) ) );
		//GenData[DifficultyParam.BigBoxY] = 0;// Math.Max(0, 150 - 20 * this[Upgrade.General]);

		// Fun run
		if ( Style->FunRun )
		{
			GenData->Set( BehaviorParam_FORWARD_LENGTH_BASE, __max( 1, GenData->Get( BehaviorParam_FORWARD_LENGTH_BASE ) / 2 ) );
			GenData->Set( BehaviorParam_FORWARD_LENGTH_ADD, __max( 1, GenData->Get( BehaviorParam_FORWARD_LENGTH_ADD ) / 2 ) );
			GenData->Set( BehaviorParam_BACK_LENGTH_BASE, __max( 1, GenData->Get( BehaviorParam_BACK_LENGTH_BASE ) / 2 ) );
			GenData->Set( BehaviorParam_BACK_LENGTH_ADD, __max( 1, GenData->Get( BehaviorParam_BACK_LENGTH_ADD ) / 2 ) );

			GenData->Set( BehaviorParam_SIT_WEIGHT, __max( 1, GenData->Get( BehaviorParam_SIT_WEIGHT ) / 2 ) );
			GenData->Set( BehaviorParam_SIT_LENGTH_BASE, __max( 1, GenData->Get( BehaviorParam_SIT_LENGTH_BASE ) / 2 ) );
			GenData->Set( BehaviorParam_SIT_LENGTH_ADD, __max( 1, GenData->Get( BehaviorParam_SIT_LENGTH_ADD ) / 2 ) );
		}
	}
}
