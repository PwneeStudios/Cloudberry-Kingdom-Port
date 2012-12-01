#include <global_header.h>
namespace CloudberryKingdom
{

	void LavaDrip_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

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

const std::shared_ptr<LavaDrip_AutoGen> LavaDrip_AutoGen::instance = std::make_shared<LavaDrip_AutoGen>();

	const std::shared_ptr<LavaDrip_AutoGen> &LavaDrip_AutoGen::getInstance()
	{
		return instance;
	}

	LavaDrip_AutoGen::LavaDrip_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	std::shared_ptr<AutoGen_Parameters> LavaDrip_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<LavaDrip_Parameters> Params = std::make_shared<LavaDrip_Parameters>();
		Params->SetParameters( data, level );

		return std::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	void LavaDrip_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		BL += Vector2( -400, 0 );
		TR += Vector2( 350, 0 );

		// Get LavaDrip parameters
		std::shared_ptr<LavaDrip_Parameters> Params = std::static_pointer_cast<LavaDrip_Parameters>( level->Style->FindParams( LavaDrip_AutoGen::getInstance() ) );

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
//C# TO C++ CONVERTER NOTE: The variable LavaDrip was renamed since it is named the same as a user-defined type:
				std::shared_ptr<LavaDrip> LavaDrip_Renamed = std::static_pointer_cast<LavaDrip>( level->getRecycle()->GetObject(ObjectType_LAVA_DRIP, true) );
				LavaDrip_Renamed->BoxSize.Y = Params->Length.RndFloat( loc, level->getRnd() );
				LavaDrip_Renamed->Init( loc, level );

				int speed = static_cast<int>( Params->Speed_GET_VAL( loc ) );
				LavaDrip_Renamed->SetPeriod( speed );

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

	void LavaDrip_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );
	}
}
