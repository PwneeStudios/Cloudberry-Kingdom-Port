#include <global_header.h>



namespace CloudberryKingdom
{

	void Cloud_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( .62f * u->Get( Upgrade_CLOUD ) );

		Shiftiness = Param( PieceSeed );
		Shiftiness.SetVal( 1 + .33f * u->Get( Upgrade_CLOUD ) );

		Size = Param( PieceSeed );
		Size.SetVal( 2 - .1f * u->Get( Upgrade_CLOUD ) );
	}

const std::shared_ptr<Cloud_AutoGen> Cloud_AutoGen::instance = std::make_shared<Cloud_AutoGen>();

	const std::shared_ptr<Cloud_AutoGen> &Cloud_AutoGen::getInstance()
	{
		return instance;
	}

	Cloud_AutoGen::Cloud_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	std::shared_ptr<AutoGen_Parameters> Cloud_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<Cloud_Parameters> Params = std::make_shared<Cloud_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameter>( Params );
	}

	void Cloud_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void Cloud_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	std::shared_ptr<ObjectBase> Cloud_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		// Get Cloud parameters
		std::shared_ptr<Cloud_Parameters> Params = std::static_pointer_cast<Cloud_Parameter>( level->Style->FindParams( Cloud_AutoGen::getInstance() ) );

		// Make the new cloud
		pos += Vector2( level->getRnd()->Rnd->Next(0, 70), level->getRnd()->Rnd->Next(0, 70) );
		std::shared_ptr<Cloud> NewCloud = static_cast<Cloud*>( level->MySourceGame->Recycle->GetObject( ObjectType_CLOUD, true ) );

		NewCloud->Shiftiness = Params->Shiftiness.GetVal( pos );
		NewCloud->Init( pos, level );

		NewCloud->getCore()->GenData.RemoveIfUnused = true;

		if ( level->Style->RemoveBlockOnOverlap )
			NewCloud->getCore()->GenData.RemoveIfOverlap = true;

		level->AddObject( NewCloud );

		return NewCloud;
	}
}
