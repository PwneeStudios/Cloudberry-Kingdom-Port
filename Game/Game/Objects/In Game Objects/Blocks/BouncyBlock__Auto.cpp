#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/FloatRectangle.h"
#include "Core/Tools/Random.h"

namespace CloudberryKingdom
{

	void BouncyBlock_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		Special.Hallway = false;

		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_BOUNCY_BLOCK ) ) );
		}

		FillWeight = Param( PieceSeed, u->Get( Upgrade_BOUNCY_BLOCK ) );

		Speed = Param( PieceSeed );
		Speed.SetVal( DifficultyHelper::Interp( 45, 60, u->Get( Upgrade_BOUNCY_BLOCK ) ) );

		SideDampening = Param( PieceSeed );
		SideDampening.SetVal( DifficultyHelper::Interp159( .55f,.83f, 1.2f, u->Get( Upgrade_BOUNCY_BLOCK ) ) );

		Size = Param( PieceSeed );
		Size.SetVal( __max( 75, 105 - 1.85f * u->Get( Upgrade_BOUNCY_BLOCK ) ) );

		EdgeSafety = Param( PieceSeed );
		EdgeSafety.SetVal( __max( .01f, DifficultyHelper::Interp159( .4f,.3f,.05f, u->Get( Upgrade_BOUNCY_BLOCK ) ) ) );
	}

	boost::shared_ptr<BouncyBlock_AutoGen> BouncyBlock_AutoGen::instance = boost::make_shared<BouncyBlock_AutoGen>();

	const boost::shared_ptr<BouncyBlock_AutoGen> &BouncyBlock_AutoGen::getInstance()
	{
		return instance;
	}

	BouncyBlock_AutoGen::BouncyBlock_AutoGen()
	{
		Do_PreFill_1 = true;

		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> BouncyBlock_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<BouncyBlock_Parameters> Params = boost::make_shared<BouncyBlock_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void BouncyBlock_AutoGen::SetHallwaysBlockProperties( const boost::shared_ptr<BouncyBlock> &block, const boost::shared_ptr<Level> &level )
	{
		block->getCore()->GenData.Used = true;

		block->Init( block->getCore()->Data.Position, Vector2(150, 150), 80, level );
	}

	void BouncyBlock_AutoGen::Hallway( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		BL.X = level->FillBL.X;

		float x = BL.X;

		while ( x < TR.X )
		{
			boost::shared_ptr<BouncyBlock> block;
			block = boost::static_pointer_cast<BouncyBlock>( CreateAt( level, Vector2( x, TR.Y - 300 ) ) );
			SetHallwaysBlockProperties( block, level );
			block = boost::static_pointer_cast<BouncyBlock>( CreateAt( level, Vector2( x, BL.Y + 300 ) ) );
			SetHallwaysBlockProperties( block, level );

			x += 2 * block->getBox()->Current->Size.X;
		}
	}

	void BouncyBlock_AutoGen::PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_1( level, BL, TR );

		boost::shared_ptr<BouncyBlock_Parameters> Params = boost::static_pointer_cast<BouncyBlock_Parameters>( level->getStyle()->FindParams( BouncyBlock_AutoGen::getInstance() ) );

		if ( Params->Special.Hallway )
			Hallway( level, BL, TR );
	}

	void BouncyBlock_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void BouncyBlock_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	boost::shared_ptr<ObjectBase> BouncyBlock_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		return CreateAt( level, pos );
	}

	boost::shared_ptr<ObjectBase> BouncyBlock_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos )
	{
		AutoGen::CreateAt( level, pos );

		boost::shared_ptr<StyleData> Style = level->getStyle();
		boost::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		boost::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get BouncyBlock parameters
		boost::shared_ptr<BouncyBlock_Parameters> Params = boost::static_pointer_cast<BouncyBlock_Parameters>( piece->Style->FindParams( BouncyBlock_AutoGen::getInstance() ) );

		boost::shared_ptr<BouncyBlock> bblock;
		float Width = Params->Size.GetVal( pos );
		Vector2 size = Vector2( Width, Width );
		Vector2 offset = Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 0) ),
								  static_cast<float>( level->getRnd()->Rnd->Next(0, 0) - size.Y ) );
		float speed = Params->Speed.GetVal( pos );
		float SideDampening = Params->SideDampening.GetVal( pos );

		bblock = boost::static_pointer_cast<BouncyBlock>( level->getRecycle()->GetObject(ObjectType_BOUNCY_BLOCK, true) );
		bblock->Init( pos + offset, size, speed, level );
		bblock->SideDampening = SideDampening;
		bblock->getBlockCore()->BlobsOnTop = true;

		bblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		bblock->getBlockCore()->GenData.EdgeSafety = Params->EdgeSafety.GetVal(pos) * size.X;

		if ( piece->Style->RemoveBlockOnOverlap )
			bblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( bblock );

		return bblock;
	}
}
