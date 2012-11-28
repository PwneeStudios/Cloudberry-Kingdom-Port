#include <global_header.h>

namespace CloudberryKingdom
{

	LevelSeedData::_StartSongProxy::_StartSongProxy( const std::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::_StartSongProxy::Apply( const std::shared_ptr<Level> &level )
	{
		lsd->_StartSong( level );
	}

	void LevelSeedData::_HasWall_ProcessProxy::Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &piece )
	{
		LevelSeedData::_HasWall_Process( level, piece );
	}

	void LevelSeedData::_SetWeather_ProcessProxy::Apply( const std::shared_ptr<Level> &level )
	{
		LevelSeedData::_SetWeather_Process( level );
	}

	void LevelSeedData::_NoStartDoorProxy::Apply( const std::shared_ptr<Level> &level )
	{
		LevelSeedData::_NoStartDoor( level );
	}

	void LevelSeedData::_FadeIn_ProcessProxy::Apply( const std::shared_ptr<Level> &level )
	{
		LevelSeedData::_FadeIn_Process( level );
	}

	LevelSeedData::EOL_StringWorldDoorEndAction_WithFadeProxy::EOL_StringWorldDoorEndAction_WithFadeProxy( const std::shared_ptr<StringWorldGameData> &gameData )
	{
		this->gameData = gameData;
	}

	void LevelSeedData::EOL_StringWorldDoorEndAction_WithFadeProxy::Apply( const std::shared_ptr<Door> &door )
	{
		gameData->EOL_StringWorldDoorEndAction_WithFade( door );
	}

	void LevelSeedData::_FadeOut_ProcessProxy::Apply( const std::shared_ptr<Level> &level )
	{
		LevelSeedData::_FadeOut_Process( level );
	}

	LevelSeedData::ModPieceViaStringProxy::ModPieceViaStringProxy( const std::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::ModPieceViaStringProxy::Apply( const std::shared_ptr<PieceSeedData> &piece )
	{
		lsd->ModPieceViaString( piece );
	}

	LevelSeedData::ModPieceViaHashProxy::ModPieceViaHashProxy( const std::shared_ptr<LevelSeedData> &lsd )
	{
		this->lsd = lsd;
	}

	void LevelSeedData::ModPieceViaHashProxy::Apply( const std::shared_ptr<PieceSeedData> &piece )
	{
		lsd->ModPieceViaHash( piece );
	}

	LevelSeedData::SetToStartSongHelper::SetToStartSongHelper( const std::shared_ptr<EzSong> &song )
	{
		this->song = song;
	}

	void LevelSeedData::SetToStartSongHelper::Apply()
	{
		Tools::SongWad->LoopSong( song );
	}

	LevelSeedData::SetToStartSongPostMakeHelper::SetToStartSongPostMakeHelper( int delay, const std::shared_ptr<Lambda> &songHelper )
	{
		this->delay = delay;
		this->songHelper = songHelper;
	}

	void LevelSeedData::SetToStartSongPostMakeHelper::Apply( const std::shared_ptr<Level> &lvl )
	{
		lvl->MyGame->WaitThenDo( delay, songHelper );
	}

	void LevelSeedData::BOL_StartMusicProxy::Apply()
	{
		LevelSeedData::BOL_StartMusic();
	}

	LevelSeedData::ScoreScreenLambda::ScoreScreenLambda( StatGroup stats, const std::shared_ptr<Level> &level )
	{
		this->stats = stats;
		this->level = level;
	}

	std::shared_ptr<GameObject> LevelSeedData::ScoreScreenLambda::Apply()
	{
		return std::make_shared<ScoreScreen>( stats, level->MyGame );
	}

	void LevelSeedData::EOL_DoorActionProxy::Apply( const std::shared_ptr<Door> &door )
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

	LevelSeedData::StandardInitHelper::StandardInitHelper( const std::shared_ptr<Lambda_2<PieceSeedData*, Upgrades*> > &CustomDiff )
	{
		this->CustomDiff = CustomDiff;
	}

	void LevelSeedData::StandardInitHelper::Apply( const std::shared_ptr<PieceSeedData> &p )
	{
		CustomDiff->Apply( p, p->getu() );
		p->MyUpgrades1->CalcGenData( p->MyGenData->gen1, p->Style );

		RndDifficulty::ZeroUpgrades( p->MyUpgrades2 );
		p->MyUpgrades1->UpgradeLevels.CopyTo( p->MyUpgrades2->UpgradeLevels, 0 );
		p->MyUpgrades2->CalcGenData( p->MyGenData->gen2, p->Style );

		p->Style_MY_INITIAL_PLATS_TYPE = StyleData::InitialPlatsType_DOOR;
		p->Style_MY_FINAL_PLATS_TYPE = StyleData::FinalPlatsType_DOOR;
	}

	void LevelSeedData::InitNormalMyModParamsHelper::Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p )
	{
		p->Style_FILLX_STEP *= 3.1f;
		p->Style_FILLY_STEP *= 1.7f;
	}

bool LevelSeedData::NoDoublePaths = true;

	std::shared_ptr<Level> LevelSeedData::MakeLevel( const std::shared_ptr<GameData> &game )
	{
		return MakeLevel( true, game );
	}

	std::shared_ptr<Level> LevelSeedData::MakeLevel( bool MakeBackground, const std::shared_ptr<GameData> &game )
	{
		this->setSeed( this->getSeed() );
		int TestNumber;

		game->EndMusicOnFinish = !NoMusicStart;

		game->DefaultHeroType = this->DefaultHeroType; // = BobPhsxMario.Instance;

		std::shared_ptr<Level> NewLevel = MakeNewLevel( game );
		NewLevel->Geometry = MyGeometry;
		std::shared_ptr<Camera> cam = NewLevel->getMainCamera();

		// Set lava
		if ( NewLevel->getInfo()->AllowLava )
		//switch (LavaMakeTypes.NeverMake)
		switch ( LavaMake )
		{
			case LavaMakeTypes_ALWAYS_MAKE:
				game->HasLava = true;
				break;
			case LavaMakeTypes_RANDOM:
				game->HasLava = Rnd->RndBool( .38f );
				break;
			default:
				game->HasLava = false;
				break;
		}
		if ( !NewLevel->MyBackground->AllowLava )
			game->HasLava = false;

		NewLevel->MyLevelSeed = this;

		float Height = 0;

		std::shared_ptr<Level> level = 0;
		for ( std::vector<PieceSeedData*>::const_iterator Piece = PieceSeeds.begin(); Piece != PieceSeeds.end(); ++Piece )
		{
			if ( ( *Piece )->Ladder != Level.LadderType_NONE )
			{
				NewLevel->MakeLadder( *Piece );

				if ( PieceSeeds.find( *Piece ) == 0 )
					cam->BLCamBound = cam->Data.Position;

				continue;
			}

			// Ensure that there are no blobs on a single path, multiplayer level
			if ( ( *Piece )->Paths == 1 && !( *Piece )->LockNumOfPaths )
			if ( PlayerManager::GetNumPlayers() > 1 && (*Piece)->MyUpgrades1[ Upgrade_FLY_BLOB ] > 0 )
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



			level = std::make_shared<Level>( true );
			level->MySourceGame = game;
			level->MyLevelSeed = this;
			level->MyTileSet = NewLevel->MyTileSet;
			level->DefaultHeroType = NewLevel->DefaultHeroType;
			level->setMainCamera( std::make_shared<Camera>() );

			cam->Data.Position = ( *Piece )->Start + Vector2( 1000, 0 );
			cam->Update();


			std::shared_ptr<MakeData> makeData = std::make_shared<MakeData>();
			makeData->LevelSeed = this;
			makeData->PieceSeed = *Piece;
			makeData->GenData = ( *Piece )->MyGenData;
			makeData->Index = PieceSeeds.find( *Piece );
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
					level->MakeVertical( 3000, abs( ( *Piece )->End.Y - ( *Piece )->Start.Y ), 0, ReturnEarly, makeData );
					Height += abs( ( *Piece )->End.Y - ( *Piece )->Start.Y );
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

				level->MainEmitter = std::make_shared<ParticleEmitter>( 1000 );
				for ( std::vector<Bob*>::const_iterator bob = level->Bobs.begin(); bob != level->Bobs.end(); ++bob )
					( *bob )->SetColorScheme( ColorSchemeManager::ColorSchemes[ 0 ] );
				level->SetToWatchMake = true;
				NewLevel = level;

				NewLevel->ReturnedEarly = true;

				Tools::CurGameData = NewLevel->MySourceGame;

				return NewLevel;
			}

			if ( PieceSeeds.find( *Piece ) == 0 )
				NewLevel->getMainCamera()->BLCamBound = level->getMainCamera()->BLCamBound;


			level->ResetAll( false );

			// Add checkpoints
			if ( ( *Piece )->CheckpointsAtStart && !( *Piece )->Style_SUPPRESS_CHECKPOINTS )
			{
				for ( int i = 0; i < level->LevelPieces[ 0 ]->NumBobs; i++ )
				{
					std::shared_ptr<Checkpoint> checkpoint = static_cast<Checkpoint*>( game->Recycle->GetObject( ObjectType_CHECKPOINT, false ) );
					checkpoint->Init( level );

					PhsxData data = level->LevelPieces[ 0 ]->StartData[ i ];
					data.Position.X = level->LevelPieces[ 0 ]->StartData[ 0 ]->Position.X;
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
			if ( level->TimeType != Level.TimeTypes_REGULAR )
				NewLevel->TimeType = level->TimeType;

			NewLevel->Par += level->Par; // Add the level's par to the big level's par

			TestNumber = Rnd->RndInt( 0, 1000 );
			Tools::Write( _T( "Test 2 ---> {0}" ), TestNumber );
		}

		// Cleanup lava
		std::vector<BlockBase*> Lavas = std::vector<BlockBase*>();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<BlockBase*>::const_iterator block = NewLevel->Blocks.begin(); block != NewLevel->Blocks.end(); ++block )
			if ( ( *block )->Core->MyType == ObjectType_LAVA_BLOCK )
				Lavas.push_back( *block );

		if ( Lavas.size() > 0 )
		{
			// Find the lowest watermark
			std::shared_ptr<BlockBase> Lowest = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector<BlockBase*>::const_iterator lava = Lavas.begin(); lava != Lavas.end(); ++lava )
				if ( Lowest == 0 || ( *lava )->Box.TR::Y < Lowest->getBox()->TR.Y )
					Lowest = *lava;

			// Extend left and right to cover whole level
			Lowest->Extend( Side_LEFT, NewLevel->BL.X - 5000 );
			Lowest->Extend( Side_RIGHT, NewLevel->TR.X + 5000 );

			// Push down a bit
			Lowest->Extend( Side_TOP, Lowest->getBox()->TR.Y - Rnd->RndFloat(0, 60) );
			if ( Lowest->getBox()->TR.Y < -840 )
				Lowest->CollectSelf();

			// Remove extra lava blocks
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector<BlockBase*>::const_iterator lava = Lavas.begin(); lava != Lavas.end(); ++lava )
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

	void LevelSeedData::MakeTheBackground( const std::shared_ptr<Level> &NewLevel, float Height )
	{
		NewLevel->MyBackground->Init( NewLevel );
	}

int LevelSeedData::ForcedReturnEarly = 0;

	int LevelSeedData::SetReturnEarly( const std::shared_ptr<PieceSeedData> &Piece )
	{
		int ReturnEarly = ForcedReturnEarly;

		return ReturnEarly;
	}

const std::wstring LevelSeedData::WallFlag = _T( "wall" );
const std::wstring LevelSeedData::FadeInFlag = _T( "fadein" );
const std::wstring LevelSeedData::FadeOutFlag = _T( "fadeout" );
const std::wstring LevelSeedData::WeatherIntensityFlag = _T( "weather" );
const std::wstring LevelSeedData::NoStartDoorFlag = _T( "nostartdoor" );
const std::wstring LevelSeedData::LevelFlag = _T( "level" );
const std::wstring LevelSeedData::WaitLengthToOpenDoorString = _T( "opendoor" );
const std::wstring LevelSeedData::OpenDoorSoundFlag = _T( "opendoorsound" );
const std::wstring LevelSeedData::SongString = _T( "song" );

	void LevelSeedData::ProcessSpecial()
	{
		if ( HasWall )
		{
			std::shared_ptr<PieceSeedData> p = PieceSeeds[ 0 ];
			//p.Style.ComputerWaitLengthRange = new Vector2(4, 23);

			p->Style_MY_MOD_PARAMS->Add( std::make_shared<_HasWall_ProcessProxy>() );
		}

		if ( NoStartDoor )
			PostMake->Add( std::make_shared<_NoStartDoorProxy>() );

		if ( FadeIn )
			PostMake->Add( std::make_shared<_FadeIn_ProcessProxy>() );

		if ( FadeOut )
			PostMake->Add( std::make_shared<_FadeOut_ProcessProxy>() );

		if ( WeatherIntensity != 1 )
			PostMake->Add( std::make_shared<_SetWeather_ProcessProxy>() );

		if ( MySong != 0 )
			PostMake->Add( std::make_shared<_StartSongProxy>( this ) );
	}

	void LevelSeedData::_StartSong( const std::shared_ptr<Level> &level )
	{
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		Tools::SongWad->Next( MySong );
		Tools::SongWad->PlayNext = true;
	}

	void LevelSeedData::_HasWall_Process( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &piece )
	{
		std::shared_ptr<NormalBlock_Parameters> Params = static_cast<NormalBlock_Parameters*>( piece->Style_FIND_PARAMS( NormalBlock_AutoGen::getInstance() ) );
		std::shared_ptr<Wall> wall = Params->SetWall( LevelGeometry_RIGHT );
		wall->Space = 20;
		wall->MyBufferType = Wall::BufferType_SPACE;
		piece->CamZoneStartAdd.X = -2000;
		wall->StartOffset = -600;
		wall->Speed = 17.5f;
		wall->InitialDelay = 72;
	}

	void LevelSeedData::_SetWeather_Process( const std::shared_ptr<Level> &level )
	{
		level->MyBackground->SetWeatherIntensity( level->MyLevelSeed->WeatherIntensity );
	}

	void LevelSeedData::_NoStartDoor( const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<CloudberryKingdom::Door> door = level->getStartDoor();
		if ( door == 0 )
			return;
		door->CollectSelf();
	}

	void LevelSeedData::_FadeIn_Process( const std::shared_ptr<Level> &level )
	{
		level->MyGame->PhsxStepsToDo += 2;
		level->MyGame->AddGameObject( std::make_shared<FadeInObject>() );
	}

	void LevelSeedData::_FadeOut_Process( const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<StringWorldGameData> stringworld = dynamic_cast<StringWorldGameData*>( Tools::WorldMap );
		std::shared_ptr<Door> door = dynamic_cast<Door*>( level->FindIObject( LevelConnector::EndOfLevelCode ) );

		if ( 0 != stringworld && 0 != door )
		{
			door->setOnEnter( std::make_shared<EOL_StringWorldDoorEndAction_WithFadeProxy>( stringworld ) );
		}
	}

	void LevelSeedData::DefaultRead( const std::wstring &str )
	{
		int i = abs( str.GetHashCode() );

		// Length
		Length = PieceLength = static_cast<int>( ( static_cast<unsigned int>( i * 997 ) ) % 7000 + 5000 );

		// Tileset
		i /= 2;
		std::shared_ptr<std::vector<void*> > tilesets = TileSets::NameLookup.Keys::ToList();
		std::shared_ptr<TileSet> tileset = CustomLevel_GUI::FreeplayTilesets[ ( i + 23 ) % CustomLevel_GUI::FreeplayTilesets.size() ];
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

	void LevelSeedData::ReadString( const std::wstring &str )
	{
		DefaultRead( str );
		UpgradeStrs.clear();

		str = Tools::RemoveComment_SlashStyle( str );
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		std::vector<std::wstring> bits = str.Split( L';' );

		for ( int i = 0; i < bits.size(); i++ )
		{
			std::wstring identifier, data;

			int index = bits[ i ]->find( _T( ":" ) );

			if ( index <= 0 )
			{
				identifier = bits[ i ];
				data = _T( "" );
			}
			else
			{
				identifier = bits[ i ]->substr( 0, index );
				data = bits[ i ]->substr( index + 1 );
			}

			std::vector<std::wstring> terms;

			// Seed [This must come first]
			if ( identifier.ToLower() == _T("s") )
			{
				try
				{
					setSeed( int::Parse( data ) );
				}
				catch ( ... )
				{
					setSeed( data.GetHashCode() );
				}
			}
			// Game type
			else if ( identifier.ToLower() == _T("g") )
			{
				MyGameType = NormalGameData::Factory;
				//try
				//{
				//	MyGameType = GameData::FactoryDict[ data ];
				//}
				//catch ( ... )
				//{
				//	MyGameType = NormalGameData::Factory;
				//}
			}
			// Geometry
			else if ( identifier.ToLower() == _T("geo") )
			{
				try
				{
					MyGeometry = static_cast<LevelGeometry>( int::Parse( data ) );
				}
				catch ( ... )
				{
					MyGeometry = LevelGeometry_RIGHT;
				}
			}
			// Hero [This must come before "ph:"]
			else if ( identifier.ToLower() == _T("h") )
			{
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
					terms = data.Split( L',' );
					if ( terms.size() == 4 )
						DefaultHeroType = BobPhsx::MakeCustom( terms[ 0 ], terms[ 1 ], terms[ 2 ], terms[ 3 ] );
					else
						DefaultHeroType = BobPhsxNormal::getInstance();
			}
			// Custom physics [This must come after "h:"]
			else if ( identifier.ToLower() == _T("ph") )
			{
					BobPhsx::CustomPhsxData custom = BobPhsx::CustomPhsxData();
					custom.Init( data );
					DefaultHeroType->SetCustomPhsx( custom );
			}
			// Tileset
			else if ( identifier.ToLower() == _T("t") )
			{
					MyTileSet.reset();
					if ( data.length() > 0 )
					{
						try
						{
							SetTileSet( data );
						}
						catch ( ... )
						{
							MyTileSet.reset();
						}
					}
					if ( MyTileSet == 0 )
						SetTileSet( _T( "castle" ) );
			}
			// Number of pieces
			else if ( identifier.ToLower() == _T("n") )
			{
					try
					{
						NumPieces = int::Parse( data );
						NumPieces = CoreMath::Restrict( 1, 5, NumPieces );
					}
					catch ( ... )
					{
						NumPieces = 1;
					}
			}
			// Length
			else if ( identifier.ToLower() == _T("l") )
			{
					try
					{
						Length = int::Parse( data );
						Length = CoreMath::Restrict( 2000, 50000, Length );
						PieceLength = Length;
					}
					catch ( ... )
					{
						PieceLength = Length = 5000;
					}
			}
			// Upgrades
			else if ( identifier.ToLower() == _T("u") )
			{
					UpgradeStrs.push_back( data );
			}
			// Wall
			else if ( identifier.ToLower() == WallFlag )
			{
					HasWall = true;
			}
			// Fade In
			else if ( identifier.ToLower() == FadeInFlag )
			{
					FadeIn = true;
			}
			// Fade Out
			else if ( identifier.ToLower() == FadeOutFlag )
			{
					FadeOut = true;
			}
			// No start door
			else if ( identifier.ToLower() == NoStartDoorFlag )
			{
					NoStartDoor = true;
			}
			// Level number
			else if ( identifier.ToLower() == LevelFlag )
			{
					LevelNum = int::Parse( data );
			}
			// Weather intensity
			else if ( identifier.ToLower() == WeatherIntensityFlag )
			{
					try
					{
						WeatherIntensity = float::Parse( data );
					}
					catch ( ... )
					{
						WeatherIntensity = 1;
					}
			}
			// Wait length to open door
			else if ( identifier.ToLower() == WaitLengthToOpenDoorString )
			{
					try
					{
						WaitLengthToOpenDoor = int::Parse( data );
					}
					catch ( ... )
					{
						WaitLengthToOpenDoor = 6;
					}
			}
			// Song to play at beginning of level
			else if ( identifier.ToLower() == SongString )
			{
					try
					{
						MySong = Tools::SongWad->FindByName( data );
					}
					catch ( ... )
					{
						MySong.reset();
					}
			}
			// Open door sound
			else if ( identifier.ToLower() == OpenDoorSoundFlag )
			{
					OpenDoorSound = true;

			}
			else
			{
			}
		}

		// Error catch.
		if ( dynamic_cast<BobPhsxMeat*>( DefaultHeroType ) != 0 )
		{
			MyGeometry = LevelGeometry_UP;
			NumPieces = 1;
		}
		if ( dynamic_cast<BobPhsxRocketbox*>( DefaultHeroType ) != 0 )
		{
			MyGeometry = LevelGeometry_RIGHT;
			NumPieces = 1;
		}

		// If no upgrade was provided, zero everything.
		if ( UpgradeStrs.empty() )
		{
			UpgradeStrs.push_back( _T( "" ) );
			Initialize( std::make_shared<ModPieceViaHashProxy>( this ) );
		}
		else
		{
			Initialize( std::make_shared<ModPieceViaStringProxy>( this ) );
		}

		ProcessSpecial();
	}

	std::wstring LevelSeedData::ToString()
	{
		int _version = 0;
		std::wstring version = StringConverterHelper::toString( _version ) + _T( ";" );

		// Seed
		std::wstring seed = _T( "s:" ) + StringConverterHelper::toString( getSeed() ) + _T(";");

		// Game
		std::wstring game = _T( "" );
		if ( MyGameType != NormalGameData::Factory )
		{
			return _T( "!This level can not be saved!" );
		}

		// Geometry
		std::wstring geometry = _T( "" );
		if ( MyGeometry != LevelGeometry_RIGHT )
			geometry = _T( "geo:" ) + static_cast<int>( MyGeometry ) + _T( ";" );

		// Hero
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
		std::wstring hero = _T( "h:" ) + DefaultHeroType->Specification.ToString() + _T(";");

		// Custom phsx
		std::wstring customphsx = _T( "" );
		if ( DefaultHeroType->CustomPhsx )
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			customphsx = DefaultHeroType->MyCustomPhsxData.ToString();

		// Tileset
		std::wstring tileset = _T( "t:" ) + MyTileSet->Name + _T( ";" );

		// Pieces
		std::wstring pieces = _T( "n:" ) + NumPieces + _T( ";" );

		// Length
		std::wstring length = _T( "l:" ) + StringConverterHelper::toString( Length ) + _T( ";" );

		// Upgrades
		std::wstring upgrades = _T( "" );
		for ( std::vector<PieceSeedData*>::const_iterator p = PieceSeeds.begin(); p != PieceSeeds.end(); ++p )
		{
			if ( ( *p )->Ladder != Level.LadderType_NONE )
				continue;

			upgrades += _T( "u:" );

			std::vector<float> upgrade_levels = ( *p )->MyUpgrades1->UpgradeLevels;
			for ( int i = 0; i < upgrade_levels.size(); i++ )
			{
				upgrades += StringConverterHelper::toString( upgrade_levels[ i ] );
				if ( i + 1 < upgrade_levels.size() )
					upgrades += _T( "," );
			}
			upgrades += _T( ";" );
		}

		// Build final string
		std::wstring str = version + seed + game + geometry + hero + customphsx + tileset + pieces + length + upgrades;

		// Add special flags
		if ( HasWall )
			str += WallFlag + _T( ";" );

		return str;
	}

	void LevelSeedData::ModPieceViaString( const std::shared_ptr<PieceSeedData> &piece )
	{
		// Break the data up by commas
		int index = CoreMath::Restrict( 0, UpgradeStrs.size() - 1, piece->MyPieceIndex );
//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
		std::vector<std::wstring> terms = UpgradeStrs[ index ].Split( L',' );

		// Try and load the data into the upgrade array.
		try
		{
			for ( int i = 0; i < terms.size(); i++ )
				piece->MyUpgrades1->UpgradeLevels[ i ] = float::Parse( terms[ i ] );
		}
		catch ( ... )
		{
			// If we fail, zero all the upgrades.
			piece->MyUpgrades1->Zero();
		}

		piece->StandardClose();
	}

	void LevelSeedData::ModPieceViaHash( const std::shared_ptr<PieceSeedData> &piece )
	{
		PieceHash = abs( PieceHash );
		PieceHash *= 997;
		PieceHash %= 1024;
		PieceHash = abs( PieceHash );

		int Bias = static_cast<int>( 75 - static_cast<unsigned int>( PieceHash ) % 50 );

		for ( int i = 0; i < piece->MyUpgrades1->UpgradeLevels.size(); i++ )
		{
			int n1 = PieceHash | ( 2 + 8 + 32 + 128 + 512 );
			int n2 = PieceHash | ( 1 + 4 + 16 + 64 + 256 );

			int value = 0;
			if ( ( n1 * n2 + static_cast<int>( exp( i ) ) ) % 100 > Bias )
				value = ( n1 + n1 * n2 ) % 10;

			piece->MyUpgrades1->UpgradeLevels[ i ] = CoreMath::Restrict( 0, 10, value );
		}

		piece->MyUpgrades1[ Upgrade_CONVEYOR ] = 0;
	piece->MyUpgrades1[ Upgrade_FIRESNAKE ] = piece->MyUpgrades1[ Upgrade_CONVEYOR ];

		piece->StandardClose();
	}

	void LevelSeedData::RandomHero( const std::shared_ptr<BobPhsx> &Hero, int Hash )
	{
		int Length = BobPhsx::CustomPhsxData::Length;
		std::vector<float> vals = std::vector<float>( Length );

		for ( int i = 0; i < Length; i++ )
		{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			var value = i * PieceHash * PieceHash + PieceHash + i * i;

			vals[ i ] = CoreMath::Restrict( BobPhsx::CustomPhsxData::Bounds( i ).MinValue, BobPhsx::CustomPhsxData::Bounds( i ).MaxValue, value );
			vals[ i ] = CoreMath::Restrict( 0, 1, value );
		}

		Hero->MyCustomPhsxData.Init( vals );
	}

	std::wstring LevelSeedData::SuggestedName()
	{
		return DefaultHeroType->Name + _T( "_" ) + StringConverterHelper::toString( getSeed() );
	}

	std::wstring LevelSeedData::GetNameFromSeedStr( const std::wstring &seed )
	{
		int index_name = seed.find( _T( "name:" ) ) + 5;
		int index_name_end = seed.find( _T( ";" ), index_name );
		std::wstring name = seed.substr( index_name, index_name_end - index_name );

		return name;
	}

	void LevelSeedData::SetToStartSong( const std::shared_ptr<EzSong> &song )
	{
		SetToStartSong( song, 5 );
	}

	void LevelSeedData::SetToStartSong( const std::shared_ptr<EzSong> &song, int delay )
	{
		NoMusicStart = true;
		PostMake->Add( std::make_shared<SetToStartSongPostMakeHelper>( delay, std::make_shared<SetToStartSongHelper>( song ) ) );
	}

	void LevelSeedData::AddGameObjects_Default( const std::shared_ptr<Level> &level, bool global, bool ShowMultiplier )
	{
		level->MyGame->AddGameObject( std::make_shared<HintGiver>(), HelpMenu::MakeListener(), std::make_shared<PerfectScoreObject>(global, ShowMultiplier) );

		level->MyGame->AddGameObject( InGameStartMenu::MakeListener() );
	}

	void LevelSeedData::AddGameObjects_BareBones( const std::shared_ptr<Level> &level, bool global )
	{
		level->MyGame->AddGameObject( InGameStartMenu::MakeListener(), std::make_shared<PerfectScoreObject>(global, true) );
	}

	void LevelSeedData::BOL_StartMusic()
	{
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		Tools::SongWad->Shuffle();
		Tools::SongWad->Start( true );
	}

	void LevelSeedData::PostMake_EnableLoad( const std::shared_ptr<Level> &level )
	{
		level->CanLoadLevels = true;
	}

	void LevelSeedData::PostMake_StandardLoad( const std::shared_ptr<Level> &level )
	{
		LevelSeedData::PostMake_Standard( level, true, false );
		level->MyGame->MakeScore = std::make_shared<ScoreScreenLambda>( StatGroup_LEVEL, level );
	}

	void LevelSeedData::PostMake_Standard( const std::shared_ptr<Level> &level, bool StartMusic, bool ShowMultiplier )
	{
		AddGameObjects_Default( level, false, ShowMultiplier );

		if ( StartMusic )
			level->MyGame->WaitThenDo( 8, std::make_shared<BOL_StartMusicProxy>() );

		std::shared_ptr<ILevelConnector> door = static_cast<ILevelConnector*>( level->FindIObject( LevelConnector::EndOfLevelCode ) );
		door->setOnOpen( std::make_shared<EOL_DoorActionProxy>() );

		level->StartRecording();
	}

	void LevelSeedData::PostMake_StringWorldStandard( const std::shared_ptr<Level> &level )
	{
		AddGameObjects_Default( level, false, true );

		level->MyGame->WaitThenDo( 8, std::make_shared<PostMake_StringWorldStandardHelper>() );
	}

	const int &LevelSeedData::getSeed() const
	{
		return Rnd->MySeed;
	}

	void LevelSeedData::setSeed( const int &value )
	{
		Rnd = std::make_shared<Rand>( value );
	}

	void LevelSeedData::SetTileSet( const std::wstring &name )
	{
		if ( name == _T( "" ) )
			SetTileSet( static_cast<TileSet*>( 0 ) );
		else
			SetTileSet( TileSets::NameLookup[ name ] );
	}

	void LevelSeedData::SetTileSet( const std::shared_ptr<TileSet> &tileset )
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
		PieceSeeds = std::vector<PieceSeedData*>();
	}

	void LevelSeedData::Release()
	{
		ReleasePieces();
		PieceSeeds.clear();
		MyGame.reset();
		MyGameType.reset();
		PostMake.reset();
	}

	void LevelSeedData::ReleasePieces()
	{
		if ( PieceSeeds.size() > 0 )
			for ( std::vector<PieceSeedData*>::const_iterator data = PieceSeeds.begin(); data != PieceSeeds.end(); ++data )
				( *data )->Release();
		PieceSeeds.clear();
	}

	LevelSeedData::LevelSeedData( const std::shared_ptr<LevelSeedData> &data )
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
		PieceSeeds = std::vector<PieceSeedData*>();

		Loaded = std::make_shared<LockableBool>();
	}

	void LevelSeedData::PreInitialize( const std::shared_ptr<GameFactory> &Type, int Difficulty, int NumPieces, int Length, const std::shared_ptr<Lambda_1<PieceSeedData*> > &CustomDiff )
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

		if ( Length == 0 )
			throw ( std::exception( _T( "Invalid length. PreInitialize may not have been called." ) ) );

		Initialize( MyGameType, MyGeometry, NumPieces, Length, MyCustomDifficulty );
	}

	void LevelSeedData::Sanitize()
	{
		int TestNumber;

		TestNumber = Rnd->RndInt( 0, 1000 );
		Tools::Write( std::wstring::Format( _T( "Pre-sanitize: {0}" ), TestNumber ) );

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
			if ( dynamic_cast<BobPhsxSpaceship*>( DefaultHeroType ) != 0 )
				DefaultHeroType = BobPhsxDouble::getInstance();
			else if ( dynamic_cast<BobPhsxRocketbox*>( DefaultHeroType ) != 0 )
				DefaultHeroType = BobPhsxJetman::getInstance();
		}

		TestNumber = Rnd->RndInt( 0, 1000 );
		Tools::Write( std::wstring::Format( _T( "Post-sanitize: {0}" ), TestNumber ) );
	}

	void LevelSeedData::StandardInit( const std::shared_ptr<Lambda_2<PieceSeedData*, Upgrades*> > &CustomDiff )
	{
		Initialize( std::make_shared<StandardInitHelper>( CustomDiff ) );

	}

	void LevelSeedData::Initialize( const std::shared_ptr<Lambda_1<PieceSeedData*> > &CustomDiff )
	{
		Initialize( MyGameType, MyGeometry, NumPieces, PieceLength, CustomDiff );
	}

	void LevelSeedData::Initialize( const std::shared_ptr<GameFactory> &factory, LevelGeometry geometry, int NumPieces, int Length, const std::shared_ptr<Lambda_1<PieceSeedData*> > &CustomDiff )
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

	float LevelSeedData::CalcPieceLength( const std::shared_ptr<PieceSeedData> &data )
	{
		if ( data->Style_MY_INITIAL_PLATS_TYPE == StyleData::InitialPlatsType_LANDING_ZONE )
		{
			return 3000;
		}

		return 0;
	}

	void LevelSeedData::InitNormal( bool Place, const std::shared_ptr<Lambda_1<PieceSeedData*> > &CustomDiff )
	{
		std::shared_ptr<PieceSeedData> Piece;

		Vector2 Pos = Vector2();

		for ( int i = 0; i < NumPieces; i++ )
		{
			Piece = std::make_shared<PieceSeedData>( i, MyGeometry, this );
			RndDifficulty::ZeroUpgrades( Piece->MyUpgrades1 );
			RndDifficulty::ZeroUpgrades( Piece->MyUpgrades2 );

			if ( Place )
			{
				Piece->Style_JUMP_TYPE = StyleData::_JumpType_ALWAYS;

				Piece->Style_MY_MOD_PARAMS->Add( std::make_shared<InitNormalMyModParamsHelper>() );
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
				Piece = std::make_shared<PieceSeedData>( this );
				Piece->Start = Pos;
				Piece->Ladder = RndDifficulty::ChooseLadder( Difficulty );
				Pos += Level::GetLadderSize( Piece->Ladder );
				DefaultHeroType->ModLadderPiece( Piece );
				PieceSeeds.push_back( Piece );
			}
		}
	}

	void LevelSeedData::InitPlace( const std::shared_ptr<Lambda_1<PieceSeedData*> > &CustomDiff )
	{
		InitNormal( true, CustomDiff );
	}

	std::shared_ptr<Level> LevelSeedData::MakeNewLevel( const std::shared_ptr<GameData> &game )
	{
		game->MyGameFlags = MyGameFlags;

		//// Get a new random seed
		//if (!LockedSeed)
		//    Seed = game.Rnd.Rnd.Next();


		//// Initialize the random number generator
		//game.Rnd.Rnd = new Random(Seed);

		// Create the level object
		std::shared_ptr<Level> NewLevel = std::make_shared<Level>();
		NewLevel->MySourceGame = game;
		NewLevel->DefaultHeroType = DefaultHeroType;
		std::shared_ptr<Camera> cam = NewLevel->setMainCamera( std::make_shared<Camera>() );
		cam->Update();

		// Set background and tileset
		NewLevel->MyBackground = Background::Get( MyBackgroundType );
		//NewLevel.MyTileSet = NewLevel.MyBackground.MyTileSet;
		NewLevel->MyTileSet = MyTileSet;

		return NewLevel;
	}

	std::shared_ptr<GameData> LevelSeedData::Create()
	{
		return Create( false );
	}

	std::shared_ptr<GameData> LevelSeedData::Create( bool MakeInBackground )
	{
		std::shared_ptr<GameData> game = MyGameType->Make( this, MakeInBackground );
		game->EndMusicOnFinish = !NoMusicStart;

		return game;
	}

	void LevelSeedData::InitializeInstanceFields()
	{
		Saveable = true;
		HasWall = false;
		FadeIn = false;
		FadeOut = false;
		WeatherIntensity = 1;
		NoStartDoor = false;
		LevelNum = -1;
		WaitLengthToOpenDoor = 6;
		OpenDoorSound = false;
		MySong = 0;
		UpgradeStrs = std::vector<std::wstring>();
		PieceHash = 1;
		NoDefaultMake = false;
		NoMusicStart = false;
		Name = _T( "" );
		PostMake = std::make_shared<Multicaster_1<Level*> >();
		ReleaseWhenLoaded = false;
		LoadingBegun = false;
		MyGeometry = LevelGeometry_RIGHT;
		PieceLength = 3000;
		LavaMake = LavaMakeTypes_RANDOM;
		LockedSeed = false;
		MyGameType = NormalGameData::Factory;
		Initialized = false;
	}

}
