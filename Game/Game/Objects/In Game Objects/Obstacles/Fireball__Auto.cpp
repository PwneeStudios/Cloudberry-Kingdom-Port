#include "Fireball__Auto.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Globals.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Core/Text/EzText.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
#include "Game/Objects/Game Objects/GameObjects/ExplodeBobs.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Tools/Recycler.h"
#include "Core/PhsxData.h"
#include "Core/Tools/Random.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void Fireball_Parameters::SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level )
	{
		AutoGen_Parameters::SetParameters( PieceSeed, level );

		std::shared_ptr<CloudberryKingdom::Upgrades> u = PieceSeed->getu();

		NumAngles = PieceSeed->Style_MASOCHISTIC ? 100 : 4;
		NumPeriods = PieceSeed->Style_MASOCHISTIC ? 2 : 1;
		NumOffsets = PieceSeed->Style_MASOCHISTIC ? 100 : 16;

		KeepUnused = Param( PieceSeed );
		if ( dynamic_cast<BobPhsxSpaceship*>( level->DefaultHeroType ) != 0 )
		{
			KeepUnused.SetVal( BobPhsxSpaceship::KeepUnused( u[ Upgrade_FIREBALL ] ) );
		}

		FillWeight = Param( PieceSeed, u[ Upgrade_FIREBALL ] );

		SetVal( SurvivalHallwaySpeed, DifficultyHelper::Interp19( 20, 45, u[ Upgrade_SPEED ] ) );

		if ( u[ Upgrade_FIREBALL ] > 0 )
			DoFill = true;

		float v = DifficultyHelper::Interp159( 800, 500, 200, u[ Upgrade_FIREBALL ] );
		if ( PieceSeed->Style_MASOCHISTIC )
			v *= .7f;

		BorderFillStep = v;

		// General difficulty
		BobWidthLevel = Param( PieceSeed );
		BobWidthLevel.SetVal( u[ Upgrade_FIREBALL ] );

		FireballMaxAngle = Param( PieceSeed );
		FireballMaxAngle.SetVal( DifficultyHelper::Interp159( .01f,.3f,.75f, u[ Upgrade_FIREBALL ] ) );

		FireballMinDist = Param( PieceSeed );
		FireballMinDist.SetVal( DifficultyHelper::Interp159( 700, 340, 120, u[ Upgrade_FIREBALL ] ) );

		MaxFireballDensity = Param( PieceSeed );
		MaxFireballDensity.SetVal( 4 * u[ Upgrade_FIREBALL ] );

		Period = Param( PieceSeed );
		Period.SetVal( DifficultyHelper::InterpRestrict159( 240, 195, 148,.7f * u[ Upgrade_SPEED ] + .3f * u[ Upgrade_FIREBALL ] ) );
	}

	void Fireball_Parameters::InitializeInstanceFields()
	{
		Arc = false;
		DoFill = false;
		BorderFillStep = Unset::Float;
		BorderTop = true;
		SurvivalHallwaySpeed = Unset::Float;
	}

const std::shared_ptr<Fireball_AutoGen> Fireball_AutoGen::instance = std::make_shared<Fireball_AutoGen>();

	const std::shared_ptr<Fireball_AutoGen> &Fireball_AutoGen::getInstance() const
	{
		return instance;
	}

	Fireball_AutoGen::Fireball_AutoGen()
	{
	}

	Fireball_AutoGen::Fireball_AutoGen()
	{
		Do_PreFill_2 = true;
	}

	std::shared_ptr<AutoGen_Parameters> Fireball_AutoGen::SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<Fireball_Parameters> Params = std::make_shared<Fireball_Parameters>();
		Params->SetParameters( data, level );

		return static_cast<AutoGen_Parameters*>( Params );
	}

	std::shared_ptr<ObjectBase> Fireball_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR )
	{
		AutoGen::CreateAt( level, pos, BL, TR );

		std::shared_ptr<StyleData> Style = level->getStyle();
		std::shared_ptr<RichLevelGenData> GenData = level->CurMakeData->GenData;
		std::shared_ptr<PieceSeedData> piece = level->CurMakeData->PieceSeed;

		// Get emitter parameters
		std::shared_ptr<Fireball_Parameters> Params = static_cast<Fireball_Parameters*>( level->Style_FIND_PARAMS( Fireball_AutoGen::getInstance() ) );

		int Period = static_cast<int>( Params->Period.GetVal( pos ) );
		int Offset = Params->ChooseOffset( Period, level->getRnd() );

		return 0;
	}

	void Fireball_AutoGen::inner( const std::shared_ptr<Fireball_Parameters> &Params, const std::shared_ptr<Level> &level, Vector2 pos, int i, LevelGeometry Geometry )
	{
		std::shared_ptr<Fireball> emitter = static_cast<Fireball*>( CreateAt( level, pos ) );

		float Speed = ( i == 0 ? 1 : -1 );

		if ( Params->Arc )
		{
			emitter->getCore()->StartData.Acceleration.Y = -abs(Speed) / 100;
		}

		float MaxAngle = Params->FireballMaxAngle.GetVal( pos );
		if ( level->Style_MASOCHISTIC )
			MaxAngle *= 1.25f;

		double Angle = Fireball_AutoGen::GetAngle( MaxAngle, Params->NumAngles, level->getRnd() );
		if ( Geometry == LevelGeometry_RIGHT )
			Angle += M_PI / 2;
		emitter->getCore()->StartData.Velocity = CoreMath::AngleToDir(Angle);

		if ( level->Style_MASOCHISTIC )
			emitter->Period = static_cast<int>( .9f * emitter->Period );

		float v = abs( 2 * emitter->getCore()->StartData.Position.Y / (.785f * emitter->Period) );
		emitter->getCore()->StartData.Velocity *= Speed * v / emitter->getCore()->StartData.Velocity.Y;
		float actual_v = emitter->getCore()->StartData.Velocity.Length();

		//emitter.Period = (int)(emitter.Period * actual_v / v);
		emitter->getCore()->StartData.Velocity *= v / actual_v;

		level->AddObject( emitter );

		emitter->getCore()->GenData.EnforceBounds = false;
	}

	void Fireball_AutoGen::BorderFill( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		std::shared_ptr<Fireball_Parameters> Params = static_cast<Fireball_Parameters*>( level->Style_FIND_PARAMS( Fireball_AutoGen::getInstance() ) );

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

	std::shared_ptr<Fireball_Parameters> Fireball_AutoGen::GetParams( const std::shared_ptr<Level> &level )
	{
		return static_cast<Fireball_Parameters*>( level->Style_FIND_PARAMS( Fireball_AutoGen::getInstance() ) );
	}

	std::shared_ptr<ObjectBase> Fireball_AutoGen::CreateAt( const std::shared_ptr<Level> &level, Vector2 pos )
	{
		std::shared_ptr<Fireball_Parameters> Params = GetParams( level );

		std::shared_ptr<Fireball> emitter = static_cast<Fireball*>( level->getRecycle()->GetObject(ObjectType_FIREBALL, true) );

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

	double Fireball_AutoGen::GetAngle( float MaxAngle, int NumAngles, const std::shared_ptr<Rand> &Rnd )
	{
		if ( NumAngles < 0 )
			return Rnd->Rnd->NextDouble() * 2 * MaxAngle - MaxAngle;
		else if ( NumAngles == 1 )
			return 0;
		else
			return Rnd->Rnd->Next( 0, NumAngles ) * 2 * MaxAngle / ( NumAngles - 1 ) - MaxAngle;
	}

	void Fireball_AutoGen::PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::PreFill_2( level, BL, TR );

		// Get Fireball parameters
		std::shared_ptr<Fireball_Parameters> Params = static_cast<Fireball_Parameters*>( level->Style_FIND_PARAMS( Fireball_AutoGen::getInstance() ) );

		int Length = level->CurPiece->PieceLength;

		if ( Params->DoStage2Fill && Params->DoFill )
			BorderFill( level, BL, TR );
	}

	void Fireball_AutoGen::Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR )
	{
		AutoGen::Cleanup_2( level, BL, TR );

		// Get Fireball parameters
		std::shared_ptr<Fireball_Parameters> Params = static_cast<Fireball_Parameters*>( level->Style_FIND_PARAMS( Fireball_AutoGen::getInstance() ) );
	}
}
