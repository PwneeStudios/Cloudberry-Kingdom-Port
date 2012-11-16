#include "BouncyBlock__Auto.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Globals.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Core/Text/EzText.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Tools/Recycler.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void BouncyBlock_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( dynamic_cast<BobPhsxSpaceship*>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u[ Upgrade_BOUNCY_BLOCK ] ) );
		}

		FillWeight = Param( PieceSeed, u[ Upgrade_BOUNCY_BLOCK ] );

		Speed = Param( PieceSeed );
		Speed_SET_VAL( DifficultyHelper::Interp( 45, 60, u[ Upgrade_BOUNCY_BLOCK ] ) );

		SideDampening = Param( PieceSeed );
		SideDampening.SetVal( DifficultyHelper::Interp159( .55f,.83f, 1.2f, u[ Upgrade_BOUNCY_BLOCK ] ) );

		Size = Param( PieceSeed );
		Size.SetVal( __max( 75, 105 - 1.85f * u[ Upgrade_BOUNCY_BLOCK ] ) );

		EdgeSafety = Param( PieceSeed );
		EdgeSafety.SetVal( __max( .01f, DifficultyHelper::Interp159( .4f,.3f,.05f, u[ Upgrade_BOUNCY_BLOCK ] ) ) );
	}

const std::shared_ptr<BouncyBlock_AutoGen> BouncyBlock_AutoGen::instance = std::make_shared<BouncyBlock_AutoGen>();

	const std::shared_ptr<BouncyBlock_AutoGen> &BouncyBlock_AutoGen::getInstance() const
	{
		return instance;
	}

	BouncyBlock_AutoGen::BouncyBlock_AutoGen()
	{
	}

	BouncyBlock_AutoGen::BouncyBlock_AutoGen()
	{
		Do_PreFill_1 = true;

		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> BouncyBlock_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<BouncyBlock_Parameters> Params = std::make_shared<BouncyBlock_Parameters>();
		Params->SetParameters( data, level );

		return static_cast<AutoGen_Parameters*>( Params );
	}

	void BouncyBlock_AutoGen::SetHallwaysBlockProperties( const std::shared_ptr<BouncyBlock> &block, const std::shared_ptr<Level> &level )
	{
		block->getCore()->GenData.Used = true;

		block->Init( block->getCore()->Data.Position, Vector2(150, 150), 80, level );
	}

	void BouncyBlock_AutoGen::Hallway( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		BL.X = level->FillBL.X;

		float x = BL.X;

		while ( x < TR.X )
		{
			std::shared_ptr<BouncyBlock> block;
			block = static_cast<BouncyBlock*>( CreateAt( level, Vector2( x, TR.Y - 300 ) ) );
			SetHallwaysBlockProperties( block, level );
			block = static_cast<BouncyBlock*>( CreateAt( level, Vector2( x, BL.Y + 300 ) ) );
			SetHallwaysBlockProperties( block, level );

			x += 2 * block->getBox()->Current->Size.X;
		}
	}

	void BouncyBlock_AutoGen::PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_1( level, BL, TR );

		std::shared_ptr<BouncyBlock_Parameters> Params = static_cast<BouncyBlock_Parameters*>( level->Style_FIND_PARAMS( BouncyBlock_AutoGen::getInstance() ) );

		if ( Params->Special.Hallway )
			Hallway( level, BL, TR );
	}

	void BouncyBlock_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void BouncyBlock_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	std::shared_ptr<ObjectBase> BouncyBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		return CreateAt( level, pos );
	}

	std::shared_ptr<ObjectBase> BouncyBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		AutoGen::CreateAt( level, pos );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get BouncyBlock parameters
		std::shared_ptr<BouncyBlock_Parameters> Params = static_cast<BouncyBlock_Parameters*>( piece->Style_FIND_PARAMS( BouncyBlock_AutoGen::getInstance() ) );

		std::shared_ptr<BouncyBlock> bblock;
		float Width = Params->Size.GetVal( pos );
		Vector2 size = Vector2( Width, Width );
		Vector2 offset = Vector2( level->getRnd()->Rnd->Next(0, 0), level->getRnd()->Rnd->Next(0, 0) - size.Y );
		float speed = Params->Speed_GET_VAL( pos );
		float SideDampening = Params->SideDampening.GetVal( pos );

		bblock = static_cast<BouncyBlock*>( level->getRecycle()->GetObject(ObjectType_BOUNCY_BLOCK, true) );
		bblock->Init( pos + offset, size, speed, level );
		bblock->SideDampening = SideDampening;
		bblock->getBlockCore()->BlobsOnTop = true;

		bblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		bblock->getBlockCore()->GenData.EdgeSafety = Params->EdgeSafety.GetVal(pos) * size.X;

		if ( piece->Style_REMOVE_BLOCK_ON_OVERLAP )
			bblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( bblock );

		return bblock;
	}
}
