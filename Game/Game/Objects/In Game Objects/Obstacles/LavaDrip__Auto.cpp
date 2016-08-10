#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/LavaDrip__Auto.h"

#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/LavaDrip.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Core/Tools/Random.h"
#include "Game/Tools/Camera.h"

namespace CloudberryKingdom
{

	void LavaDrip_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		// General difficulty
		BobWidthLevel = Param( PieceSeed, u->Get( Upgrade_LAVA_DRIP ) );

		LavaDripStep = Param( PieceSeed, u->Get( Upgrade_LAVA_DRIP ) == 0 ? LavaDripStepCutoff + 1 : DifficultyHelper::Interp159( 1450, 550, 250, u->Get( Upgrade_LAVA_DRIP ) ) );

		Length = VectorParam( PieceSeed, Vector2( 1400 - 100 * u->Get( Upgrade_LAVA_DRIP ), 1400 + 80 * u->Get( Upgrade_LAVA_DRIP ) ) );

		Speed = Param( PieceSeed, __min( 3, 1 + .043f * u->Get( Upgrade_SPEED ) + .017f * u->Get( Upgrade_LAVA_DRIP ) ) );
	}

	void LavaDrip_Parameters::InitializeInstanceFields()
	{
		LavaDripStepCutoff = 1499;
	}

	boost::shared_ptr<LavaDrip_AutoGen> LavaDrip_AutoGen::instance = boost::make_shared<LavaDrip_AutoGen>();

	const boost::shared_ptr<LavaDrip_AutoGen> &LavaDrip_AutoGen::getInstance()
	{
		return instance;
	}

	LavaDrip_AutoGen::LavaDrip_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	boost::shared_ptr<AutoGen_Parameters> LavaDrip_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<LavaDrip_Parameters> Params = boost::make_shared<LavaDrip_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void LavaDrip_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		BL += Vector2( -400, 0 );
		TR += Vector2( 350, 0 );

		// Get LavaDrip parameters
		boost::shared_ptr<LavaDrip_Parameters> Params = boost::static_pointer_cast<LavaDrip_Parameters>( level->getStyle()->FindParams( LavaDrip_AutoGen::getInstance() ) );

		float step = 5;

		Vector2 loc;
		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			loc = Vector2( BL.X + 600, ( TR.Y + BL.Y ) / 2 );
		else
			loc = Vector2( ( TR.X + BL.X ) / 2, BL.Y + 600 );

		while ( loc.X < TR.X && level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT || loc.Y < TR.Y && (level->getPieceSeed()->GeometryType == LevelGeometry_UP || level->getPieceSeed()->GeometryType == LevelGeometry_DOWN) )
		{
			step = level->getRnd()->RndFloat(Params->LavaDripStep.GetVal(loc), Params->LavaDripStep.GetVal(loc));

			Vector2 CamSize = level->getMainCamera()->GetSize();

			if ( step < Params->LavaDripStepCutoff )
			{
				boost::shared_ptr<LavaDrip> LavaDrip_Renamed = boost::static_pointer_cast<LavaDrip>( level->getRecycle()->GetObject(ObjectType_LAVA_DRIP, true) );
				LavaDrip_Renamed->BoxSize.Y = Params->Length.RndFloat( loc, level->getRnd() );
				LavaDrip_Renamed->Init( loc, level );

				int speed = static_cast<int>( Params->Speed.GetVal( loc ) );
				LavaDrip_Renamed->SetPeriod( static_cast<float>( speed ) );

				LavaDrip_Renamed->Offset = level->getRnd()->Rnd->Next(LavaDrip_Renamed->Period);

				LavaDrip_Renamed->getCore()->GenData.LimitGeneralDensity = false;

				level->AddObject( LavaDrip_Renamed );
			}

			if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
				loc.X += step;
			else
				loc.Y += step;
		}
	}

	void LavaDrip_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}
}
