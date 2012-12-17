#include <global_header.h>

namespace CloudberryKingdom
{

	void ConveyorBlock_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{

		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		KeepUnused = Param( PieceSeed );
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_CONVEYOR ) ) );
		}

		FillWeight = Param( PieceSeed, u->Get( Upgrade_CONVEYOR ) * ( .5f + .5f * u->Get( Upgrade_CONVEYOR ) / 10 ) );

		Speed = Param( PieceSeed, DifficultyHelper::Interp( .04175f,.16f, u->Get( Upgrade_CONVEYOR ) ) * DifficultyHelper::Interp( 1, 1.55f, u->Get( Upgrade_SPEED ) ) );

		Width = Param( PieceSeed, DifficultyHelper::InterpRestrict19( 240, 60, u->Get( Upgrade_CONVEYOR ) ) );
	}

	boost::shared_ptr<ConveyorBlock_AutoGen> ConveyorBlock_AutoGen::instance = boost::make_shared<ConveyorBlock_AutoGen>();

	const boost::shared_ptr<ConveyorBlock_AutoGen> &ConveyorBlock_AutoGen::getInstance()
	{
		return instance;
	}

	ConveyorBlock_AutoGen::ConveyorBlock_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
	}

	boost::shared_ptr<AutoGen_Parameters> ConveyorBlock_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<ConveyorBlock_Parameters> Params = boost::make_shared<ConveyorBlock_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void ConveyorBlock_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void ConveyorBlock_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	boost::shared_ptr<ConveyorBlock_Parameters> ConveyorBlock_AutoGen::GetParams( const boost::shared_ptr<Level> &level )
	{
		return boost::static_pointer_cast<ConveyorBlock_Parameters>( level->getStyle()->FindParams( ConveyorBlock_AutoGen::getInstance() ) );
	}

	boost::shared_ptr<ObjectBase> ConveyorBlock_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		boost::shared_ptr<StyleData> Style = level->getStyle();
		boost::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		boost::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get ConveyorBlock parameters
		boost::shared_ptr<ConveyorBlock_Parameters> Params = GetParams( level );

		int Width = static_cast<int>( Params->Width.GetVal( pos ) );
		float Height = 60;
		Vector2 size = Vector2( static_cast<float>( Width ), static_cast<float>( Height ) );
		//float speed = Params.Speed.GetVal(pos);
		float speed = .35f * Params->Speed.GetVal( pos );

		speed *= -1; //level.Rnd.RndBit();

		boost::shared_ptr<ConveyorBlock> conveyblock = boost::static_pointer_cast<ConveyorBlock>( level->getRecycle()->GetObject(ObjectType_CONVEYOR_BLOCK, false) );
		conveyblock->Init( pos, size );
		conveyblock->Speed = speed;

		conveyblock->getBlockCore()->BlobsOnTop = true;

		conveyblock->getBlockCore()->Decide_RemoveIfUnused(Params->KeepUnused.GetVal(pos), level->getRnd());
		conveyblock->getBlockCore()->GenData.EdgeSafety = static_cast<float>( GenData->Get(DifficultyParam_EDGE_SAFETY, pos) );

		if ( level->getStyle()->RemoveBlockOnOverlap )
			conveyblock->getBlockCore()->GenData.RemoveIfOverlap = true;

		level->AddBlock( conveyblock );

		return conveyblock;
	}
}
