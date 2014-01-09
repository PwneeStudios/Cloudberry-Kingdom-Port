#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/Serpent__Auto.h"

#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/Serpent.h"
#include "Game/Tools/Recycler.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Core/Tools/Random.h"
#include "Game/Tools/Camera.h"

namespace CloudberryKingdom
{

	void Serpent_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		// General difficulty
		BobWidthLevel = Param( PieceSeed, u->Get( Upgrade_SERPENT ) );

		NumToMake = Param( PieceSeed, u->Get( Upgrade_SERPENT ) < 4.f ? 3.f : 2.f );

		SerpentStep = Param( PieceSeed, u->Get( Upgrade_SERPENT ) == 0 ? SerpentStepCutoff + 1 : DifficultyHelper::Interp159( 1650, 860, 350, u->Get( Upgrade_SERPENT ) ) );

		SerpentPeriod = Param( PieceSeed, __max( 70.f, 200.f - 9.f * u->Get( Upgrade_SPEED ) ) );
	}

	void Serpent_Parameters::InitializeInstanceFields()
	{
		SerpentStepCutoff = 1651;
	}

boost::shared_ptr<Serpent_AutoGen> Serpent_AutoGen::instance = boost::make_shared<Serpent_AutoGen>();

	const boost::shared_ptr<Serpent_AutoGen> &Serpent_AutoGen::getInstance()
	{
		return instance;
	}

	Serpent_AutoGen::Serpent_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	boost::shared_ptr<AutoGen_Parameters> Serpent_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<Serpent_Parameters> Params = boost::make_shared<Serpent_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void Serpent_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		BL += Vector2( -400, 0 );
		TR += Vector2( 350, 0 );

		// Get Serpent parameters
		boost::shared_ptr<Serpent_Parameters> Params = boost::static_pointer_cast<Serpent_Parameters>( level->getStyle()->FindParams( Serpent_AutoGen::getInstance() ) );

		float step = 5;

		Vector2 loc;
		if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
			loc = Vector2( BL.X + 600, ( TR.Y + BL.Y ) / 2 );
		else
			loc = Vector2( ( TR.X + BL.X ) / 2, BL.Y + 600 );

		while ( loc.X < TR.X && level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT || loc.Y < TR.Y && (level->getPieceSeed()->GeometryType == LevelGeometry_UP || level->getPieceSeed()->GeometryType == LevelGeometry_DOWN) )
		{
			step = level->getRnd()->RndFloat(Params->SerpentStep.GetVal(loc), Params->SerpentStep.GetVal(loc));

			Vector2 CamSize = level->getMainCamera()->GetSize();

			if ( step < Params->SerpentStepCutoff )
			{
				int period = static_cast<int>( Params->SerpentPeriod.GetVal( loc ) );
				int offset = level->getRnd()->Rnd->Next(period);
				int num = static_cast<int>( Params->NumToMake.GetVal( loc ) );

				// Create 2 serpents in this location, with offset perios.
				for ( int i = 0; i < num; i++ )
				{
					boost::shared_ptr<Serpent> serpent = boost::static_pointer_cast<Serpent>( level->getRecycle()->GetObject(ObjectType_SERPENT, true) );
					serpent->Init( loc, level );

					serpent->SetPeriod( period );

					serpent->Offset = static_cast<int>( offset + i * period / static_cast<float>( num ) );

					serpent->getCore()->GenData.LimitGeneralDensity = false;

					// Make sure we stay in bounds
					//Tools::EnsureBounds_X(serpent, TR, BL);

					level->AddObject( serpent );
				}
			}

			if ( level->getPieceSeed()->GeometryType == LevelGeometry_RIGHT )
				loc.X += step;
			else
				loc.Y += step;
		}
	}

	void Serpent_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		level->Cleanup_xCoord( ObjectType_SERPENT, 10 );
	}
}
