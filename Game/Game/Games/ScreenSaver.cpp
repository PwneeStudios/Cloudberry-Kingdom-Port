#include <global_header.h>

#include "Hacks/List.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	ScreenSaver::ConstructorPressAListenerHelper::ConstructorPressAListenerHelper( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	void ScreenSaver::ConstructorPressAListenerHelper::Apply()
	{
		Tools::CurGameData->FadeToBlack( .0275f );
		Tools::SongWad->FadeOut();
		ss->DoBackgroundPhsx = false;

		Tools::CurGameData->WaitThenDo( 55, std::make_shared<ConstructorPressAListenerHelperHelper>( ss ) );

		ss->PressA_Listener->Release();
		if ( ss->PressA != 0 )
			ss->PressA->Kill( true );
	}

	ScreenSaver::ScreenSaverReleaseHelper::ScreenSaverReleaseHelper( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	void ScreenSaver::ScreenSaverReleaseHelper::Apply()
	{
		ss->Release();
	}

	ScreenSaver::ConstructorPressAListenerHelperHelper::ConstructorPressAListenerHelperHelper( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	void ScreenSaver::ConstructorPressAListenerHelperHelper::Apply()
	{
		Tools::CurGameData = CloudberryKingdomGame::TitleGameFactory->Make();
		Tools::CurGameData->FadeIn( .0275f );
		Tools::AddToDo( std::make_shared<ScreenSaverReleaseHelper>( ss ) );
	}

	ScreenSaver::OnSwapLambda::OnSwapLambda()
	{
	}

	void ScreenSaver::OnSwapLambda::Apply( const std::shared_ptr<LevelSeedData> &data )
	{
		Tools::ShowLoadingScreen = false;
		Tools::TheGame->LogoScreenPropUp = false;
		Tools::Write( _T( "+++++++++++++++++++ Ending screensave load..." ) );
	}

	ScreenSaver::GetSeedFuncLambdaSS::GetSeedFuncLambdaSS( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	std::shared_ptr<LevelSeedData> ScreenSaver::GetSeedFuncLambdaSS::Apply( const int &index )
	{
		return ss->Make( index );
	}
	
	ScreenSaver::ConstructorOnSwapToLevelHelper::ConstructorOnSwapToLevelHelper( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	void ScreenSaver::ConstructorOnSwapToLevelHelper::Apply( const int &index )
	{
		// Hide the 'Press A to start' text after the first level
		if ( index > 0 )
			ss->PressA->Hid = true;

		Tools::CurLevel->SuppressSounds = true;

		Tools::CurLevel->WatchComputer( false ); // Watch the computer
		Tools::CurGameData->PhsxStepsToDo += 1; // Skip beginning
		Tools::CurGameData->SuppressSoundForExtraSteps = true;
		ss->Duration = 10000;

		bool First = index == 0;
		//bool First = true;

		if ( ss->ForTrailer )
		{
			BobVec Bobs = Tools::CurLevel->Bobs;
			for ( int i = 0; i < 4; i++ )
				if ( static_cast<int>( Bobs.size() ) > i )
					Bobs[ i ]->SetColorScheme( ColorSchemeManager::ColorSchemes[ i ] );
		}

		if ( First )
		{
			Tools::CurGameData->SuppressSongInfo = true;

			Tools::SongWad->FadeOut();

			Tools::CurLevel->Bobs[ 0 ]->SetColorScheme( ColorSchemeManager::ComputerColorSchemes[ 0 ] );

			Tools::CurLevel->Bobs[ 0 ]->PlayerObject->EnqueueAnimation( 0, 0, true, true, false, 100 );

			ss->pos_t = ss->zoom_t = 0;
			Tools::CurGameData->FadeIn( 0 );
		}

		// Add 'Press (A) to start' text
		if ( index == 0 )
		{
			Tools::CurGameData->WaitThenDo( MandatoryWatchLength_Initial + InitialDarkness - 3, std::make_shared<MakePressALambda>( ss, ss->ForTrailer ), true );

			Tools::CurGameData->WaitThenDo( getMandatoryWatchLength() + InitialDarkness - 3, std::make_shared<AddListenerLambda>(ss), true );
		}
	}

	ScreenSaver::MakePressALambda::MakePressALambda( const std::shared_ptr<ScreenSaver> &ss, bool ForTrailer )
	{
		this->ss = ss;
		this->ForTrailer = ForTrailer;
	}

	void ScreenSaver::MakePressALambda::Apply()
	{
		UserPowers::Set( UserPowers::CanSkipScreensaver, true );

	#if defined(PC_VERSION)
		ss->PressA = MakeMagic( GUI_Text, ( Localization::Words_PRESS_ANY_KEY, Vector2( 0, -865 ), true ) );
	#else
		ss->PressA = MakeMagic( GUI_Text, ( Localization::Words_PRESS_ANY_KEY, Vector2( 0, -865 ), true ) );
	#endif
		ss->PressA->MyText->setScale( ss->PressA->MyText->getScale() * .68f );
		ss->PressA->PreventRelease = true;
		ss->PressA->FixedToCamera = true;
		ss->PressA->Oscillate_Renamed = true;
		if ( !ForTrailer )
			Tools::CurGameData->AddGameObject( ss->PressA );
	}

	ScreenSaver::AddListenerLambda::AddListenerLambda( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	void ScreenSaver::AddListenerLambda::Apply()
	{
		ss->PressA_Listener = MakeMagic( Listener, ( ControllerButtons_A, std::make_shared<ConstructorPressAListenerHelper>( ss ) ) );
		ss->PressA_Listener->PreventRelease = true;
		ss->PressA_Listener->setControl( -2 );
		Tools::CurGameData->AddGameObject( ss->PressA_Listener );
	}

	ScreenSaver::StartMusicLambda::StartMusicLambda()
	{
	}

	void ScreenSaver::StartMusicLambda::Apply()
	{
		// Start the music
		Tools::SongWad->Unpause();
	}

	ScreenSaver::RecordScratchLambda::RecordScratchLambda()
	{
	}

	void ScreenSaver::RecordScratchLambda::Apply()
	{
		Tools::SoundWad->FindByName( _T( "Record_Scratch" ) )->Play();
	}

	ScreenSaver::WindLambda::WindLambda( const std::shared_ptr<FancyVector2> &wind_t )
	{
		this->wind_t = wind_t;
	}

	void ScreenSaver::WindLambda::Apply()
	{
		wind_t->LerpTo( 1, 40 );
	}

	ScreenSaver::PosLerpToLambda::PosLerpToLambda( const std::shared_ptr<FancyVector2> &pos_t, int zoomout_length, LerpStyle style )
	{
		this->pos_t = pos_t;
		this->zoomout_length = zoomout_length;
		this->style = style;
	}

	void ScreenSaver::PosLerpToLambda::Apply()
	{
		pos_t->LerpTo( 1, zoomout_length + 6, style );
	}

	ScreenSaver::ZoomLerpToLambda::ZoomLerpToLambda( const std::shared_ptr<FancyVector2> &zoom_t, int zoomout_length, LerpStyle style )
	{
		this->zoom_t = zoom_t;
		this->zoomout_length = zoomout_length;
		this->style = style;
	}

	void ScreenSaver::ZoomLerpToLambda::Apply()
	{
		zoom_t->LerpTo( 1, zoomout_length, style );
	}

	ScreenSaver::SigmoidLambda::SigmoidLambda( const std::shared_ptr<FancyVector2> &zoom_t )
	{
		this->zoom_t = zoom_t;
	}

	void ScreenSaver::SigmoidLambda::Apply()
	{
		zoom_t->LerpTo( .6f, 90, LerpStyle_SIGMOID );
	}

	ScreenSaver::FadeInLambda::FadeInLambda( const std::shared_ptr<Level> &lvl, float InitialFadeInSpeed )
	{
		this->lvl = lvl;
		this->InitialFadeInSpeed = InitialFadeInSpeed;
	}

	void ScreenSaver::FadeInLambda::Apply()
	{
		lvl->MyGame->FadeIn( InitialFadeInSpeed );
	}

	ScreenSaver::MultiplayerBlobsMyModParamsHelper::MultiplayerBlobsMyModParamsHelper( const std::shared_ptr<ScreenSaver> &ss )
	{
		this->ss = ss;
	}

	void ScreenSaver::MultiplayerBlobsMyModParamsHelper::Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p )
	{
		// ->Style->FindParams
		std::shared_ptr<FlyingBlob_Parameters> GParams = std::static_pointer_cast<FlyingBlob_Parameters>( p->Style->FindParams( FlyingBlob_AutoGen::getInstance() ) );
		GParams->KeepUnused.SetVal( ss->MyLevel->getRnd()->RndBool(.5f) ? 0 : ss->MyLevel->getRnd()->RndFloat(0,.06f) );
		GParams->FillWeight.SetVal( 100 );
		GParams->Period.SetVal( 115 );
		GParams->Range.SetVal( 600 );
	}

	void ScreenSaver::ForTrailerParams()
	{
		ForTrailer = true;

		Bungee = false;
		AllHeroes = true;
		Difficulty = 4;
		Paths = 1;
		FixedHero = BobPhsxNormal::getInstance();
		FixedTileSet = TileSet::Get( _T( "sea" ) );

		InitialFadeInSpeed = 1;
		InitialDarkness = 0;
		PartialZoomOut += 260;
		FullZoomOut += 260;
		KillCapeDelay += 260;
		InitialDelay += 0;

		//InitialZoom = .45f;
		InitialZoom = 1;
	}

	void ScreenSaver::Init()
	{
		StringWorldGameData::Init();

		Tools::WorldMap = Tools::CurGameData = shared_from_this();
		Tools::CurLevel = this->MyLevel;
	}

	const int ScreenSaver::getMandatoryWatchLength()
	{
		if ( UserPowers::CanSkipScreensaver )
			return 0;
		else
			return MandatoryWatchLength_Initial;
	}

	int ScreenSaver::InitialDarkness = 30;

	ScreenSaver::ScreenSaver() :
		InitialFadeInSpeed( 0 ), ForTrailer( false ), Bungee( false ), AllHeroes( false ), Difficulty( 0 ), Paths( 0 ), InitialZoom( 0 )
	{
		// See ScreenSaver_Construct.

		/*InitializeInstanceFields();
		Constructor();*/
	}

	ScreenSaver::ScreenSaver( bool ForTrailer ) :
		InitialFadeInSpeed( 0 ), ForTrailer( false ), Bungee( false ), AllHeroes( false ), Difficulty( 0 ), Paths( 0 ), InitialZoom( 0 )
	{
		assert( !"Should not be called." );
		/*InitializeInstanceFields();
		this->ForTrailer = ForTrailer;
		if ( ForTrailer )
			ForTrailerParams();
		Constructor();*/
	}

	void ScreenSaver::Constructor()
	{
		WaitLengthToOpenDoor_FirstLevel = 10 + InitialDarkness - 3;

		Tools::TheGame->LogoScreenPropUp = true;
		Tools::Write( _T( "+++++++++++++++++++ Beginning screensave load..." ) );

		this->GetSeedFunc = std::make_shared<GetSeedFuncLambdaSS>( std::static_pointer_cast<ScreenSaver>( shared_from_this() ) );

		OnSwapToFirstLevel->Add( std::make_shared<OnSwapLambda>() );

		OnSwapToLevel->Add( std::make_shared<ConstructorOnSwapToLevelHelper>( std::static_pointer_cast<ScreenSaver>( shared_from_this() ) ) );
	}

	void ScreenSaver::Release()
	{
		StringWorldGameData::Release();

		PressA_Listener.reset();
		PressA.reset();
	}

	void ScreenSaver::UpdateGamePause()
	{
		StringWorldGameData::UpdateGamePause();
		if ( Tools::TheGame->LoadingScreen_Renamed != 0 && !Tools::TheGame->LoadingScreen_Renamed->IsDone )
			PauseGame = true;
	}

	void ScreenSaver::BackgroundPhsx()
	{
		 StringWorldGameData::BackgroundPhsx();

		if ( Tools::TheGame->LoadingScreen_Renamed != 0 && !Tools::TheGame->LoadingScreen_Renamed->IsDone )
		{
			Tools::TheGame->LoadingScreen_Renamed->Accelerate = true;
			return;
		}

		PhsxCount++;

		std::shared_ptr<Level> lvl = Tools::CurLevel;
		if ( lvl != 0 && lvl->Bobs.size() > 0 )
		{
			if ( pos_t == 0 )
			{
				pos_t = std::make_shared<FancyVector2>();
				pos_t->setVal( 0 );
				zoom_t = std::make_shared<FancyVector2>();
				zoom_t->setVal( InitialZoom );
				wind_t = std::make_shared<FancyVector2>();
				wind_t->setVal( 0 );

				lvl->MyGame->WaitThenDo( InitialDarkness, std::make_shared<FadeInLambda>( lvl, InitialFadeInSpeed ) );

				lvl->MyGame->WaitThenDo( PartialZoomOut, std::make_shared<SigmoidLambda>( zoom_t ) );
				int zoomout_length = 21;
				int zoomout_start = FullZoomOut + InitialDarkness - 3;
				LerpStyle style = LerpStyle_SIGMOID;
				lvl->MyGame->WaitThenDo( zoomout_start, std::make_shared<ZoomLerpToLambda>( zoom_t, zoomout_length, style ) );
				lvl->MyGame->WaitThenDo( zoomout_start, std::make_shared<PosLerpToLambda>( pos_t, zoomout_length, style ) );

				lvl->MyGame->WaitThenDo( KillCapeDelay + InitialDarkness, std::make_shared<WindLambda>( wind_t ) );

				lvl->MyGame->WaitThenDo( zoomout_start - 3 - 3, std::make_shared<RecordScratchLambda>() );
				Tools::SongWad->SetPlayList( _T( "Ripcurl^Blind_Digital" ) );
				Tools::SongWad->Restart( true, false );
				Tools::SongWad->Pause();
				lvl->MyGame->WaitThenDo( zoomout_start + zoomout_length + 28, std::make_shared<StartMusicLambda>() );
			}

			lvl->Bobs[ 0 ]->CapeWind = CoreMath::LerpRestrict( 2.7f, 0.f, wind_t->getVal() ) * Cape::SineWind( Vector2(-1, .15f), .75f + .3f, 4.5f, static_cast<float>( lvl->CurPhsxStep ) );

			std::shared_ptr<Camera> cam = lvl->getMainCamera();
			cam->UseEffective = true;
			cam->EffectivePos = lvl->Bobs[ 0 ]->getPos();
			cam->EffectiveZoom = Vector2( .0025f );

			cam->EffectivePos = CoreMath::LerpRestrict( lvl->Bobs[ 0 ]->getPos(), cam->Data.Position, pos_t->getVal() );
			cam->EffectivePos.Y = cam->Data.Position.Y;
			cam->EffectiveZoom = Vector2( CoreMath::LerpRestrict( .0025f,.001f, zoom_t->getVal() ) );
		}


		if ( DoBackgroundPhsx && NextIsReady() && (Tools::CurLevel->CurPhsxStep > Duration || Tools::CurLevel->CurPhsxStep > Tools::CurLevel->CurPiece->PieceLength - 50) )
		{
			SetLevel();
			Recycler::DumpMetaBin();
		}
	}

	std::shared_ptr<LevelSeedData> ScreenSaver::Make( int index )
	{
		bool First = index == 0;

		std::shared_ptr<BobPhsx> hero = FixedHero;
		if ( hero == 0 )
		{
			std::vector<std::shared_ptr<BobPhsx> > l;
			l.push_back( BobPhsxSmall::getInstance() );
			l.push_back( BobPhsxBig::getInstance() );
			l.push_back( BobPhsxBouncy::getInstance() );
			l.push_back( BobPhsxInvert::getInstance() );
			l.push_back( BobPhsxSpaceship::getInstance() );
			l.push_back( BobPhsxScale::getInstance() );
			l.push_back( BobPhsxWheel::getInstance() );
			l.push_back( BobPhsx::MakeCustom( Hero_BaseType_WHEEL, Hero_Shape_SMALL, Hero_MoveMod_JETPACK ) );
			l.push_back( BobPhsx::MakeCustom( Hero_BaseType_WHEEL, Hero_Shape_CLASSIC, Hero_MoveMod_DOUBLE ) );
			
			hero = l[ index % l.size() ];
		}

		int Length = 6700;

		// Create the LevelSeedData
		std::shared_ptr<LevelSeedData> data;
		if ( Difficulty >= 0 )
			data = RegularLevel::HeroLevel( static_cast<float>( Difficulty ), hero, Length );
		else
			data = RegularLevel::HeroLevel( static_cast<float>( index % 5 ), hero, Length );

		if ( Bungee )
		{
			data->MyGameFlags.IsTethered = true;
		}

		if ( FixedTileSet == 0 )
		{
			std::vector<std::wstring> tileset_choices;
			tileset_choices.push_back( _T( "forest" ) );
			tileset_choices.push_back( _T( "cave" ) );
			tileset_choices.push_back( _T( "castle" ) );
			tileset_choices.push_back( _T( "cloud" ) );
			tileset_choices.push_back( _T( "hills" ) );
			tileset_choices.push_back( _T( "sea" ) );

			data->SetTileSet( Tools::GlobalRnd->ChooseOne( tileset_choices ) );
		}
		else
			data->SetTileSet( FixedTileSet );

		//data.SetTileSet(Tools.GlobalRnd.ChooseOne("sea", "forest", "cave", "castle", "cloud", "hills",
		//                                          "sea_rain", "forest_snow", "hills_rain"));

		// Adjust the piece seed data
		for ( std::vector<std::shared_ptr<PieceSeedData> >::const_iterator piece = data->PieceSeeds.begin(); piece != data->PieceSeeds.end(); ++piece )
		{
			if ( First )
			{
				FirstLevel( index, *piece );
			}

			// Shorten the initial computer delay
			if ( First )
			{
				std::shared_ptr<SingleData> style = std::dynamic_pointer_cast<SingleData>( ( *piece )->Style );
				style->ComputerWaitLengthRange = Vector2( static_cast<float>( InitialDelay ) );
				style->InitialDoorYRange = Vector2( -200 );
			}
			else
				( *piece )->Style->ComputerWaitLengthRange = Vector2( 0 );

			// No balls to the wall
			( *piece )->Style->FunRun = false;

			// Only one path
			( *piece )->Paths = Paths;
			( *piece )->LockNumOfPaths = true;
		}

		return data;
	}

	void ScreenSaver::FirstLevel( int index, const std::shared_ptr<PieceSeedData> &piece )
	{
		piece->MyUpgrades1->Zero();
		piece->MyUpgrades2->Zero();

		float Difficulty = 8.25f;
		piece->MyUpgrades1->Get( Upgrade_PINKY ) = Difficulty;
		piece->MyUpgrades1->Get( Upgrade_SPIKE ) = Difficulty;
		piece->MyUpgrades1->Get( Upgrade_SPIKEY_GUY ) = Difficulty;
		piece->MyUpgrades1->Get( Upgrade_JUMP ) = 0;
		piece->MyUpgrades1->Get( Upgrade_SPEED ) = 9;
		piece->MyUpgrades1->Get( Upgrade_CEILING ) = 7;

		piece->MyUpgrades1->CalcGenData( piece->MyGenData->gen1, piece->Style );
		//piece->MyUpgrades1->UpgradeLevels.CopyTo( piece->MyUpgrades2->UpgradeLevels, 0 );
		CopyFromTo( piece->MyUpgrades1->UpgradeLevels, piece->MyUpgrades2->UpgradeLevels );
		piece->MyUpgrades2->CalcGenData( piece->MyGenData->gen2, piece->Style );
	}

	void ScreenSaver::MultiplayerBlobs( int index, const std::shared_ptr<PieceSeedData> &piece )
	{
		//// Easy/Masochistic
		//piece.MyUpgrades1.Zero();
		//piece.MyUpgrades2.Zero();

		if ( index % 2 == 1 )
		{
			//piece.MyUpgrades1->Get(Upgrade.Pinky) = 9;
			//piece.MyUpgrades1->Get(Upgrade.Spike) = 9;
			//piece.MyUpgrades1->Get(Upgrade.SpikeyGuy) = 9;
			//piece.MyUpgrades1->Get(Upgrade.Laser) = 9;
			//piece.MyUpgrades1->Get(Upgrade.SpikeyLine) = 9;
			//piece.MyUpgrades1->Get(Upgrade.Firesnake) = 4;
			//piece.MyUpgrades1->Get(Upgrade.FireSpinner) = 9;
			//piece.MyUpgrades1->Get(Upgrade.MovingBlock) = 7;
			//piece.MyUpgrades1->Get(Upgrade.GhostBlock) = 8;
			//piece.MyUpgrades1->Get(Upgrade.Jump) = 2;
			//piece.MyUpgrades1->Get(Upgrade.Speed) = 9;
			//piece.MyUpgrades1->Get(Upgrade.Ceiling) = 7;
		}

		piece->MyUpgrades1->Get( Upgrade_SPIKE ) = 9;
		piece->MyUpgrades1->Get( Upgrade_FLY_BLOB ) = 9;
		if ( index % 4 == 1 )
			piece->MyUpgrades1->Get( Upgrade_FIREBALL ) = 9;
		piece->MyUpgrades1->Get( Upgrade_JUMP ) = 1;
		piece->MyUpgrades1->Get( Upgrade_SPEED ) = 7;
		piece->MyUpgrades1->Get( Upgrade_CEILING ) = 7;

		piece->Style->FunRun = false;
		piece->Style->PauseType = StyleData::_PauseType_NORMAL;
		piece->Style->MoveTypePeriod = StyleData::_MoveTypePeriod_NORMAL1;
		piece->MyUpgrades1->CalcGenData( piece->MyGenData->gen1, piece->Style );
		//piece->MyUpgrades1->UpgradeLevels.CopyTo( piece->MyUpgrades2->UpgradeLevels, 0 );
		CopyFromTo( piece->MyUpgrades1->UpgradeLevels, piece->MyUpgrades2->UpgradeLevels );
		piece->MyUpgrades2->CalcGenData( piece->MyGenData->gen2, piece->Style );
		piece->Paths = Paths;
		piece->LockNumOfPaths = true;
		LevelSeedData::NoDoublePaths = false;

		piece->MyUpgrades1->CalcGenData( piece->MyGenData->gen1, piece->Style );
		//piece->MyUpgrades1->UpgradeLevels.CopyTo( piece->MyUpgrades2->UpgradeLevels, 0 );
		CopyFromTo( piece->MyUpgrades1->UpgradeLevels, piece->MyUpgrades2->UpgradeLevels );
		piece->MyUpgrades2->CalcGenData( piece->MyGenData->gen2, piece->Style );

		piece->Style->MyModParams->Add( std::make_shared<MultiplayerBlobsMyModParamsHelper>( std::static_pointer_cast<ScreenSaver>( shared_from_this() ) ) );
	}

	void ScreenSaver::InitializeInstanceFields()
	{
		ForTrailer = false;
		Bungee = false;
		AllHeroes = false;
		Difficulty = 4;
		Paths = 1;
		FixedHero = BobPhsxNormal::getInstance();
		FixedTileSet = 0;
		InitialZoom = 0;
		InitialFadeInSpeed = .01f;
		PartialZoomOut = 60 + InitialDarkness - 3;
		FullZoomOut = 180;
		KillCapeDelay = 200;
		InitialDelay = 210 + InitialDarkness - 3;
		PressA_Listener = 0;
		PhsxCount = 0;
		Duration = 0;
		DoBackgroundPhsx = true;
	}
}
