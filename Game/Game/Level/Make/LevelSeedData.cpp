#include <global_header.h>

#include "Hacks/List.h"
#include "Hacks/Dict.h"
#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Tilesets/CloudberryKingdom.TileSets.h"

#include <Game/Objects/Game Objects/GameObjects/ChapterTitle.h>

namespace CloudberryKingdom
{

	LevelSeedData::_NewHeroProxy::_NewHeroProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::_NewHeroProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		lsd->_NewHero( level );
	}

	LevelSeedData::_RepeatHeroProxy::_RepeatHeroProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::_RepeatHeroProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		lsd->_RepeatHero( level );
	}

	LevelSeedData::_ShowChapterNameProxy::_ShowChapterNameProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::_ShowChapterNameProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		lsd->_ShowChapterName( level );
	}

	LevelSeedData::_ScoreScreenProxy::_ScoreScreenProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::_ScoreScreenProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		lsd->_ScoreScreen( level );
	}


	LevelSeedData::_StartSongProxy::_StartSongProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::_StartSongProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		lsd->_StartSong( level );
	}

	void LevelSeedData::_HasWall_ProcessProxy::Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &piece )
	{
		LevelSeedData::_HasWall_Process( level, piece );
	}

	void LevelSeedData::_SetWeather_ProcessProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		LevelSeedData::_SetWeather_Process( level );
	}

	void LevelSeedData::_NoStartDoorProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		LevelSeedData::_NoStartDoor( level );
	}

	void LevelSeedData::_FadeIn_ProcessProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		LevelSeedData::_FadeIn_Process( level );
	}

	LevelSeedData::EOL_StringWorldDoorEndAction_WithFadeProxy::EOL_StringWorldDoorEndAction_WithFadeProxy( const boost::shared_ptr<StringWorldGameData> &gameData )
	{
		this->gameData = gameData;
	}

	void LevelSeedData::EOL_StringWorldDoorEndAction_WithFadeProxy::Apply( const boost::shared_ptr<Door> &door )
	{
		gameData->EOL_StringWorldDoorEndAction_WithFade( door );
	}

	void LevelSeedData::_FadeOut_ProcessProxy::Apply( const boost::shared_ptr<Level> &level )
	{
		LevelSeedData::_FadeOut_Process( level );
	}

	LevelSeedData::ModPieceViaStringProxy::ModPieceViaStringProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::ModPieceViaStringProxy::Apply( const boost::shared_ptr<PieceSeedData> &piece )
	{
		lsd->ModPieceViaString( piece );
	}

	LevelSeedData::ModPieceViaHashProxy::ModPieceViaHashProxy( const boost::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::ModPieceViaHashProxy::Apply( const boost::shared_ptr<PieceSeedData> &piece )
	{
		lsd->ModPieceViaHash( piece );
	}

	LevelSeedData::SetToStartSongHelper::SetToStartSongHelper( const boost::shared_ptr<EzSong> &song )
	{
		this->song = song;
	}

	void LevelSeedData::SetToStartSongHelper::Apply()
	{
		Tools::SongWad->LoopSong( song );
	}

	LevelSeedData::SetToStartSongPostMakeHelper::SetToStartSongPostMakeHelper( int delay, const boost::shared_ptr<Lambda> &songHelper )
	{
		this->delay = delay;
		this->songHelper = songHelper;
	}

	void LevelSeedData::SetToStartSongPostMakeHelper::Apply( const boost::shared_ptr<Level> &lvl )
	{
		lvl->MyGame->WaitThenDo( delay, songHelper );
	}

	void LevelSeedData::BOL_StartMusicProxy::Apply()
	{
		LevelSeedData::BOL_StartMusic();
	}

	LevelSeedData::ScoreScreenLambda::ScoreScreenLambda( StatGroup stats, const boost::shared_ptr<Level> &level )
	{
		this->stats = stats;
		this->level = level;
	}

	boost::shared_ptr<GameObject> LevelSeedData::ScoreScreenLambda::Apply()
	{
		return MakeMagic( ScoreScreen, ( stats, level->MyGame, false ) );
	}

	void LevelSeedData::EOL_DoorActionProxy::Apply( const boost::shared_ptr<Door> &door )
	{
		GameData::EOL_DoorAction( door );
	}

	void LevelSeedData::PostMake_StringWorldStandardHelper::Apply()
	{
		if ( !Tools::SongWad->IsPlaying() )
		{
			Tools::SongWad->SetPlayList( Tools::SongList_Standard );
			Tools::SongWad->Shuffle();
			Tools::SongWad->Start( true );
		}
	}

	LevelSeedData::StandardInitHelper::StandardInitHelper( const boost::shared_ptr<Lambda_2<boost::shared_ptr<PieceSeedData>, boost::shared_ptr<Upgrades> > > &CustomDiff )
	{
		this->CustomDiff = CustomDiff;
	}

	void LevelSeedData::StandardInitHelper::Apply( const boost::shared_ptr<PieceSeedData> &p )
	{
		CustomDiff->Apply( p, p->getu() );
		p->MyUpgrades1->CalcGenData( p->MyGenData->gen1, p->Style );

		RndDifficulty::ZeroUpgrades( p->MyUpgrades2 );
		CopyFromTo( p->MyUpgrades1->UpgradeLevels, p->MyUpgrades2->UpgradeLevels );
		p->MyUpgrades2->CalcGenData( p->MyGenData->gen2, p->Style );

		p->Style->MyInitialPlatsType = StyleData::InitialPlatsType_DOOR;
		p->Style->MyFinalPlatsType = StyleData::FinalPlatsType_DOOR;
	}

	void LevelSeedData::InitNormalMyModParamsHelper::Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p )
	{
		p->Style->FillxStep *= 3.1f;
		p->Style->FillyStep *= 1.7f;
	}

	bool LevelSeedData::NoDoublePaths = true;

	boost::shared_ptr<Level> LevelSeedData::MakeLevel( const boost::shared_ptr<GameData> &game )
	{
		return MakeLevel( true, game );
	}

	boost::shared_ptr<Level> LevelSeedData::MakeLevel( bool MakeBackground, const boost::shared_ptr<GameData> &game )
	{
		this->setSeed( this->getSeed() );
		int TestNumber;

		game->EndMusicOnFinish = !NoMusicStart;

		game->DefaultHeroType = this->DefaultHeroType; // = BobPhsxMario.Instance;

		boost::shared_ptr<Level> NewLevel = MakeNewLevel( game );
		NewLevel->Geometry = MyGeometry;
		boost::shared_ptr<Camera> cam = NewLevel->getMainCamera();

        // Set lava
        //if (NewLevel.Info.AllowLava)
        //switch (LavaMake)
        //{
        //    case LavaMakeTypes.AlwaysMake: game.HasLava = true; break;
        //    case LavaMakeTypes.Random: game.HasLava = Rnd.RndBool(.38f); break;
        //    default: game.HasLava = false; break;
        //}
        if ( NewLevel->getInfo()->AllowLava )
            game->HasLava = true;

		if ( !NewLevel->MyBackground->AllowLava )
			game->HasLava = false;

		NewLevel->MyLevelSeed = shared_from_this();

		float Height = 0;

		boost::shared_ptr<Level> level = 0;
		for ( std::vector<boost::shared_ptr<PieceSeedData> >::const_iterator Piece = PieceSeeds.begin(); Piece != PieceSeeds.end(); ++Piece )
		{
			if ( ( *Piece )->Ladder != LadderType_NONE )
			{
				NewLevel->MakeLadder( *Piece );

				if ( IndexOf( PieceSeeds, *Piece ) == 0 )
					cam->BLCamBound = cam->Data.Position;

				continue;
			}

			// Ensure that there are no blobs on a single path, multiplayer level
			if ( ( *Piece )->Paths == 1 && !( *Piece )->LockNumOfPaths )
			if ( PlayerManager::GetNumPlayers() > 1 && (*Piece)->MyUpgrades1->Get( Upgrade_FLY_BLOB ) > 0 )
			{
				( *Piece )->Paths = 2;
			}

			// Ensure there are no double paths!
			// Would like to allow double paths, but they are broken sometimes.
			if ( NoDoublePaths )
				( *Piece )->Paths = 1;

			// Ensure that bungee levels have at least two paths!
			if ( MyGameFlags.IsTethered && ( *Piece )->Paths == 1 )
			{
				( *Piece )->Paths = 2;
			}

			TestNumber = Rnd->RndInt( 0, 1000 );
			Tools::Write( _T( "Test 1 ---> {0}" ), TestNumber );



			level = boost::make_shared<Level>( true );
			level->MySourceGame = game;
			level->MyLevelSeed = shared_from_this();
			level->MyTileSet = NewLevel->MyTileSet;
			level->DefaultHeroType = NewLevel->DefaultHeroType;
			level->setMainCamera( boost::make_shared<Camera>() );

			cam->Data.Position = ( *Piece )->Start + Vector2( 1000, 0 );
			cam->Update();


			boost::shared_ptr<MakeData> makeData = boost::make_shared<MakeData>();
			makeData->LevelSeed = shared_from_this();
			makeData->PieceSeed = *Piece;
			makeData->GenData = ( *Piece )->MyGenData;
			makeData->Index = IndexOf( PieceSeeds, *Piece );
			makeData->OutOf = PieceSeeds.size();

			int ReturnEarly = SetReturnEarly( *Piece );

			level->Geometry = ( *Piece )->GeometryType;
			level->BoxesOnly = true;
			switch ( ( *Piece )->GeometryType )
			{
				case LevelGeometry_RIGHT:
					level->MakeSingle( 3000, ( *Piece )->End.X, ( *Piece )->Start.X, 0, ReturnEarly, makeData );
					break;

				case LevelGeometry_DOWN:
				case LevelGeometry_UP:
					level->MakeVertical( 3000, fabs( ( *Piece )->End.Y - ( *Piece )->Start.Y ), 0, ReturnEarly, makeData );
					Height += fabs( ( *Piece )->End.Y - ( *Piece )->Start.Y );
					break;

				//case LevelGeometry.Big:
				//    level.MakeBig(this.Length, 0, ReturnEarly, makeData);
				//    break;

				//case LevelGeometry.OneScreen:
				//    level.MakeOneScreen(this.Length, ReturnEarly, makeData);
				//    break;
			}

			TestNumber = Rnd->RndInt( 0, 1000 );
			Tools::Write( _T( "Test 1.5 ---> {0}" ), TestNumber );


			if ( ReturnEarly > 0 )
			{
				Tools::DrawBoxes = true;

				level->MainEmitter = boost::make_shared<ParticleEmitter>( 1000 );
				for ( BobVec::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
					( *bob )->SetColorScheme( ColorSchemeManager::ColorSchemes[ 0 ] );
				level->SetToWatchMake = true;
				NewLevel = level;

				NewLevel->ReturnedEarly = true;

				Tools::CurGameData = NewLevel->MySourceGame;

				return NewLevel;
			}

			if ( IndexOf( PieceSeeds, *Piece ) == 0 )
				NewLevel->getMainCamera()->BLCamBound = level->getMainCamera()->BLCamBound;


			level->ResetAll( false );

			// Add checkpoints
			if ( ( *Piece )->CheckpointsAtStart && !( *Piece )->Style->SuppressCheckpoints )
			{
				for ( int i = 0; i < level->LevelPieces[ 0 ]->NumBobs; i++ )
				{
					boost::shared_ptr<Checkpoint> checkpoint = boost::static_pointer_cast<Checkpoint>( game->Recycle->GetObject( ObjectType_CHECKPOINT, false ) );
					checkpoint->Init( level );

					PhsxData data = level->LevelPieces[ 0 ]->StartData[ i ];
					data.Position.X = level->LevelPieces[ 0 ]->StartData[ 0 ].Position.X;
					data.Position += level->LevelPieces[ 0 ]->CheckpointShift[ i ];

					checkpoint->getCore()->StartData = checkpoint->getCore()->Data = data;

					checkpoint->MyPiece = level->LevelPieces[ 0 ];
					checkpoint->MyPieceIndex = i;

					level->AddObject( checkpoint );
				}
			}


			level->Cleanup( ObjectType_CHECKPOINT, Vector2( 900, 900 ) );
			level->CleanAllObjectLists();

			// Add initial start data
			if ( ( *Piece )->InitialCheckpointsHere )
			{
				NewLevel->CurPiece = level->LevelPieces[ 0 ];
			}

			// Absorb the new level
			NewLevel->AbsorbLevel( level );

			// Absorb the new level's time type
			if ( level->TimeType != TimeTypes_REGULAR )
				NewLevel->TimeType = level->TimeType;

			NewLevel->Par += level->Par; // Add the level's par to the big level's par

			TestNumber = Rnd->RndInt( 0, 1000 );
			Tools::Write( _T( "Test 2 ---> {0}" ), TestNumber );
		}

		// Cleanup lava
		BlockVec Lavas = BlockVec();
		for ( BlockVec::const_iterator block = NewLevel->Blocks.begin(); block != NewLevel->Blocks.end(); ++block )
			if ( ( *block )->getCore()->MyType == ObjectType_LAVA_BLOCK )
				Lavas.push_back( *block );

		if ( Lavas.size() > 0 )
		{
			// Find the lowest watermark
			boost::shared_ptr<BlockBase> Lowest = 0;
			for ( BlockVec::const_iterator lava = Lavas.begin(); lava != Lavas.end(); ++lava )
				if ( Lowest == 0 || ( *lava )->getBox()->TR.Y < Lowest->getBox()->TR.Y )
					Lowest = *lava;

			// Extend left and right to cover whole level
			Lowest->Extend( Side_LEFT, NewLevel->BL.X - 5000 );
			Lowest->Extend( Side_RIGHT, NewLevel->TR.X + 5000 );

			// Push down a bit
			Lowest->Extend( Side_TOP, Lowest->getBox()->TR.Y - Rnd->RndFloat(0, 60) );
			if ( Lowest->getBox()->TR.Y < -840 )
				Lowest->CollectSelf();

			// Remove extra lava blocks
			for ( BlockVec::const_iterator lava = Lavas.begin(); lava != Lavas.end(); ++lava )
				if ( *lava != Lowest )
					( *lava )->CollectSelf();
		}

		if ( MakeBackground )
			MakeTheBackground( NewLevel, Height );

		// Select first piece of level to start
		NewLevel->SetCurrentPiece( 0 );

		// Count coins, blobs
		NewLevel->CountCoinsAndBlobs();

		return NewLevel;
	}

	void LevelSeedData::MakeTheBackground( const boost::shared_ptr<Level> &NewLevel, float Height )
	{
		NewLevel->MyBackground->Init( NewLevel );
	}

	int LevelSeedData::ForcedReturnEarly = 0;

	int LevelSeedData::SetReturnEarly( const boost::shared_ptr<PieceSeedData> &Piece )
	{
		int ReturnEarly = ForcedReturnEarly;

		return ReturnEarly;
	}

	const std::wstring LevelSeedData::WallFlag = std::wstring( L"wall" );
	const std::wstring LevelSeedData::FadeInFlag = std::wstring( L"fadein" );
	const std::wstring LevelSeedData::FadeOutFlag = std::wstring( L"fadeout" );
	const std::wstring LevelSeedData::WeatherIntensityFlag = std::wstring( L"weather" );
	const std::wstring LevelSeedData::NoStartDoorFlag = std::wstring( L"nostartdoor" );
	const std::wstring LevelSeedData::LevelFlag = std::wstring( L"level" );
	const std::wstring LevelSeedData::IndexFlag = std::wstring( L"index" );
	const std::wstring LevelSeedData::WaitLengthToOpenDoorString = std::wstring( L"opendoor" );
	const std::wstring LevelSeedData::OpenDoorSoundFlag = std::wstring( L"opendoorsound" );
	const std::wstring LevelSeedData::SongString = std::wstring( L"song" );

	const std::wstring LevelSeedData::NewHeroFlag = L"newhero";

	const std::wstring LevelSeedData::RepeatHeroFlag = L"repeathero";
	const std::wstring LevelSeedData::ChapterNameFlag = L"chapter";
	const std::wstring LevelSeedData::ScoreScreenFlag = L"scorescreen";

    const std::wstring LevelSeedData::DarknessFlag = L"darkness";
    const std::wstring LevelSeedData::MasochistFlag = L"masochist";

	const std::wstring RepeatHeroFlag = L"repeathero";
	const std::wstring ChapterNameFlag = L"chapter";
	const std::wstring ScoreScreenFlag = L"scorescreen";


	void LevelSeedData::ProcessSpecial()
	{
		if ( HasWall )
		{
			boost::shared_ptr<PieceSeedData> p = PieceSeeds[ 0 ];
			//p.Style.ComputerWaitLengthRange = new Vector2(4, 23);

			p->Style->MyModParams->Add( boost::make_shared<_HasWall_ProcessProxy>() );
		}

		if (NewHero) PostMake->Add( boost::make_shared<_NewHeroProxy>( shared_from_this() ) );

		if (RepeatHero) PostMake->Add( boost::make_shared<_RepeatHeroProxy>( shared_from_this() ) );

		if (ShowChapterName) PostMake->Add( boost::make_shared<_ShowChapterNameProxy>( shared_from_this() ) );

		if (GiveScoreScreen) PostMake->Add( boost::make_shared<_ScoreScreenProxy>( shared_from_this() ) );

		if ( NoStartDoor )
			PostMake->Add( boost::make_shared<_NoStartDoorProxy>() );

		if ( FadeIn )
			PostMake->Add( boost::make_shared<_FadeIn_ProcessProxy>() );

		if ( FadeOut )
			PostMake->Add( boost::make_shared<_FadeOut_ProcessProxy>() );

		if ( WeatherIntensity != 1 )
			PostMake->Add( boost::make_shared<_SetWeather_ProcessProxy>() );

		if ( MySong != 0 )
			PostMake->Add( boost::make_shared<_StartSongProxy>( shared_from_this() ) );
	}

	void LevelSeedData::WaitThenPlay( boost::shared_ptr<GameData> game, int wait, boost::shared_ptr<EzSong> song)
	{
		game->WaitThenDo( wait, boost::make_shared<WaitThenPlayProxy>( song ) );
	}

	LevelSeedData::WaitThenPlayProxy::WaitThenPlayProxy( boost::shared_ptr<EzSong> _song )
	{
		song = _song;
	}

	void LevelSeedData::WaitThenPlayProxy::Apply()
	{
		if ( song == 0 )
		{
			Tools::SongWad->Start( true );
			Tools::SongWad->Next();
		}
		else
		{
			Tools::SongWad->Next( song );
		}
		Tools::SongWad->PlayNext = true;
	}


	void LevelSeedData::_StartSong( const boost::shared_ptr<Level> &level )
	{
		if ( MySong == Tools::Song_Happy )
		{
			Tools::SongWad->SetPlayList(MySong);
			WaitThenPlay(level->MyGame, 40, MySong);
		}
		else
		{
			Tools::SongWad->SetPlayList(Tools::SongList_Standard);
			WaitThenPlay(level->MyGame, 40, MySong);
		}
	}

	void LevelSeedData::_HasWall_Process( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &piece )
	{
		boost::shared_ptr<NormalBlock_Parameters> Params = boost::static_pointer_cast<NormalBlock_Parameters>( piece->Style->FindParams( NormalBlock_AutoGen::getInstance() ) );
		boost::shared_ptr<Wall> wall = Params->SetWall( LevelGeometry_RIGHT );
		wall->Space = 20;
		wall->MyBufferType = Wall::BufferType_SPACE;
		piece->CamZoneStartAdd.X = -2000;
		wall->StartOffset = -600;
		wall->Speed = 17.5f;
		wall->InitialDelay = 72;
	}

	void LevelSeedData::_SetWeather_Process( const boost::shared_ptr<Level> &level )
	{
		level->MyBackground->SetWeatherIntensity( level->MyLevelSeed->WeatherIntensity );
	}

	void LevelSeedData::_NoStartDoor( const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<CloudberryKingdom::Door> door = level->getStartDoor();
		if ( door == 0 )
			return;
		door->CollectSelf();
	}

    void LevelSeedData::_NewHero( const boost::shared_ptr<Level> &level )
    {
		//level->MyGame->AddGameObject( MakeMagic( NewHero_GUI, ( Localization::WordString( Localization::Words_NewHeroUnlocked ) + L"\n" + Localization::WordString( level->DefaultHeroType->Name ) ) ) );
        level->MyGame->AddGameObject( MakeMagic( NewHero_GUI, ( Localization::WordString (level->DefaultHeroType->Name ) ) ) );
		level->MyLevelSeed->WaitLengthToOpenDoor = 150;
        level->MyLevelSeed->AlwaysOverrideWaitDoorLength = true;
    }

		void LevelSeedData::_RepeatHero( const boost::shared_ptr<Level> &level )
		{
			level->MyGame->AddGameObject( MakeMagic( LevelTitle, ( Localization::WordString( level->DefaultHeroType->Name ), Vector2(0, 200), 1.f, false) ) );
		}

		void LevelSeedData::_ShowChapterName( const boost::shared_ptr<Level> &level )
		{
			if ( level->MyLevelSeed->ChapterNameIndex < 0 || level->MyLevelSeed->ChapterNameIndex >= static_cast<int>( CampaignSequence::ChapterName.size() ) ) return;

			level->SetBack(27);

			Tools::SongWad->SuppressNextInfoDisplay = true;
			Tools::SongWad->DisplayingInfo = false;

			level->MyGame->AddGameObject( MakeMagic( ChapterTitle, ( CampaignSequence::ChapterName[ level->MyLevelSeed->ChapterNameIndex ] ) ) );
			level->MyLevelSeed->WaitLengthToOpenDoor = 150;
			level->MyLevelSeed->AlwaysOverrideWaitDoorLength = true;
		}

		void LevelSeedData::_ScoreScreen( const boost::shared_ptr<Level> &level )
		{
			level->MyGame->MakeScore = boost::make_shared<LevelSeedData::MakeScoreProxy>( level );

			boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( level->FindIObject(LevelConnector::EndOfLevelCode) );
			door->setOnOpen( boost::make_shared<LevelSeedData::EOL_DoorActionProxy>() );

			level->StartRecording();
		}

		LevelSeedData::MakeScoreProxy::MakeScoreProxy( boost::shared_ptr<Level> _level )
		{
			level = _level;
		}

		boost::shared_ptr<GameObject> LevelSeedData::MakeScoreProxy::Apply()
		{
			CampaignSequence::MarkProgress( level );
			return MakeMagic( ScoreScreen, ( StatGroup_LEVEL, level->MyGame, true ) );
		}

	void LevelSeedData::_FadeIn_Process( const boost::shared_ptr<Level> &level )
	{
		level->MyGame->PhsxStepsToDo += 2;
		level->MyGame->AddGameObject( boost::make_shared<FadeInObject>() );
	}

	void LevelSeedData::_FadeOut_Process( const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<StringWorldGameData> stringworld = boost::dynamic_pointer_cast<StringWorldGameData>( Tools::WorldMap );
		boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( level->FindIObject( LevelConnector::EndOfLevelCode ) );

		if ( 0 != stringworld && 0 != door )
		{
			door->setOnEnter( boost::make_shared<EOL_StringWorldDoorEndAction_WithFadeProxy>( stringworld ) );
		}
	}

	void LevelSeedData::DefaultRead( const std::wstring &str )
	{
		int i = abs( GetHashCode(str) );

		// Length
		Length = PieceLength = static_cast<int>( ( static_cast<unsigned int>( i * 997 ) ) % 7000 + 5000 );

		// Tileset
		i /= 2;
		//boost::shared_ptr<std::vector<boost::shared_ptr<BackgroundTemplate> > > tilesets = TileSets::NameLookup.Keys::ToList();
		boost::shared_ptr<TileSet> tileset = CustomLevel_GUI::FreeplayTilesets[ ( i + 23 ) % CustomLevel_GUI::FreeplayTilesets.size() ];
		if ( tileset == TileSets::Random )
			tileset = CustomLevel_GUI::FreeplayTilesets[ ( i + 2323 ) % CustomLevel_GUI::FreeplayTilesets.size() ];
		if ( tileset == TileSets::Random )
			tileset = CustomLevel_GUI::FreeplayTilesets[ CustomLevel_GUI::FreeplayTilesets.size() - 1 ];
		SetTileSet( tileset );

		// Geometry, gametype
		i /= 3;
		i *= 2;
		MyGeometry = LevelGeometry_RIGHT;
		MyGameType = NormalGameData::Factory;
		LavaMake = LevelSeedData::LavaMakeTypes_NEVER_MAKE;

		// Hero
		DefaultHeroType = CustomLevel_GUI::FreeplayHeroes[ ( i + 555 ) % CustomLevel_GUI::FreeplayHeroes.size() ];
		RandomHero( DefaultHeroType, i * i + 3 * i );

		// Pieces
		NumPieces = i % 2 + 1;

		// Seed
		setSeed( i % 7777777 );

		PieceHash = i * getSeed();
	}

	void LevelSeedData::ReadString( std::wstring str )
	{
		DefaultRead( str );
		UpgradeStrs.clear();

		str = Tools::RemoveComment_SlashStyle( str );

		std::vector<std::wstring> bits = Split( str, L';' );

		// FIXME: Fix all the try/catch error cases in the following loop.

		for ( int i = 0; i < static_cast<int>( bits.size() ); i++ )
		{
			std::wstring identifier, data;

			int index = bits[ i ].find( std::wstring( L":" ) );

			if ( index <= 0 )
			{
				identifier = bits[ i ];
				data = std::wstring( L"" );
			}
			else
			{
				identifier = bits[ i ].substr( 0, index );
				data = bits[ i ].substr( index + 1 );
			}

			std::vector<std::wstring> terms;
			std::wstring lower_identifier = ToLower( identifier );

			// Seed [This must come first]
			if ( lower_identifier == std::wstring( L"s" ) )
			{
				int seedval = 0;
				if ( ParseInt( data, seedval ) )
				{
					setSeed( seedval );
				}
				else
				{
					setSeed( GetHashCode(data) );
				}
			}
			// Game type
			else if ( lower_identifier == std::wstring( L"g" ) )
			{
				MyGameType = NormalGameData::Factory;
			}
			// Geometry
			else if ( lower_identifier == std::wstring( L"geo" ) )
			{
				int geomval = 0;
				if ( ParseInt( data, geomval ) )
				{
					MyGeometry = static_cast<LevelGeometry>( geomval );
				}
				else
				{
					MyGeometry = LevelGeometry_RIGHT;
				}
			}
			// Hero [This must come before "ph:"]
			else if ( lower_identifier == std::wstring( L"h" ) )
			{
				terms = Split( data, L',' );
				if ( terms.size() == 4 )
					DefaultHeroType = BobPhsx::MakeCustom( terms[ 0 ], terms[ 1 ], terms[ 2 ], terms[ 3 ] );
				else
					DefaultHeroType = BobPhsxNormal::getInstance();
			}
			// Custom physics [This must come after "h:"]
			else if ( lower_identifier == std::wstring( L"ph" ) )
			{
				BobPhsx::CustomPhsxData custom = BobPhsx::CustomPhsxData();
				custom.Init( data );
				DefaultHeroType->SetCustomPhsx( custom );
			}
			// Tileset
			else if ( lower_identifier == std::wstring( L"t" ) )
			{
				MyTileSet.reset();
				if ( data.length() > 0 && Contains( TileSets::NameLookup, data ) )
				{
					SetTileSet( data );
				}
				if ( MyTileSet == 0 )
					SetTileSet( std::wstring( L"castle" ) );
			}
			// Number of pieces
			else if ( lower_identifier == std::wstring( L"n" ) )
			{
				int numval = 0;
				if( ParseInt( data, numval ) )
				{
					NumPieces = numval;
					NumPieces = CoreMath::RestrictVal( 1, 5, NumPieces );
				}
				else
				{
					NumPieces = 1;
				}
			}
			// Length
			else if ( lower_identifier == std::wstring( L"l" ) )
			{
				int lengthval = 0;
				if ( ParseInt( data, lengthval ) )
				{
					Length = lengthval;
					Length = CoreMath::RestrictVal( 2000, 50000, Length );
					PieceLength = Length;
				}
				else
				{
					PieceLength = Length = 5000;
				}
			}
			// Upgrades
			else if ( lower_identifier == std::wstring( L"u" ) )
			{
				UpgradeStrs.push_back( data );
			}
			// Meta
			else if ( lower_identifier == std::wstring( L"m" ) )
			{
				int metaval = 0;
				if ( ParseInt( data, metaval ) )
					MyMetaGameType = static_cast<MetaGameType>( metaval );
				else
					MyMetaGameType = MetaGameType_NONE;
			}
			// Wall
			else if ( lower_identifier == WallFlag )
			{
				HasWall = true;
			}
			// Fade In
			else if ( lower_identifier == FadeInFlag )
			{
				FadeIn = true;

				float fadeinval = 0;
				if ( ParseFloat( data, fadeinval ) )
				{
					FadeInSpeed = fadeinval;
				}
			}
			// Fade Out
			else if ( lower_identifier == FadeOutFlag )
			{
				FadeOut = true;
                
				float fadeoutval = 0;
				if ( ParseFloat( data, fadeoutval ) )
				{
					FadeOutSpeed = fadeoutval;
				}
			}
            // NewHero
			else if ( lower_identifier == NewHeroFlag )
			{
				NewHero = true;
			}

					// RepeatHero
					else if ( lower_identifier == RepeatHeroFlag )
					{
						RepeatHero = true;
					}	
					// Chapter Name
					else if ( lower_identifier == ChapterNameFlag )
					{
						ShowChapterName = true;
						int chapterindex = 0;
						if ( ParseInt( data, chapterindex ) )
							ChapterNameIndex = chapterindex - 1;
						else
							ChapterNameIndex = -1;
					}
					// Score Screen
					else if ( lower_identifier == ScoreScreenFlag )
					{
						GiveScoreScreen = true;
					}

            // Darkness
			else if ( lower_identifier == DarknessFlag )
			{
				Darkness = true;
			}
            // Masochist
			else if ( lower_identifier == MasochistFlag )
			{
				Masochistic = true;
			}
			// No start door
			else if ( lower_identifier == NoStartDoorFlag )
			{
				NoStartDoor = true;
			}
			// Level number
			else if ( lower_identifier == LevelFlag )
			{
				int levelval = 0;
				if ( ParseInt( data, levelval ) )
					LevelNum = levelval;
				else
					LevelNum = 0;
			}
			// Index number
			else if ( lower_identifier == IndexFlag )
			{
				int Indexval = 0;
				if ( ParseInt( data, Indexval ) )
					LevelIndex = Indexval;
				else
					LevelIndex = 0;
			}
			// Weather intensity
			else if ( lower_identifier == WeatherIntensityFlag )
			{
				float weatherval = 0;
				if ( ParseFloat( data, weatherval ) )
				{
					WeatherIntensity = weatherval;
				}
				else
				{
					WeatherIntensity = 1;
				}
			}
			// Wait length to open door
			else if ( lower_identifier == WaitLengthToOpenDoorString )
			{
				int waitlengthval = 0;
				if ( ParseInt( data, waitlengthval ) )
				{
					WaitLengthToOpenDoor = waitlengthval;
				}
				else
				{
					WaitLengthToOpenDoor = 6;
				}
			}
			// Song to play at beginning of level
			else if ( lower_identifier == SongString )
			{
				MySong = Tools::SongWad->FindByName( data );
			}
			// Open door sound
			else if ( lower_identifier == OpenDoorSoundFlag )
			{
				OpenDoorSound = true;
			}
			else
			{
			}
		}

		// Error catch.
		if ( boost::dynamic_pointer_cast<BobPhsxMeat>( DefaultHeroType ) != 0 )
		{
			MyGeometry = LevelGeometry_UP;
			NumPieces = 1;
		}
		if ( boost::dynamic_pointer_cast<BobPhsxRocketbox>( DefaultHeroType ) != 0 )
		{
			MyGeometry = LevelGeometry_RIGHT;
			NumPieces = 1;
		}

		// If no upgrade was provided, zero everything.
		if ( UpgradeStrs.empty() )
		{
			UpgradeStrs.push_back( std::wstring( L"" ) );
			Initialize( boost::make_shared<ModPieceViaHashProxy>( shared_from_this() ) );
		}
		else
		{
			Initialize( boost::make_shared<ModPieceViaStringProxy>( shared_from_this() ) );
		}

		ProcessSpecial();
	}

	std::wstring LevelSeedData::ToString()
	{
		int _version = 0;
		std::wstring version = StringConverterHelper::toString( _version ) + std::wstring( L";" );

		// Seed
		std::wstring seed = std::wstring( L"s:" ) + StringConverterHelper::toString( getSeed() ) + std::wstring( L";" );

		// Game
		std::wstring game = std::wstring( L"" );
		if ( MyGameType != NormalGameData::Factory )
		{
			return std::wstring( L"!This level can not be saved!" );
		}

		// Geometry
		std::wstring geometry = std::wstring( L"" );
		if ( MyGeometry != LevelGeometry_RIGHT )
			geometry = Format( _T( "geo:%d;" ), + static_cast<int>( MyGeometry ) );

		// Hero
		std::wstring hero = Format( _T( "h:%ls;" ), DefaultHeroType->Specification.ToString().c_str() );

		// Custom phsx
		std::wstring customphsx = std::wstring( L"" );
		if ( DefaultHeroType->CustomPhsx )
			customphsx = DefaultHeroType->MyCustomPhsxData.ToString();

		// Tileset
		std::wstring tileset = Format( _T( "t:%ls;" ), MyTileSet->Name.c_str() );

		// Pieces
		std::wstring pieces = Format( _T( "n:%d;" ), NumPieces );

		// Length
		std::wstring length = Format( _T( "l:%ls;" ), StringConverterHelper::toString( Length ).c_str() );

		// Upgrades
		std::wstring upgrades = std::wstring( L"" );
		for ( std::vector<boost::shared_ptr<PieceSeedData> >::const_iterator p = PieceSeeds.begin(); p != PieceSeeds.end(); ++p )
		{
			if ( ( *p )->Ladder != LadderType_NONE )
				continue;

			upgrades += std::wstring( L"u:" );

			std::vector<float> upgrade_levels = ( *p )->MyUpgrades1->UpgradeLevels;
			for ( int i = 0; i < static_cast<int>( upgrade_levels.size() ); i++ )
			{
				upgrades += StringConverterHelper::toString( upgrade_levels[ i ] );
				if ( i + 1 < static_cast<int>( upgrade_levels.size() ) )
					upgrades += std::wstring( L"," );
			}
			upgrades += std::wstring( L";" );
		}

        // Metagame origin
        std::wstring meta = L"m:" + ::ToString( static_cast<int>( PieceSeeds[0]->MyMetaGameType ) ) + L";";

		// Build final string
		std::wstring str = version + seed + game + geometry + hero + customphsx + tileset + pieces + length + upgrades + meta;

		// Add special flags
		if ( HasWall ) str += WallFlag + std::wstring( L";" );
		if ( Masochistic ) str += MasochistFlag + L";";

		return str;
	}

	void LevelSeedData::ModPieceViaString( const boost::shared_ptr<PieceSeedData> &piece )
	{
		// Break the data up by commas
		int index = CoreMath::RestrictVal( 0, UpgradeStrs.size() - 1, piece->MyPieceIndex );
		std::vector<std::wstring> terms = Split( UpgradeStrs[ index ], L',' );

		// Try and load the data into the upgrade array.
		bool result = false;

		for ( int i = 0; i < static_cast<int>( terms.size() ); i++ )
		{
			float val = 0;
			if ( ParseFloat( terms[ i ], val ) )
				piece->MyUpgrades1->UpgradeLevels[ i ] = val;
			else
				piece->MyUpgrades1->UpgradeLevels[ i ] = 0;
		}

		piece->StandardClose();
	}

	void LevelSeedData::ModPieceViaHash( const boost::shared_ptr<PieceSeedData> &piece )
	{
		PieceHash = abs( PieceHash );
		PieceHash *= 997;
		PieceHash %= 1024;
		PieceHash = abs( PieceHash );

		int Bias = static_cast<int>( 75 - static_cast<unsigned int>( PieceHash ) % 50 );

		for ( int i = 0; i < static_cast<int>( piece->MyUpgrades1->UpgradeLevels.size() ); i++ )
		{
			int n1 = PieceHash | ( 2 + 8 + 32 + 128 + 512 );
			int n2 = PieceHash | ( 1 + 4 + 16 + 64 + 256 );

			int value = 0;
			if ( ( n1 * n2 + static_cast<int>( exp( static_cast<double>( i ) ) ) ) % 100 > Bias )
				value = ( n1 + n1 * n2 ) % 10;

			piece->MyUpgrades1->UpgradeLevels[ i ] = static_cast<float>( CoreMath::RestrictVal( 0, 10, value ) );
		}

		piece->MyUpgrades1->Get( Upgrade_CONVEYOR ) = 0;
		piece->MyUpgrades1->Get( Upgrade_FIRESNAKE ) = piece->MyUpgrades1->Get( Upgrade_CONVEYOR );

		piece->StandardClose();
	}

	void LevelSeedData::RandomHero( const boost::shared_ptr<BobPhsx> &Hero, int Hash )
	{
		int Length = BobPhsx::CustomPhsxData::Length;
		std::vector<float> vals = std::vector<float>( Length );

		for ( int i = 0; i < Length; i++ )
		{
			int value = i * PieceHash * PieceHash + PieceHash + i * i;

			vals[ i ] = CoreMath::RestrictVal( BobPhsx::CustomPhsxData::Bounds( i ).MinValue, BobPhsx::CustomPhsxData::Bounds( i ).MaxValue, static_cast<float>( value ) );
			vals[ i ] = static_cast<float>( CoreMath::RestrictVal( 0, 1, value ) );
		}

		Hero->MyCustomPhsxData.Init( vals );
	}

	std::wstring LevelSeedData::SuggestedName()
	{
		return Localization::WordString( DefaultHeroType->Name ) + std::wstring( L"_" ) + StringConverterHelper::toString( getSeed() );
	}

	std::wstring LevelSeedData::GetNameFromSeedStr( const std::wstring &seed )
	{
		int index_name = seed.find( std::wstring( L"name:" ) ) + 5;
		int index_name_end = seed.find( std::wstring( L";" ), index_name );
		std::wstring name = seed.substr( index_name, index_name_end - index_name );

		return name;
	}

	void LevelSeedData::SetToStartSong( const boost::shared_ptr<EzSong> &song )
	{
		SetToStartSong( song, 5 );
	}

	void LevelSeedData::SetToStartSong( const boost::shared_ptr<EzSong> &song, int delay )
	{
		NoMusicStart = true;
		PostMake->Add( boost::make_shared<SetToStartSongPostMakeHelper>( delay, boost::make_shared<SetToStartSongHelper>( song ) ) );
	}

	void LevelSeedData::AddGameObjects_Default( const boost::shared_ptr<Level> &level, bool global, bool ShowMultiplier )
	{
		level->MyGame->AddGameObject( MakeMagic( HintGiver, () ) );
		level->MyGame->AddGameObject( HelpMenu::MakeListener() );
		level->MyGame->AddGameObject( MakeMagic( PerfectScoreObject, (global, ShowMultiplier) ) );

		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
	}

	void LevelSeedData::AddGameObjects_BareBones( const boost::shared_ptr<Level> &level, bool global )
	{
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
		level->MyGame->AddGameObject( MakeMagic( PerfectScoreObject, (global, true) ) );
	}

	void LevelSeedData::BOL_StartMusic()
	{
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		Tools::SongWad->Shuffle();
		Tools::SongWad->Start( true );
	}

	void LevelSeedData::PostMake_EnableLoad( const boost::shared_ptr<Level> &level )
	{
		level->CanLoadLevels = true;
	}

	void LevelSeedData::PostMake_StandardLoad( const boost::shared_ptr<Level> &level )
	{
		LevelSeedData::PostMake_Standard( level, true, false );
		level->MyGame->MakeScore = boost::make_shared<ScoreScreenLambda>( StatGroup_LEVEL, level );
	}

	void LevelSeedData::PostMake_Standard( const boost::shared_ptr<Level> &level, bool StartMusic, bool ShowMultiplier )
	{
		AddGameObjects_Default( level, false, ShowMultiplier );

		if ( StartMusic )
			level->MyGame->WaitThenDo( 8, boost::make_shared<BOL_StartMusicProxy>() );

		boost::shared_ptr<ILevelConnector> door = boost::static_pointer_cast<ILevelConnector>( level->FindIObject( LevelConnector::EndOfLevelCode ) );
		door->setOnOpen( boost::make_shared<EOL_DoorActionProxy>() );

		level->StartRecording();
	}

	void LevelSeedData::PostMake_StringWorldStandard( const boost::shared_ptr<Level> &level )
	{
		AddGameObjects_Default( level, false, true );

		level->MyGame->WaitThenDo( 8, boost::make_shared<PostMake_StringWorldStandardHelper>() );
	}

	const int &LevelSeedData::getSeed() const
	{
		return Rnd->MySeed;
	}

	void LevelSeedData::setSeed( const int &value )
	{
		Rnd = boost::make_shared<Rand>( value );
	}

	void LevelSeedData::SetTileSet( const std::wstring &name )
	{
		if ( name == std::wstring( L"" ) )
			SetTileSet( name );
		else
			SetTileSet( TileSets::NameLookup[ name ] );
	}

	void LevelSeedData::SetTileSet( const boost::shared_ptr<TileSet> &tileset )
	{
		MyTileSet = tileset;
		MyBackgroundType = MyTileSet == 0 ? 0 : MyTileSet->MyBackgroundType;
	}

	void LevelSeedData::Reset()
	{
		Loaded->setval( false );
		LoadingBegun = false;
		MyGame.reset();

		ReleasePieces();
		PieceSeeds = std::vector<boost::shared_ptr<PieceSeedData> >();
	}

	void LevelSeedData::Release()
	{
#if defined(DEBUG)
		Name += std::wstring( L"_Released" );
#endif

		MySong.reset();
		OnBeginLoad.reset();
		Loaded.reset();
		DefaultHeroType.reset();
		Rnd.reset();
		MyBackgroundType.reset();
		MyTileSet.reset();
		MyCustomDifficulty.reset();

		ReleasePieces();
		PieceSeeds.clear();
		MyGame.reset();
		MyGameType.reset();
		PostMake.reset();
	}

	void LevelSeedData::ReleasePieces()
	{
		if ( PieceSeeds.size() > 0 )
			for ( std::vector<boost::shared_ptr<PieceSeedData> >::const_iterator data = PieceSeeds.begin(); data != PieceSeeds.end(); ++data )
				( *data )->Release();
		PieceSeeds.clear();
	}

	LevelSeedData::LevelSeedData( const boost::shared_ptr<LevelSeedData> &data )
	{
		InitializeInstanceFields();
		setSeed( data->getSeed() );

		MyGameType = data->MyGameType;
		MyBackgroundType = data->MyBackgroundType;
		MyTileSet = data->MyTileSet;
		MyTileSet = data->MyTileSet;

		DefaultHeroType = data->DefaultHeroType;
		MyGameFlags = data->MyGameFlags;

		Length = data->Length;
		PieceLength = data->PieceLength;
		NumPieces = data->NumPieces;

		Difficulty = data->Difficulty;

		MyGeometry = data->MyGeometry;

		Masochistic = data->Masochistic;

		BaseInit();
	}

	LevelSeedData::LevelSeedData()
	{
		InitializeInstanceFields();
		MyBackgroundType = BackgroundType::Random;

		MyGameType.reset();
		setSeed( Tools::GlobalRnd->Rnd->Next() );

		BaseInit();
	}

	void LevelSeedData::BaseInit()
	{
		PieceSeeds = std::vector<boost::shared_ptr<PieceSeedData> >();

		Loaded = boost::make_shared<LockableBool>();
	}

	void LevelSeedData::PreInitialize( const boost::shared_ptr<GameFactory> &Type, int Difficulty, int NumPieces, int Length, const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff )
	{
		this->MyGameType = Type;
		this->Difficulty = Difficulty;
		this->NumPieces = NumPieces;
		this->Length = Length;
		this->MyCustomDifficulty = CustomDiff;
	}

	void LevelSeedData::Init()
	{
		if ( Initialized )
			return;

		if ( MyGameType == ActionGameData::Factory )
			return;

		// FIXME: Implement exceptions?
		//if ( Length == 0 )
		//	throw ( std::exception( std::wstring( L"Invalid length. PreInitialize may not have been called." ) ) );

		Initialize( MyGameType, MyGeometry, NumPieces, Length, MyCustomDifficulty );
	}

	void LevelSeedData::Sanitize()
	{
		int TestNumber;

		TestNumber = Rnd->RndInt( 0, 1000 );
		Tools::Write( Format( _T( "Pre-sanitize: %d" ), TestNumber ).c_str() );

		// Convert random tileset to an actual randomly chosen tileset
		// use global RND.
		if ( MyTileSet == TileSets::Random )
		{
			MyTileSet = CustomLevel_GUI::FreeplayTilesets[ Tools::GlobalRnd->RndInt( 1, CustomLevel_GUI::FreeplayTilesets.size() - 1 ) ];
			//MyTileSet = CustomLevel_GUI.FreeplayTilesets.Choose(Rnd);
			//MyTileSet = new TileSet[] { TileSets.Terrace, TileSets.Dungeon, TileSets.Castle }.Choose(Rnd);

			SetTileSet( MyTileSet );
		}

		// Convert random hero to an actual randomly chosen hero
		if ( DefaultHeroType == BobPhsxRandom::getInstance() )
		{
			DefaultHeroType = BobPhsxRandom::ChooseHeroType();
		}

		// No spaceships or carts on vertical levels
		if ( MyGeometry == LevelGeometry_UP || MyGeometry == LevelGeometry_DOWN )
		{
			if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( DefaultHeroType ) != 0 )
				DefaultHeroType = BobPhsxDouble::getInstance();
			else if ( boost::dynamic_pointer_cast<BobPhsxRocketbox>( DefaultHeroType ) != 0 )
				DefaultHeroType = BobPhsxJetman::getInstance();
		}

		TestNumber = Rnd->RndInt( 0, 1000 );
		Tools::Write( Format( _T( "Post-sanitize: %d" ), TestNumber ).c_str() );
	}

	void LevelSeedData::StandardInit( const boost::shared_ptr<Lambda_2<boost::shared_ptr<PieceSeedData> , boost::shared_ptr<Upgrades> > > &CustomDiff )
	{
		Initialize( boost::make_shared<StandardInitHelper>( CustomDiff ) );

	}

	void LevelSeedData::Initialize( const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff )
	{
		Initialize( MyGameType, MyGeometry, NumPieces, PieceLength, CustomDiff );
	}

	void LevelSeedData::Initialize( const boost::shared_ptr<GameFactory> &factory, LevelGeometry geometry, int NumPieces, int Length, const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff )
	{
		Initialized = true;

		MyGameType = factory;
		MyGeometry = geometry;

		this->NumPieces = NumPieces;
		this->PieceLength = this->Length = Length;

		Sanitize();

		if ( factory == NormalGameData::Factory )
			InitNormal( false, CustomDiff );
	}

	float LevelSeedData::CalcPieceLength( const boost::shared_ptr<PieceSeedData> &data )
	{
		if ( data->Style->MyInitialPlatsType == StyleData::InitialPlatsType_LANDING_ZONE )
		{
			return 3000;
		}

		return 0;
	}

	void LevelSeedData::InitNormal( bool Place, const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff )
	{
		boost::shared_ptr<PieceSeedData> Piece;

		Vector2 Pos = Vector2();

		for ( int i = 0; i < NumPieces; i++ )
		{
			Piece = boost::make_shared<PieceSeedData>( i, MyGeometry, shared_from_this() );
			
            if ( MyMetaGameType != MetaGameType_NONE )
                Piece->MyMetaGameType = MyMetaGameType;

            Piece->Style->Masochistic = Masochistic;			
			
			RndDifficulty::ZeroUpgrades( Piece->MyUpgrades1 );
			RndDifficulty::ZeroUpgrades( Piece->MyUpgrades2 );

			if ( Place )
			{
				Piece->Style->JumpType = StyleData::_JumpType_ALWAYS;

				Piece->Style->MyModParams->Add( boost::make_shared<InitNormalMyModParamsHelper>() );
			}

			if ( CustomDiff != 0 )
				CustomDiff->Apply( Piece );
			else
				RndDifficulty::IntToDifficulty( Piece, MyTileSet );
			if ( Piece->Paths == -1 )
				Piece->Paths = RndDifficulty::ChoosePaths( Piece );

			Piece->Start = Pos;
			if ( MyGeometry == LevelGeometry_RIGHT )
				Pos.X += CalcPieceLength( Piece ) + PieceLength;
			else if ( MyGeometry == LevelGeometry_UP )
				Pos.Y += PieceLength;
			else if ( MyGeometry == LevelGeometry_DOWN )
				Pos.Y -= PieceLength;
			Piece->End = Pos;

			Piece->MyGenData->p1 = Piece->Start;
			Piece->MyGenData->p2 = Piece->End;

			if ( i == 0 )
			{
				Piece->CheckpointsAtStart = false;
				Piece->InitialCheckpointsHere = true;
			}
			else
			{
				Piece->CheckpointsAtStart = true;
				Piece->InitialCheckpointsHere = false;
			}
			PieceSeeds.push_back( Piece );

			if ( i < NumPieces - 1 )
			{
				Piece = boost::make_shared<PieceSeedData>( shared_from_this() );
				Piece->Start = Pos;
				Piece->Ladder = RndDifficulty::ChooseLadder( Difficulty );
				Pos += Level::GetLadderSize( Piece->Ladder );
				DefaultHeroType->ModLadderPiece( Piece );
				PieceSeeds.push_back( Piece );
			}
		}
	}

	void LevelSeedData::InitPlace( const boost::shared_ptr<Lambda_1<boost::shared_ptr<PieceSeedData> > > &CustomDiff )
	{
		InitNormal( true, CustomDiff );
	}

	boost::shared_ptr<Level> LevelSeedData::MakeNewLevel( const boost::shared_ptr<GameData> &game )
	{
		game->MyGameFlags = MyGameFlags;

		//// Get a new random seed
		//if (!LockedSeed)
		//    Seed = game.Rnd.Rnd.Next();


		//// Initialize the random number generator
		//game.Rnd.Rnd = new Random(Seed);

		// Create the level object
		boost::shared_ptr<Level> NewLevel = boost::make_shared<Level>();
		NewLevel->MySourceGame = game;
		NewLevel->DefaultHeroType = DefaultHeroType;
		NewLevel->setMainCamera( boost::make_shared<Camera>() );
		boost::shared_ptr<Camera> cam = NewLevel->getMainCamera();
		cam->Update();

		// Set background and tileset
		NewLevel->MyBackground = Background::Get( MyBackgroundType );
		//NewLevel.MyTileSet = NewLevel.MyBackground.MyTileSet;
		NewLevel->MyTileSet = MyTileSet;

		return NewLevel;
	}

	boost::shared_ptr<GameData> LevelSeedData::Create()
	{
		return Create( false );
	}

	boost::shared_ptr<GameData> LevelSeedData::Create( bool MakeInBackground )
	{
		boost::shared_ptr<GameData> game = MyGameType->Make( shared_from_this(), MakeInBackground );
		game->EndMusicOnFinish = !NoMusicStart;

		return game;
	}

	void LevelSeedData::InitializeInstanceFields()
	{
		Difficulty = 0; NumPieces = 0; Length = 0;
		Initialized = false;

		Saveable = true;
		HasWall = false;

		FadeIn = false;
		FadeOut = false;
		FadeInSpeed = .032f;
		FadeOutSpeed = .02f;
        NewHero = false;
		RepeatHero = false;
		ChapterNameIndex = -1; ShowChapterName = false;
		GiveScoreScreen = false;

        Darkness = false;
        Masochistic = false;
		AlwaysOverrideWaitDoorLength = false;
		MyMetaGameType = MetaGameType_NONE;

		WeatherIntensity = 1;
		NoStartDoor = false;
		LevelNum = -1;
		LevelIndex = -1;
		WaitLengthToOpenDoor = 6;
		OpenDoorSound = false;
		MySong = 0;
		UpgradeStrs = std::vector<std::wstring>();
		PieceHash = 1;
		NoDefaultMake = false;
		NoMusicStart = false;
		Name = std::wstring( L"" );
		PostMake = boost::make_shared<Multicaster_1<boost::shared_ptr<Level> > >();
		ReleaseWhenLoaded = false;
		LoadingBegun = false;
		MyGeometry = LevelGeometry_RIGHT;
		PieceLength = 3000;
		LavaMake = LavaMakeTypes_RANDOM;
		LockedSeed = false;
		MyGameType = NormalGameData::Factory;
		Initialized = false;

#if defined(DEBUG)
		static int debug_count = 0;
		static std::wstring debug_name = std::wstring( L"" );
		debug_count++;
		debug_name = ::ToString( debug_count );
		Name = debug_name;
#endif

	}

}
