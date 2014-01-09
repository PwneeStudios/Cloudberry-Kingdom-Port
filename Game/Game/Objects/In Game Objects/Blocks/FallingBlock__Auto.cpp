#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/FallingBlock__Auto.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Blocks/FallingBlock.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Core/Tools/Random.h"

namespace CloudberryKingdom
{

	void FallingBlock_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{


		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_FALLING_BLOCK ) ) );
		}

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( u->Get( Upgrade_FALLING_BLOCK ) );

		Delay = Param( PieceSeed );
		Delay.SetVal( __max( 1, 60 - 7 * u->Get( Upgrade_FALLING_BLOCK ) ) );

		Width = Param( PieceSeed );
		Width.SetVal( __max( 70, 113 - .1f * ( 110 - 70 ) * u->Get( Upgrade_FALLING_BLOCK ) ) );

		AngryAccel = Param( PieceSeed );
		AngryAccel.SetVal( DifficultyHelper::Interp( -70, 320, u->Get( Upgrade_BOUNCY_BLOCK ) ) );

		AngryRatio = Param( PieceSeed );
		AngryRatio.SetVal( DifficultyHelper::Interp( -27, 35, u->Get( Upgrade_BOUNCY_BLOCK ) ) );

		AngrySpeed = Param( PieceSeed );
		AngrySpeed.SetVal( 4 * u->Get( Upgrade_FALLING_BLOCK ) );
	}

boost::shared_ptr<FallingBlock_AutoGen> FallingBlock_AutoGen::instance = boost::make_shared<FallingBlock_AutoGen>();

	const boost::shared_ptr<FallingBlock_AutoGen> &FallingBlock_AutoGen::getInstance()
	{
		return instance;
	}

	FallingBlock_AutoGen::FallingBlock_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> FallingBlock_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<FallingBlock_Parameters> Params = boost::make_shared<FallingBlock_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void FallingBlock_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void FallingBlock_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	boost::shared_ptr<ObjectBase> FallingBlock_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		boost::shared_ptr<StyleData> Style = level->getStyle();
		boost::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		boost::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get FallingBlock parameters
		boost::shared_ptr<FallingBlock_Parameters> Params = boost::static_pointer_cast<FallingBlock_Parameters>( level->getStyle()->FindParams( FallingBlock_AutoGen::getInstance() ) );

		boost::shared_ptr<FallingBlock> fblock;
		float Width = Params->Width.GetVal( pos );
		Vector2 size = Vector2( Width, Width );
		Vector2 offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ),
								  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) - size.Y ) );

		fblock = boost::static_pointer_cast<FallingBlock>( level->getRecycle()->GetObject(ObjectType_FALLING_BLOCK, true) );
		int Life = static_cast<int>( Params->Delay.GetVal( pos ) );
		fblock->Init( pos + offset, size, Life, level );
		fblock->getBlockCore()->BlobsOnTop = true;

		fblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		fblock->getBlockCore()->GenData.EdgeSafety = static_cast<float>( GenData->Get(DifficultyParam_EDGE_SAFETY, pos) );

		if ( level->getRnd()->Rnd->NextDouble() < Params->AngryRatio.GetVal(pos) / 100 )
		{
			// Make angry
			fblock->Thwomp = true;
			fblock->AngryMaxSpeed = Params->AngrySpeed.GetVal( pos );
			fblock->AngryAccel = Vector2( 0, Params->AngryAccel.GetVal( pos ) / 100 );
		}

		if ( level->getStyle()->RemoveBlockOnOverlap )
			fblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( fblock );

		return fblock;
	}
}
