#include <small_header.h>
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"

#include "Core/PhsxData.h"
#include "Core/Tools/Random.h"
#include "Game/Level/Make/Generators.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Tools.h"

#include "Game/Player/Hero Physics/Base.h"

#include <Hacks/List.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	void StyleData::Release()
	{
		MyModParams->Clear();
		MyModParams.reset();
		GenParams.clear();
		Rnd.reset();
	}

	void StyleData::CalcGenParams( const boost::shared_ptr<PieceSeedData> &SeedData, const boost::shared_ptr<Level> &level )
	{
		GenParams = std::map<boost::shared_ptr<AutoGen>, boost::shared_ptr<AutoGen_Parameters> >();
		for ( std::vector<boost::shared_ptr<AutoGen> >::const_iterator gen = Generators::Gens.begin(); gen != Generators::Gens.end(); ++gen )
			GenParams.insert( std::make_pair( *gen, ( *gen )->SetParameters( SeedData, level ) ) );

		MyModParams->Apply( level, SeedData );

		// Change data depending on hero type
		level->DefaultHeroType->ModData( level->CurMakeData, shared_from_this() );
		level->DefaultHeroType->ModLadderPiece( SeedData );

		// Set time type
		level->TimeType = TimeType;
	}

	boost::shared_ptr<AutoGen_Parameters> StyleData::FindParams( const boost::shared_ptr<AutoGen> &gen )
	{
		return GenParams[ gen ];
	}

	//boost::shared_ptr<StyleData> StyleData::Clone()
	//{
	//	return static_cast<StyleData>( this->MemberwiseClone() );
	//}

	float _singlepathration[] = { .7f,.1f,.1f,.1f };
	std::vector<float> StyleData::_SinglePathRatio = VecFromArray( _singlepathration );

	StyleData::StyleData( const boost::shared_ptr<Rand> &Rnd )
	{
		//this.Rnd = new Rand(Rnd.MySeed);
		InitializeInstanceFields();
		this->Rnd = Rnd;

		Randomize();
	}

	void StyleData::Calculate( const boost::shared_ptr<Upgrades> &u )
	{
		float JumpLevel = u->Get( Upgrade_JUMP );

		float tempVector2[] = { 1, 1, 1, 1 };
		std::vector<float> PauseTypeRatio = VecFromArray( tempVector2 );
		PauseTypeRatio[ 0 ] += .3f * JumpLevel;
		PauseType = static_cast<_PauseType>( Rnd->Rnd->Next( 0, _PauseType_LENGTH ) );

		ReverseType = static_cast<_ReverseType>( Rnd->Rnd->Next( 0, _ReverseType_LENGTH ) );

		CalculateKeepUnused( JumpLevel );
	}

	void StyleData::CalculateKeepUnused( float JumpLevel )
	{
		// Extra fill: keep unused
		float ChanceToHaveUnused = .4f - .1f * ( .4f - -.2f ) * JumpLevel;
		if ( Rnd->RndFloat( 0, 1 ) < ChanceToHaveUnused )
		{
			float chance = .1f - .1f * ( .1f - 0 ) * JumpLevel;
			ChanceToKeepUnused = Rnd->RndFloat( 0, chance );
		}
	}

	void StyleData::Randomize()
	{
		int TestNumber;

		TestNumber = Rnd->RndInt( 0, 1000 );
		Tools::Write( Format( _T( "Pre-style: %d" ), TestNumber ).c_str() );

		FillxStep = 225;
		FillyStep = 200;

		//FillxStep = 175;
		//FillyStep = 175;

		UpperSafetyNetOffset = 0;

		MyGroundType = GroundType_SAFETY_NET;
		MyTopType = GroundType_INVERT_SAFETY_NET;

		// Fast
		//TopSpace = 560;
		//BottomSpace = 250;

		// Compromise, still too slow
		TopSpace = 360;
		BottomSpace = 180;

		// Ideal, way too slow
		//TopSpace = -250;
		//BottomSpace = -250;

		MakeInitialPlats = true;

		OverlapCleanupType = _OverlapCleanupType_REGULAR;

		SparsityType = static_cast<_SparsityType>( Rnd->Choose( SparsityTypeRatio ) );

		ElevatorSwitchType = static_cast<_ElevatorSwitchType>( Rnd->Choose( ElevatorSwitchTypeRatio ) );

		FlyingBlobOffsetType = static_cast<_OffsetType>( Rnd->Choose( OffsetTypeRatio ) );
		PendulumOffsetType = static_cast<_OffsetType>( Rnd->Choose( OffsetTypeRatio ) );

		JumpType = static_cast<_JumpType>( Rnd->Rnd->Next( 0, _JumpType_LENGTH ) );


		MoveTypePeriod = static_cast<_MoveTypePeriod>( Rnd->Rnd->Next( 0, _MoveTypePeriod_LENGTH ) );
		MoveTypeInnerPeriod = static_cast<_MoveTypeInnerPeriod>( Rnd->Rnd->Next( 0, _MoveTypeInnerPeriod_LENGTH ) );

		FillType = static_cast<_FillType>( Rnd->Choose( FillTypeRatio ) );

		PauseType = static_cast<_PauseType>( Rnd->Rnd->Next( 0, _PauseType_LENGTH ) );

		// Path types
		Bob1Start = static_cast<_StartType>( Rnd->Rnd->Next( 0, _StartType_LENGTH ) );
		Bob2Start = static_cast<_StartType>( Rnd->Rnd->Next( 0, _StartType_LENGTH ) );
		Bob3Start = static_cast<_StartType>( Rnd->Rnd->Next( 0, _StartType_LENGTH ) );
		SinglePathType = static_cast<_SinglePathType>( Rnd->Choose( _SinglePathRatio ) );
		DoublePathType = static_cast<_DoublePathType>( Rnd->Rnd->Next( 0, _DoublePathType_LENGTH ) );
		TriplePathType = static_cast<_TriplePathType>( Rnd->Rnd->Next( 0, _TriplePathType_LENGTH ) );

		TestNumber = Rnd->RndInt( 0, 1000 );
		Tools::Write( Format( _T( "Post-style: %d" ), TestNumber ).c_str() );
	}

	float StyleData::GetSparsity()
	{
		return Sparsity[ static_cast<int>( SparsityType ) ];
	}

	int StyleData::GetOffset( int Period, Vector2 pos, _OffsetType Type )
	{
		switch ( Type )
		{
			case _OffsetType_RANDOM:
				return Rnd->Rnd->Next( 0, Period );
			case _OffsetType_ALL_SAME:
				return 0;
			case _OffsetType_SPATIALLY_PERIODIC:
				return ( static_cast<int>( Period * ( pos.X / 2000 ) ) ) % Period;
		}

		return 0;
	}

	void StyleData::SetStartType( PhsxData &Start, Vector2 &CheckpointShift, _StartType StartType, const boost::shared_ptr<PieceSeedData> &Piece )
	{
		switch ( StartType )
		{
			case _StartType_TOP:
				Start.Position = Vector2( 100, 600 ) + Piece->Start;
				CheckpointShift = Vector2( 0, 50 );
				break;

			case _StartType_MIDDLE:
				Start.Position = Vector2( 100, -75 ) + Piece->Start;
				CheckpointShift = Vector2( 0, 210 );
				break;

			case _StartType_BOTTOM:
				Start.Position = Vector2( 100, -530 ) + Piece->Start;
				CheckpointShift = Vector2( 0, 220 );
				break;
		}
	}

	void StyleData::SetSinglePathType( const boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &Piece )
	{
		SetStartType( makeData->Start[ 0 ], makeData->CheckpointShift[ 0 ], Bob1Start, Piece );

		switch ( SinglePathType )
		{
			case _SinglePathType_NORMAL:
				makeData->MoveData[ 0 ].MaxTargetY = 875;
				makeData->MoveData[ 0 ].MinTargetY = -625;
				break;

			case _SinglePathType_HIGH:
				makeData->MoveData[ 0 ].MaxTargetY = 950;
				makeData->MoveData[ 0 ].MinTargetY = 100;
				break;

			case _SinglePathType_MID:
				makeData->MoveData[ 0 ].MaxTargetY = 450;
				makeData->MoveData[ 0 ].MinTargetY = -100;
				break;

			case _SinglePathType_LOW:
				makeData->MoveData[ 0 ].MaxTargetY = 300;
				makeData->MoveData[ 0 ].MinTargetY = -500;
				break;
		}
	}

	void StyleData::SetDoubePathType( const boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &Piece )
	{
		if ( DoublePathType == _DoublePathType_INDEPENDENT )
			DoublePathType = _DoublePathType_GAP;

		// Make sure double paths are always well separated
		if ( Rnd->RndBool() )
		{
			Bob1Start = _StartType_BOTTOM;
			Bob2Start = _StartType_TOP;
		}
		else
		{
			Bob1Start = _StartType_TOP;
			Bob2Start = _StartType_BOTTOM;
		}

		SetStartType( makeData->Start[ 0 ], makeData->CheckpointShift[ 0 ], Bob1Start, Piece );
		SetStartType( makeData->Start[ 1 ], makeData->CheckpointShift[ 1 ], Bob2Start, Piece );
		makeData->Start[ 1 ].Position.X += 100;

		switch ( DoublePathType )
		{
			case _DoublePathType_INDEPENDENT:
				for ( int i = 0; i < 2; i++ )
				{
					makeData->MoveData[ i ].MaxTargetY = 900;
					makeData->MoveData[ i ].MinTargetY = -600;
				}
				break;

			case _DoublePathType_SEPARATED:
				makeData->MoveData[ 0 ].MaxTargetY = 900;
				makeData->MoveData[ 0 ].MinTargetY = 120;

				makeData->MoveData[ 1 ].MaxTargetY = 100;
				makeData->MoveData[ 1 ].MinTargetY = -600;
				break;

			case _DoublePathType_GAP:
				makeData->MoveData[ 0 ].MaxTargetY = 1000;
				makeData->MoveData[ 0 ].MinTargetY = 700;

				makeData->MoveData[ 1 ].MaxTargetY = -300;
				makeData->MoveData[ 1 ].MinTargetY = -700;
				break;
		}
	}

	void StyleData::SetTriplePathType( const boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &Piece )
	{
		if ( TriplePathType == _TriplePathType_INDEPENDENT )
			TriplePathType = _TriplePathType_SEPARATED;

		SetStartType( makeData->Start[ 0 ], makeData->CheckpointShift[ 0 ], Bob1Start, Piece );
		SetStartType( makeData->Start[ 1 ], makeData->CheckpointShift[ 1 ], Bob2Start, Piece );
		SetStartType( makeData->Start[ 2 ], makeData->CheckpointShift[ 2 ], Bob3Start, Piece );
		makeData->Start[ 1 ].Position.X += 60;
		makeData->Start[ 2 ].Position.X += 120;

		switch ( TriplePathType )
		{
			case _TriplePathType_INDEPENDENT:
				for ( int i = 0; i < 2; i++ )
				{
					makeData->MoveData[ i ].MaxTargetY = 1000;
					makeData->MoveData[ i ].MinTargetY = -650;
				}
				break;

			case _TriplePathType_SEPARATED:
				makeData->MoveData[ 0 ].MaxTargetY = 1000;
				makeData->MoveData[ 0 ].MinTargetY = 450;

				makeData->MoveData[ 1 ].MaxTargetY = 450;
				makeData->MoveData[ 1 ].MinTargetY = -200;

				makeData->MoveData[ 2 ].MaxTargetY = -280;
				makeData->MoveData[ 2 ].MinTargetY = -650;
				break;
		}
	}

	void StyleData::SuppressGroundCeiling( const boost::shared_ptr<PieceSeedData> &piece )
	{
		boost::shared_ptr<Ceiling_Parameters> Ceiling_Params = boost::dynamic_pointer_cast<Ceiling_Parameters>( FindParams( Ceiling_AutoGen::getInstance() ) );
		Ceiling_Params->Make = false;
		boost::shared_ptr<NormalBlock_Parameters> NBlock_Params = boost::dynamic_pointer_cast<NormalBlock_Parameters>( FindParams( NormalBlock_AutoGen::getInstance() ) );
		NBlock_Params->Make = false;
	}

	void StyleData::SetToMake_BouncyHallway( const boost::shared_ptr<PieceSeedData> &piece )
	{
		SuppressGroundCeiling( piece );

		boost::shared_ptr<BouncyBlock_Parameters> Bounce_Params = boost::dynamic_pointer_cast<BouncyBlock_Parameters>( FindParams( BouncyBlock_AutoGen::getInstance() ) );
		Bounce_Params->Special.Hallway = true;
	}

	void StyleData::InitializeInstanceFields()
	{
		UseLowerBlockBounds = false;

		MyGroundType = MyTopType = static_cast<GroundType>( 0 );
		RemovedUnusedOverlappingBlocks = false;
		RemoveBlockOnCol = false;
		RemoveBlockOnOverlap = false;
		MinBlockDist = 0;

		ChanceToKeepUnused = 0;
		FunRun = false;
		Masochistic = false;
		RemovedUnusedOverlappingBlocks = false;
		RemoveBlockOnCol = false;
		RemoveBlockOnOverlap = false;
		MinBlockDist = 0;


		Zoom = 0;
		TimeType = static_cast<TimeTypes>( 0 );
		SuppressCoins = false; SuppressCheckpoints = false;
		TopSpace = 0; BottomSpace = 0;
		FillxStep = 0; FillyStep = 0;
		ModNormalBlockWeight = 0;
		MyFinalPlatsType = static_cast<FinalPlatsType>( 0 );
		MyFinalDoorStyle = static_cast<FinalDoorStyle>( 0 );
		MyInitialPlatsType = static_cast<InitialPlatsType>( 0 );
		MakeInitialPlats = false;
		UpperSafetyNetOffset = 0; LowerSafetyNetOffset = 0;
		BlockFillType = static_cast<_BlockFillType>( 0 );
		OverlapCleanupType = static_cast<_OverlapCleanupType>( 0 );
		AlwaysCurvyMove = false;
		AlwaysEdgeJump = false;
		MoveTypePeriod = static_cast<_MoveTypePeriod>( 0 );
		MoveTypeInnerPeriod = static_cast<_MoveTypeInnerPeriod>( 0 );
		PauseType = static_cast<_PauseType>( 0 );
		ReverseType = static_cast<_ReverseType>( 0 );
		JumpType = static_cast<_JumpType>( 0 );
		ElevatorSwitchType = static_cast<_ElevatorSwitchType>( 0 );
		PendulumOffsetType = static_cast<_OffsetType>( 0 ); FlyingBlobOffsetType = static_cast<_OffsetType>( 0 );
		FillType = static_cast<_FillType>( 0 );
		SinglePathType = static_cast<_SinglePathType>( 0 );
		DoublePathType = static_cast<_DoublePathType>( 0 );
		TriplePathType = static_cast<_TriplePathType>( 0 );
		Bob1Start = Bob2Start = Bob3Start = static_cast<_StartType>( 0 );
		ChanceToKeepUnused = 0;
		FunRun = false;
		Masochistic = false;




		MyModParams = boost::make_shared<Multicaster_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> > >();
		Zoom = 1;
		TimeType = TimeTypes_REGULAR;
		ModNormalBlockWeight = 1;
		ComputerWaitLengthRange = Vector2( 15, 36 );
		DoorHitBoxPadding = Vector2();
		MyFinalPlatsType = FinalPlatsType_DOOR;
		MyFinalDoorStyle = FinalDoorStyle_NORMAL;
		MyInitialPlatsType = InitialPlatsType_NORMAL;
		SafeStartPadding = 0;
		SafeEndPadding = 0;
		LengthPadding = 0;
		AutoOpenDoor = false;

		float tempVector3[] = { 1, 0 };
		BlockFillTypeRatio = VecFromArray( tempVector3 );

		float tempVector4[] = { 1, 1.5f, 2, 4 };
		Sparsity = VecFromArray( tempVector4 );

		float tempVector5[] = { .5f,.35f,.1f,.05f };
		SparsityTypeRatio = VecFromArray( tempVector5 );

		AlwaysCurvyMove = false;
		AlwaysEdgeJump = false;

		float tempVector6[] = { .35f,.5f,.1f,.05f };
		ElevatorSwitchTypeRatio = VecFromArray( tempVector6 );

		float tempVector7[] = { .7f,.25f,.05f };
		OffsetTypeRatio = VecFromArray( tempVector7 );

		float tempVector8[] = { .7f,.25f,.05f };
		FillTypeRatio = VecFromArray( tempVector8 );

		FunRun = true;
		Masochistic = false;
	}
}
