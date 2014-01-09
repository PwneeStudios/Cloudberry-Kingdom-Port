#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/Cloud__Auto.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Core/Tools/Random.h"
#include "Game/Games/GameType.h"

namespace CloudberryKingdom
{

	void Cloud_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		FillWeight = Param( PieceSeed );
		FillWeight.SetVal( .62f * u->Get( Upgrade_CLOUD ) );

		Shiftiness = Param( PieceSeed );
		Shiftiness.SetVal( 1 + .33f * u->Get( Upgrade_CLOUD ) );

		Size = Param( PieceSeed );
		Size.SetVal( 2 - .1f * u->Get( Upgrade_CLOUD ) );
	}

	boost::shared_ptr<Cloud_AutoGen> Cloud_AutoGen::instance = boost::make_shared<Cloud_AutoGen>();

	const boost::shared_ptr<Cloud_AutoGen> &Cloud_AutoGen::getInstance()
	{
		return instance;
	}

	Cloud_AutoGen::Cloud_AutoGen()
	{
		Do_WeightedPreFill_1 = true;
		//Generators.AddGenerator(this);
	}

	boost::shared_ptr<AutoGen_Parameters> Cloud_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<Cloud_Parameters> Params = boost::make_shared<Cloud_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void Cloud_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );
	}

	void Cloud_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}

	boost::shared_ptr<ObjectBase> Cloud_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		// Get Cloud parameters
		boost::shared_ptr<Cloud_Parameters> Params = boost::static_pointer_cast<Cloud_Parameters>( level->getStyle()->FindParams( Cloud_AutoGen::getInstance() ) );

		// Make the new cloud
		pos += Vector2( static_cast<float>( level->getRnd()->Rnd->Next(0, 70) ),
						static_cast<float>( level->getRnd()->Rnd->Next(0, 70) ) );
		boost::shared_ptr<Cloud> NewCloud = boost::static_pointer_cast<Cloud>( level->MySourceGame->Recycle->GetObject( ObjectType_CLOUD, true ) );

		NewCloud->Shiftiness = Params->Shiftiness.GetVal( pos );
		NewCloud->Init( pos, level );

		NewCloud->getCore()->GenData.RemoveIfUnused = true;

		if ( level->getStyle()->RemoveBlockOnOverlap )
			NewCloud->getCore()->GenData.RemoveIfOverlap = true;

		level->AddObject( NewCloud );

		return NewCloud;
	}
}
