#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	EOL_StringWorldDoorActionProxy::EOL_StringWorldDoorActionProxy( const std::shared_ptr<StringWorldGameData> &gameData )
	{
		this->gameData = gameData;
	}

	void EOL_StringWorldDoorActionProxy::Apply( const std::shared_ptr<Door> &door )
	{
		gameData->EOL_StringWorldDoorAction( door );
	}

	EOL_StringWorldDoorEndActionProxy::EOL_StringWorldDoorEndActionProxy( const std::shared_ptr<StringWorldGameData> &gameData )
	{
		this->gameData = gameData;
	}

	void EOL_StringWorldDoorEndActionProxy::Apply( const std::shared_ptr<Door> &door )
	{
		gameData->EOL_StringWorldDoorEndAction( door );
	}

	void EOG_StandardDoorActionProxy::Apply( const std::shared_ptr<Door> &door )
	{
		StringWorldGameData::EOG_StandardDoorAction( door );
	}

	StringWorldGameData::StartOfLevelLambda::StartOfLevelLambda( const std::shared_ptr<StringWorldGameData> &g, const std::shared_ptr<Level> &level, bool Hold_FirstLevelHasBegun )
	{
		this->g = g;
		this->level = level;
		this->Hold_FirstLevelHasBegun = Hold_FirstLevelHasBegun;
	}

	bool StringWorldGameData::StartOfLevelLambda::Apply()
	{
		if ( level->MyGame->PauseGame )
			return false;

		if ( g->FirstDoorAction || Hold_FirstLevelHasBegun )
			g->StartOfLevelDoorAction( level );

		// Start music
		if ( g->StartLevelMusic != 0 )
			g->StartLevelMusic->Apply( g );

		return true;
	}

	void StringWorldGameData::DefaultStartLevelMusicProxy::Apply( const std::shared_ptr<StringWorldGameData> &stringworld )
	{
		StringWorldGameData::DefaultStartLevelMusic( stringworld );
	}

	StringWorldGameData::OpenAndShowLambda::OpenAndShowLambda( const std::shared_ptr<StringWorldGameData> &g, const std::shared_ptr<Level> &level, const std::shared_ptr<Door> &door, const std::shared_ptr<LevelSeedData> &CurLevelSeed )
	{
		this->g = g;
		this->level = level;
		this->door = door;
		this->CurLevelSeed = CurLevelSeed;
	}

	void StringWorldGameData::OpenAndShowLambda::Apply()
	{
		g->_StartOfLevelDoorAction__OpenAndShow( level, door, CurLevelSeed->OpenDoorSound );
	}

	StringWorldGameData::FinishLambda::FinishLambda( const std::shared_ptr<StringWorldGameData> &g )
	{
		this->g = g;
	}

	void StringWorldGameData::FinishLambda::Apply( bool val )
	{
		g->Finish( val );
	}

	StringWorldGameData::CloseDoorAndAbsorbLambda::CloseDoorAndAbsorbLambda( const std::shared_ptr<Door> &door )
	{
		this->door = door;
	}

	void StringWorldGameData::CloseDoorAndAbsorbLambda::Apply()
	{
		// Close the door
		door->SetLock( true, false, true );

		// Absorb level stats
		PlayerManager::AbsorbTempStats();
		PlayerManager::AbsorbLevelStats();
	}

	StringWorldGameData::StartNextLevelLambda::StartNextLevelLambda( const std::shared_ptr<StringWorldGameData> &g )
	{
		this->g = g;
	}

	bool StringWorldGameData::StartNextLevelLambda::Apply()
	{
		// If the next level is loaded, start the level
		if ( g->NextIsReady() )
		{
			g->WaitingForNext = false;

			g->SetLevel();
			g->LevelBegin( Tools::CurLevel );

			return true;
		}
		// Otherwise wait
		else
			return false;
	}

	std::shared_ptr<GameData> StringWorldGameData::Factory( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return 0;
	}

	void StringWorldGameData::Release()
	{
		if ( Released )
			return;

		if ( NextLevelSeed != 0 )
		{
			NextLevelSeed->MyGame->Release();
			NextLevelSeed->Release();
		}
		NextLevelSeed.reset();

		CurLevelSeed.reset();
		LastLevelSeedSet.reset();
		OnBeginLoad.reset();
		OnLevelBegin.reset();
		OnSwapToLevel.reset();
		OnSwapToFirstLevel.reset();
		OnSwapToLastLevel.reset();
		StartLevelMusic.reset();

		if ( Tools::WorldMap == this )
			Tools::WorldMap.reset();

		GameData::Release();
	}

	std::shared_ptr<LevelSeedData> StringWorldGameData::GetSeed( int Index )
	{
		if ( GetSeedFunc == 0 )
			return 0;
		else
			return GetSeedFunc( Index );
	}

	bool StringWorldGameData::NextIsReady()
	{
		if ( NextLevelSeed == 0 )
			return false;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( NextLevelSeed->Loaded )
		{
			return NextLevelSeed->Loaded->getval();
		}
	}

	void StringWorldGameData::LevelBegin( const std::shared_ptr<Level> &level )
	{
		Recycler::DumpMetaBin();

		if ( OnLevelBegin != 0 )
		{
			bool result = OnLevelBegin->Apply( level );
			if ( result )
			{
				return;
			}
		}

		BeginningCloseDoor( level );

		bool Hold_FirstLevelHasBegun = FirstLevelHasBegun;
		if ( level->MyGame != 0 )
		{
			level->MyGame->AddToDo( std::make_shared<StartOfLevelLambda>( this, level, Hold_FirstLevelHasBegun ) );

			level->MyGame->PhsxStepsToDo += 2;
		}

		FirstLevelHasBegun = true;
	}

	void StringWorldGameData::DefaultStartLevelMusic( const std::shared_ptr<StringWorldGameData> &stringworld )
	{
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );

		if ( !stringworld->FirstLevelHasLoaded )
			Tools::SongWad->Next();
	}

	void StringWorldGameData::BeginningCloseDoor( const std::shared_ptr<Level> &level )
	{
		// Find the initial door
		std::shared_ptr<Door> door = dynamic_cast<Door*>( level->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 == door )
			return;

		// Close the door
		door->SetLock( true, true, false );
		door->HideBobs();

		level->Finished = true;
	}

	void StringWorldGameData::StartOfLevelDoorAction( const std::shared_ptr<Level> &level )
	{
		std::shared_ptr<GameData> game = level->MyGame;

		if ( game == 0 )
			return;

		// Find the initial door
		std::shared_ptr<Door> door = dynamic_cast<Door*>( level->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 == door )
		{

			return;
		}

		// Open the door and show players
		int Wait = WaitLengthToOpenDoor_FirstLevel;

		if ( CurLevelIndex > 0 )
			Wait = CurLevelSeed->WaitLengthToOpenDoor;
		game->WaitThenDo( Wait, std::make_shared<OpenAndShowLambda>( this, level, door, CurLevelSeed ) );
	}

	void StringWorldGameData::_StartOfLevelDoorAction__OpenAndShow( const std::shared_ptr<Level> &level, const std::shared_ptr<Door> &door, bool OpenDoorSound )
	{
		// Whether to play a sound for the door opening
		bool sound = false;
		if ( CurLevelIndex == StartIndex || OpenDoorSound )
			sound = true;

		level->Finished = false;
		door->SetLock( false, false, sound );
		door->ShowBobs();
	}

	bool StringWorldGameData::LevelIsLoaded( const std::shared_ptr<LevelSeedData> &data )
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( data->Loaded )
		{
			return data->Loaded->getval();
		}
	}

	void StringWorldGameData::SetLevel()
	{
		if ( NextLevelSeed->MyGame != 0 )
		{
			// Check for last level
			if ( NextIsLast() )
			{
				std::shared_ptr<ObjectBase> obj = NextLevelSeed->MyGame->MyLevel->FindIObject( LevelConnector::EndOfLevelCode );

				std::shared_ptr<Door> door = dynamic_cast<Door*>( obj );
				if ( 0 != door )
					door->setOnOpen( std::make_shared<EOG_StandardDoorActionProxy>() );
			}

			// Replace all Bobs with new Bobs (to handle newly joined players)
			NextLevelSeed->MyGame->UpdateBobs();
			NextLevelSeed->MyGame->Reset();
		}

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( NextLevelSeed->Loaded )
		{
			// If game hasn't loaded yet, bring loading screen
			if ( !NextLevelSeed->Loaded->getval() )
			{
				if ( !NextLevelSeed->LoadingBegun )
					Tools::Break();

				if ( !Tools::ShowLoadingScreen )
				{
					Tools::CurLevel = MyLevel;
					Tools::CurGameData = this;
					Tools::BeginLoadingScreen( true );
				}
			}
			else
			{
				SwapToLevel();
				Tools::WorldMap = this;
			}
		}
	}

	void StringWorldGameData::Finish( bool Replay )
	{
		GameData::Finish( Replay );
	}

	bool StringWorldGameData::NextIsLast()
	{
		return NextLevelSeed->Name == _T( "Last" );
	}

	void StringWorldGameData::SwapToLevel()
	{
		Tools::CurGameData = NextLevelSeed->MyGame;
		Tools::CurLevel = NextLevelSeed->MyGame->MyLevel;

		// Perform actions if this is the first level being swapped in.
		if ( !FirstLevelSwappedIn )
		{
			if ( OnSwapToFirstLevel != 0 )
				OnSwapToFirstLevel->Apply( NextLevelSeed );
			FirstLevelSwappedIn = true;
		}

		// Perform actions if this is the last level being swapped in.
		if ( NextIsLast() )
		{
			if ( OnSwapToLastLevel != 0 )
				OnSwapToLastLevel->Apply( NextLevelSeed );
		}

		// Stores the GameObjects in the current game marked as 'PreventRelease'
		std::vector<GameObject*> ObjectsToSave = std::vector<GameObject*>();

		if ( CurLevelSeed != 0 && NextLevelSeed != CurLevelSeed )
		{
			if ( CurLevelSeed->MyGame->Loading )
				throw InvalidOperationException( _T( "Swapping from a level that hasn't finished loading!" ) );

			for ( std::vector<GameObject*>::const_iterator obj = CurLevelSeed->MyGame->MyGameObjects.begin(); obj != CurLevelSeed->MyGame->MyGameObjects.end(); ++obj )
				if ( ( *obj )->PreventRelease )
					ObjectsToSave.push_back( *obj );

			CurLevelSeed->MyGame->Release();
			CurLevelSeed->Loaded->setval( false );
			CurLevelSeed->Release();
		}

		CurLevelSeed = NextLevelSeed;
		CurLevelIndex = NextLevelIndex;

		//Tools.CurGameData = CurLevelSeed.MyGame;
		//Tools.CurLevel = CurLevelSeed.MyGame.MyLevel;

		// Set end of game function
		Tools::CurGameData->EndGame = std::make_shared<FinishLambda>( this );

		// Add the saved objects
		for ( std::vector<GameObject*>::const_iterator obj = ObjectsToSave.begin(); obj != ObjectsToSave.end(); ++obj )
			Tools::CurGameData->AddGameObject( *obj );

		// Additional processing
		AdditionalSwapToLevelProcessing( Tools::CurGameData );

		if ( OnSwapToLevel != 0 )
			OnSwapToLevel->Apply( CurLevelIndex );

		// Burn one frame
		Tools::CurGameData->MyLevel->PhsxStep( true );
	}

	void StringWorldGameData::AdditionalSwapToLevelProcessing( const std::shared_ptr<GameData> &game )
	{
	}

	void StringWorldGameData::Load( int Index )
	{
		GameData::LockLevelStart = false;

		NextLevelIndex = Index;
		NextLevelSeed = GetSeed( NextLevelIndex );

		if ( NextLevelSeed == 0 )
			return;

		if ( CurLevelSeed == 0 )
			CurLevelSeed = NextLevelSeed;

		if ( OnBeginLoad != 0 )
			OnBeginLoad->Apply();

		GameData::StartLevel( NextLevelSeed, true );
	}

	void StringWorldGameData::BackgroundPhsx()
	{
		if ( SkipBackgroundPhsx )
			return;

		// ActionGames immediately switch to next game when they are done.
		std::shared_ptr<ActionGameData> ActionGame = dynamic_cast<ActionGameData*>( Tools::CurGameData );
		if ( 0 != ActionGame && ActionGame->Done )
			TellGameToBringNext( 0, ActionGame );

		// The following code handles beginning the loading of new levels.
		if ( ( Tools::ShowLoadingScreen || EndLoadingImmediately ) && Tools::CurGameData != CurLevelSeed->MyGame )
		{
			// If the level is finished loading, end the loading screen
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock ( CurLevelSeed->Loaded )
			{
				if ( CurLevelSeed->Loaded->getval() )
				{
					if ( EndLoadingImmediately )
						Tools::EndLoadingScreen_Immediate();
					else
						Tools::EndLoadingScreen();
					SetLevel();
				}
			}
		}
		else
		{
			// Begin loading next level
			if ( FirstLevelHasLoaded )
			{
				if ( CurLevelSeed == NextLevelSeed )
				{
					Load( CurLevelIndex + 1 );

					// Set current level's next level
					if ( LastLevelSeedSet != Tools::CurLevel )
					{
						LastLevelSeedSet = Tools::CurLevel;

						std::shared_ptr<ILevelConnector> connector = static_cast<ILevelConnector*>( Tools::CurLevel->FindIObject( LevelConnector::EndOfLevelCode ) );
						if ( connector != 0 )
							connector->setNextLevelSeedData( NextLevelSeed );
					}
				}
			}
		}

		// If the level is finished loading, end the loading screen
		if ( !FirstLevelHasLoaded )
		{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock ( CurLevelSeed->Loaded )
			{
				if ( CurLevelSeed->Loaded->getval() )
				{
					LevelBegin( Tools::CurLevel );

					FirstLevelHasLoaded = true;
				}
			}
		}
	}

	StringWorldGameData::StringWorldGameData()
	{
		InitializeInstanceFields();
	}

	StringWorldGameData::StringWorldGameData( Func<int, LevelSeedData*> GetSeed )
	{
		InitializeInstanceFields();
		this->GetSeedFunc = std::make_shared<Func>( this, &StringWorldGameData::GetSeed );
	}

	std::shared_ptr<Level> StringWorldGameData::MakeLevel()
	{
		std::shared_ptr<Level> level = std::make_shared<Level>( false );
		level->setMainCamera( std::make_shared<Camera>() );

		return level;
	}

	void StringWorldGameData::Init()
	{
		Init( 0 );
	}

	void StringWorldGameData::Init( int StartIndex )
	{
		this->StartIndex = StartIndex;

		DrawObjectText = true;

		MyLevel = MakeLevel();
		MyLevel->MyGame = this;

		AllowQuickJoin = false;

		SuppressQuickSpawn = true;

		Load( StartIndex );
		SetLevel();

		FadeIn( .011f );
		BlackAlpha = 1.35f;

		GameData::Init();
	}

	void StringWorldGameData::SetToReturnTo( int code )
	{
		GameData::SetToReturnTo( code );
	}

	void StringWorldGameData::ReturnTo( int code )
	{
		GameData::ReturnTo( code );

		EndGame->Apply( false );
	}

	void StringWorldGameData::EOG_StandardDoorAction( const std::shared_ptr<Door> &door )
	{
		Tools::CurrentAftermath = std::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = true;

		for ( std::vector<Bob*>::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			( *bob )->CollectSelf();

		//Tools.CurGameData.AddGameObject(new VictoryPanel());

		// Absorb game stats
		PlayerManager::AbsorbTempStats();
		PlayerManager::AbsorbLevelStats();
		PlayerManager::AbsorbGameStats();
	}

	void StringWorldGameData::EOL_StringWorldDoorAction( const std::shared_ptr<Door> &door )
	{
		// Make sure that there is another level to go to
		if ( NextLevelSeed == 0 )
			return;
		else
		{
			std::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;
			BaseDoorAction( door );

			// Close the door
			game->AddToDo( std::make_shared<CloseDoorAndAbsorbLambda>( door ) );

			if ( door->getOnEnter() != 0 )
				door->getOnEnter()->Apply(door);
		}
	}

	void StringWorldGameData::EOL_StringWorldDoorEndAction( const std::shared_ptr<Door> &door )
	{
		std::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

		// Tell the current Game to perform the following
		TellGameToBringNext( 13, game );
	}

	void StringWorldGameData::EOL_StringWorldDoorEndAction_WithFade( const std::shared_ptr<Door> &door )
	{
		std::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

		Tools::SongWad->FadeOut();
		game->FadeToBlack( .02f, 47 );

		// Tell the current Game to perform the following
		//TellGameToBringNext(98, game);
		TellGameToBringNext( 165, game );
	}

	void StringWorldGameData::TellGameToBringNext( int delay, const std::shared_ptr<GameData> &game )
	{
		if ( WaitingForNext )
			return;

		WaitingForNext = true;

		game->WaitThenAddToToDo( delay, std::make_shared<StartNextLevelLambda>( this ) );
	}

	void StringWorldGameData::BaseDoorAction( const std::shared_ptr<Door> &door )
	{
		std::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

		game->CompleteLevelEvent();

		// Don't do anything if level has ended
		if ( door->getCore()->MyLevel->Finished )
			return;

		// Ensure door isn't reused
		door->getOnOpen().reset();

		// End this level
		door->getCore()->MyLevel->EndLevel();

		// Give bonus to completing player
		door->getCore()->MyLevel->EndOfLevelBonus(door->InteractingBob->getMyPlayerData());
	}

	void StringWorldGameData::PhsxStep()
	{
		SuppressQuickSpawn = true;
	}

	void StringWorldGameData::PostDraw()
	{
		//base.PostDraw();
	}

	void StringWorldGameData::InitializeInstanceFields()
	{
		NextLevelIndex = 0;
		CurLevelIndex = 0;
		FirstLevelHasLoaded = false;
		FirstLevelHasBegun = false;
		WaitLengthToOpenDoor_FirstLevel = 6;
		StartLevelMusic = std::make_shared<DefaultStartLevelMusicProxy>();
		FirstDoorAction = true;
		OnSwapToFirstLevel = std::make_shared<Multicaster_1<LevelSeedData*> >();
		OnSwapToLastLevel = std::make_shared<Multicaster_1<LevelSeedData*> >();
		OnSwapToLevel = std::make_shared<Multicaster_1<int> >();
		FirstLevelSwappedIn = false;
		EndLoadingImmediately = false;
		LastLevelSeedSet = 0;
		StartIndex = 0;
		WaitingForNext = false;
	}
}
