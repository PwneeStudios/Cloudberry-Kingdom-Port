#include <small_header.h>
#include "Game/Objects/In Game Objects/Obstacles/Fireball__Auto.h"

#include "Core/PhsxData.h"
#include "Core/Tools/CoreMath.h"
#include "Core/Tools/Random.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Unset.h"

#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Tools/Camera.h"
#include "Game/Level/LevelPiece.h"

namespace CloudberryKingdom
{

	void Fireball_Parameters::SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		boost::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		NumAngles = PieceSeed->Style->Masochistic ? 100 : 4;
		NumPeriods = PieceSeed->Style->Masochistic ? 2 : 1;
		NumOffsets = PieceSeed->Style->Masochistic ? 100 : 16;

		KeepUnused = Param( PieceSeed );
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u->Get( Upgrade_FIREBALL ) ) );
		}

		FillWeight = Param( PieceSeed, u->Get( Upgrade_FIREBALL ) );

		SetVal( SurvivalHallwaySpeed, DifficultyHelper::Interp19( 20, 45, u->Get( Upgrade_SPEED ) ) );

		if ( u->Get( Upgrade_FIREBALL ) > 0 )
			DoFill = true;

		float v = DifficultyHelper::Interp159( 800, 500, 200, u->Get( Upgrade_FIREBALL ) );
		if ( PieceSeed->Style->Masochistic )
			v *= .7f;

		BorderFillStep = v;

		// General difficulty
		BobWidthLevel = Param( PieceSeed );
		BobWidthLevel.SetVal( u->Get( Upgrade_FIREBALL ) );

		FireballMaxAngle = Param( PieceSeed );
		FireballMaxAngle.SetVal( DifficultyHelper::Interp159( .01f,.3f,.75f, u->Get( Upgrade_FIREBALL ) ) );

		FireballMinDist = Param( PieceSeed );
		FireballMinDist.SetVal( DifficultyHelper::Interp159( 700, 340, 120, u->Get( Upgrade_FIREBALL ) ) );

		MaxFireballDensity = Param( PieceSeed );
		MaxFireballDensity.SetVal( 4 * u->Get( Upgrade_FIREBALL ) );

		Period = Param( PieceSeed );
		Period.SetVal( DifficultyHelper::InterpRestrict159( 240, 195, 148,.7f * u->Get( Upgrade_SPEED ) + .3f * u->Get( Upgrade_FIREBALL ) ) );
	}

	void Fireball_Parameters::InitializeInstanceFields()
	{
		Arc = false;
		DoFill = false;
		BorderFillStep = Unset::Float;
		BorderTop = true;
		SurvivalHallwaySpeed = Unset::Float;
	}

boost::shared_ptr<Fireball_AutoGen> Fireball_AutoGen::instance = boost::make_shared<Fireball_AutoGen>();

	const boost::shared_ptr<Fireball_AutoGen> &Fireball_AutoGen::getInstance()
	{
		return instance;
	}

	Fireball_AutoGen::Fireball_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	boost::shared_ptr<AutoGen_Parameters> Fireball_AutoGen::SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<Fireball_Parameters> Params = boost::make_shared<Fireball_Parameters>();
		Params->SetParameters( data, level );

		return boost::static_pointer_cast<AutoGen_Parameters>( Params );
	}

	boost::shared_ptr<ObjectBase> Fireball_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		boost::shared_ptr<StyleData> Style = level->getStyle();
		boost::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		boost::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get emitter parameters
		boost::shared_ptr<Fireball_Parameters> Params = boost::static_pointer_cast<Fireball_Parameters>( level->getStyle()->FindParams( Fireball_AutoGen::getInstance() ) );

		int Period = static_cast<int>( Params->Period.GetVal( pos ) );
		int Offset = Params->ChooseOffset( Period, level->getRnd() );

		return 0;
	}

	void Fireball_AutoGen::inner( const boost::shared_ptr<Fireball_Parameters> &Params, const boost::shared_ptr<Level> &level, Vector2 pos, int i, LevelGeometry Geometry )
	{
		boost::shared_ptr<Fireball> emitter = boost::static_pointer_cast<Fireball>( CreateAt( level, pos ) );

		float Speed = ( i == 0.f ? 1.f : -1.f );

		if ( Params->Arc )
		{
			emitter->getCore()->StartData.Acceleration.Y = -fabs(Speed) / 100;
		}

		float MaxAngle = Params->FireballMaxAngle.GetVal( pos );
		if ( level->getStyle()->Masochistic )
			MaxAngle *= 1.25f;

		double Angle = Fireball_AutoGen::GetAngle( MaxAngle, Params->NumAngles, level->getRnd() );
		if ( Geometry == LevelGeometry_RIGHT )
			Angle += M_PI / 2;
		emitter->getCore()->StartData.Velocity = CoreMath::AngleToDir(Angle);

		if ( level->getStyle()->Masochistic )
			emitter->Period = static_cast<int>( .9f * emitter->Period );

		float v = fabs( 2 * emitter->getCore()->StartData.Position.Y / (.785f * emitter->Period) );
		emitter->getCore()->StartData.Velocity *= Speed * v / emitter->getCore()->StartData.Velocity.Y;
		float actual_v = emitter->getCore()->StartData.Velocity.Length();

		//emitter.Period = (int)(emitter.Period * actual_v / v);
		emitter->getCore()->StartData.Velocity *= v / actual_v;

		level->AddObject( emitter );

		emitter->getCore()->GenData.EnforceBounds = false;
	}

	void Fireball_AutoGen::BorderFill( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		boost::shared_ptr<Fireball_Parameters> Params = boost::static_pointer_cast<Fireball_Parameters>( level->getStyle()->FindParams( Fireball_AutoGen::getInstance() ) );

		LevelGeometry Geometry = level->CurMakeData->PieceSeed->GeometryType;

		Vector2 pos = BL;

		float shift = -50;

		for ( int i = 0; i <= 1; i++ )
		{
			if ( !Params->BorderTop && i == 1 )
				continue;

			if ( Geometry == LevelGeometry_RIGHT )
			{
				shift = -250;
				pos.Y = ( i == 0 ? level->getMainCamera()->BL.Y + shift : level->getMainCamera()->TR.Y - shift );

				pos.X = BL.X + Params->BorderFillStep / 2;
				while ( pos.X < TR.X + 400 )
				{
					int n = level->getRnd()->RndInt(1, 3);
					for ( int q = 0; q < n; q++ )
						inner( Params, level, pos, i, Geometry );
					pos.X += n * Params->BorderFillStep;
				}
			}
			else
			{
				pos.X = ( i == 0 ? level->getMainCamera()->BL.X + shift : level->getMainCamera()->TR.X - shift );
				for ( pos.Y = BL.Y; pos.Y < TR.Y; pos.Y += Params->BorderFillStep )
					inner( Params, level, pos, i, Geometry );
			}
		}
	}

	boost::shared_ptr<Fireball_Parameters> Fireball_AutoGen::GetParams( const boost::shared_ptr<Level> &level )
	{
		return boost::static_pointer_cast<Fireball_Parameters>( level->getStyle()->FindParams( Fireball_AutoGen::getInstance() ) );
	}

	boost::shared_ptr<ObjectBase> Fireball_AutoGen::CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos )
	{
		boost::shared_ptr<Fireball_Parameters> Params = GetParams( level );

		boost::shared_ptr<Fireball> emitter = boost::static_pointer_cast<Fireball>( level->getRecycle()->GetObject(ObjectType_FIREBALL, true) );

		emitter->Init( PhsxData(), level );

		emitter->getCore()->Data.Position = pos;
		emitter->getCore()->StartData.Position = pos;

		emitter->Period = ( level->getRnd()->Rnd->Next(Params->NumPeriods - 1) + 1 ) * static_cast<int>(Params->Period.GetVal(pos));

		if ( Params->NumOffsets < 0 )
			emitter->Offset = level->getRnd()->Rnd->Next(emitter->Period);
		else
			emitter->Offset = level->getRnd()->Rnd->Next(0, Params->NumOffsets) * emitter->Period / Params->NumOffsets;

		return emitter;
	}

	double Fireball_AutoGen::GetAngle( float MaxAngle, int NumAngles, const boost::shared_ptr<Rand> &Rnd )
	{
		if ( NumAngles < 0 )
			return Rnd->Rnd->NextDouble() * 2 * MaxAngle - MaxAngle;
		else if ( NumAngles == 1 )
			return 0;
		else
			return Rnd->Rnd->Next( 0, NumAngles ) * 2 * MaxAngle / ( NumAngles - 1 ) - MaxAngle;
	}

	void Fireball_AutoGen::PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get Fireball parameters
		boost::shared_ptr<Fireball_Parameters> Params = boost::static_pointer_cast<Fireball_Parameters>( level->getStyle()->FindParams( Fireball_AutoGen::getInstance() ) );

		int Length = level->CurPiece->PieceLength;

		if ( Params->DoStage2Fill && Params->DoFill )
			BorderFill( level, BL, TR );
	}

	void Fireball_AutoGen::Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		// Get Fireball parameters
		boost::shared_ptr<Fireball_Parameters> Params = boost::static_pointer_cast<Fireball_Parameters>( level->getStyle()->FindParams( Fireball_AutoGen::getInstance() ) );
	}
}
