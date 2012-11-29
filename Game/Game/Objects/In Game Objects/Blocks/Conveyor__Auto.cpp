#include <global_header.h>
namespace CloudberryKingdom
{

	void ConveyorBlock_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( dynamic_cast<BobPhsxSpaceship*>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_CONVEYOR ) ) );
		}

		FillWeight = Param( PieceSeed, u->Get( Upgrade_CONVEYOR ) * ( .5f + .5f * u->Get( Upgrade_CONVEYOR ) / 10 ) );

		Speed = Param( PieceSeed, DifficultyHelper::Interp( .04175f,.16f, u->Get( Upgrade_CONVEYOR ) ) * DifficultyHelper::Interp( 1, 1.55f, u->Get( Upgrade_SPEED ) ) );

		Width = Param( PieceSeed, DifficultyHelper::InterpRestrict19( 240, 60, u->Get( Upgrade_CONVEYOR ) ) );
	}

const std::shared_ptr<ConveyorBlock_AutoGen> ConveyorBlock_AutoGen::instance = std::make_shared<ConveyorBlock_AutoGen>();

	const std::shared_ptr<ConveyorBlock_AutoGen> &ConveyorBlock_AutoGen::getInstance()
	{
		return instance;
	}

	ConveyorBlock_AutoGen::ConveyorBlock_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
	}

	std::shared_ptr<AutoGen_Parameters> ConveyorBlock_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<ConveyorBlock_Parameters> Params = std::make_shared<ConveyorBlock_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameter>( Params );
	}

	void ConveyorBlock_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void ConveyorBlock_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	std::shared_ptr<ConveyorBlock_Parameters> ConveyorBlock_AutoGen::GetParams( const std::shared_ptr<Level> &level )
	{
		return std::static_pointer_cast<ConveyorBlock_Parameter>( level->Style->FindParams( ConveyorBlock_AutoGen::getInstance() ) );
	}

	std::shared_ptr<ObjectBase> ConveyorBlock_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get ConveyorBlock parameters
		std::shared_ptr<ConveyorBlock_Parameters> Params = GetParams( level );

		int Width = static_cast<int>( Params->Width.GetVal( pos ) );
		float Height = 60;
		Vector2 size = Vector2( Width, Height );
		//float speed = Params.Speed.GetVal(pos);
		float speed = .35f * Params->Speed_GET_VAL( pos );

		speed *= -1; //level.Rnd.RndBit();

		std::shared_ptr<ConveyorBlock> conveyblock = static_cast<ConveyorBlock*>( level->getRecycle()->GetObject(ObjectType_CONVEYOR_BLOCK, false) );
		conveyblock->Init( pos, size );
		conveyblock->Speed = speed;

		conveyblock->getBlockCore()->BlobsOnTop = true;

		conveyblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		conveyblock->getBlockCore()->GenData.EdgeSafety = GenData->Get(DifficultyParam_EDGE_SAFETY, pos);

		if ( level->Style_REMOVE_BLOCK_ON_OVERLAP )
			conveyblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( conveyblock );

		return conveyblock;
	}
}
