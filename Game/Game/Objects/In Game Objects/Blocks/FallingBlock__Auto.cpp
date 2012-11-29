#include <global_header.h>
namespace CloudberryKingdom
{

	void FallingBlock_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( std::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
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

const std::shared_ptr<FallingBlock_AutoGen> FallingBlock_AutoGen::instance = std::make_shared<FallingBlock_AutoGen>();

	const std::shared_ptr<FallingBlock_AutoGen> &FallingBlock_AutoGen::getInstance()
	{
		return instance;
	}

	FallingBlock_AutoGen::FallingBlock_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> FallingBlock_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<FallingBlock_Parameters> Params = std::make_shared<FallingBlock_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameter>( Params );
	}

	void FallingBlock_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void FallingBlock_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	std::shared_ptr<ObjectBase> FallingBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get FallingBlock parameters
		std::shared_ptr<FallingBlock_Parameters> Params = std::static_pointer_cast<FallingBlock_Parameter>( level->Style->FindParams( FallingBlock_AutoGen::getInstance() ) );

		std::shared_ptr<FallingBlock> fblock;
		float Width = Params->Width.GetVal( pos );
		Vector2 size = Vector2( Width, Width );
		Vector2 offset = Vector2( level->getRnd()->Rnd->Next(0, 0), level->getRnd()->Rnd->Next(0, 0) - size.Y );

		fblock = static_cast<FallingBlock*>( level->getRecycle()->GetObject(ObjectType_FALLING_BLOCK, true) );
		int Life = static_cast<int>( Params->Delay.GetVal( pos ) );
		fblock->Init( pos + offset, size, Life, level );
		fblock->getBlockCore()->BlobsOnTop = true;

		fblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		fblock->getBlockCore()->GenData.EdgeSafety = GenData->Get(DifficultyParam_EDGE_SAFETY, pos);

		if ( level->getRnd()->Rnd->NextDouble() < Params->AngryRatio.GetVal(pos) / 100 )
		{
			// Make angry
			fblock->Thwomp = true;
			fblock->AngryMaxSpeed = Params->AngrySpeed.GetVal( pos );
			fblock->AngryAccel = Vector2( 0, Params->AngryAccel.GetVal( pos ) / 100 );
		}

		if ( level->Style->RemoveBlockOnOverlap )
			fblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( fblock );

		return fblock;
	}
}
