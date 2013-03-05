#include <global_header.h>

namespace CloudberryKingdom
{

	EOL_StringWorldDoorActionProxy::EOL_StringWorldDoorActionProxy( const boost::shared_ptr<StringWorldGameData> &gameData )
	{
		this->gameData = gameData;
	}

	void EOL_StringWorldDoorActionProxy::Apply( const boost::shared_ptr<Door> &door )
	{
		gameData->EOL_StringWorldDoorAction( door );
	}

	EOL_StringWorldDoorEndActionProxy::EOL_StringWorldDoorEndActionProxy( const boost::shared_ptr<StringWorldGameData> &gameData )
	{
		this->gameData = gameData;
	}

	void EOL_StringWorldDoorEndActionProxy::Apply( const boost::shared_ptr<Door> &door )
	{
		gameData->EOL_StringWorldDoorEndAction( door );
	}

	void EOG_StandardDoorActionProxy::Apply( const boost::shared_ptr<Door> &door )
	{
		StringWorldGameData::EOG_StandardDoorAction( door );
	}

	StringWorldGameData::StartOfLevelLambda::StartOfLevelLambda( const boost::shared_ptr<StringWorldGameData> &g, const boost::shared_ptr<Level> &level, bool Hold_FirstLevelHasBegun )
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

	void StringWorldGameData::DefaultStartLevelMusicProxy::Apply( const boost::shared_ptr<StringWorldGameData> &stringworld )
	{
		StringWorldGameData::DefaultStartLevelMusic( stringworld );
	}

	StringWorldGameData::OpenAndShowLambda::OpenAndShowLambda( const boost::shared_ptr<StringWorldGameData> &g, const boost::shared_ptr<Level> &level, const boost::shared_ptr<Door> &door, const boost::shared_ptr<LevelSeedData> &CurLevelSeed )
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

	StringWorldGameData::FinishLambda::FinishLambda( const boost::shared_ptr<StringWorldGameData> &g )
	{
		this->g = g;
	}

	void StringWorldGameData::FinishLambda::Apply( const bool &val )
	{
		g->Finish( val );
	}

	StringWorldGameData::CloseDoorAndAbsorbLambda::CloseDoorAndAbsorbLambda( const boost::shared_ptr<Door> &door )
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

	StringWorldGameData::StartNextLevelLambda::StartNextLevelLambda( const boost::shared_ptr<StringWorldGameData> &g )
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

	boost::shared_ptr<GameData> StringWorldGameData::Factory( const boost::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return 0;
	}

	void StringWorldGameData::Release()
	{
		if ( Released )
			return;

		// Release the current level
		if ( CurLevelSeed != 0 )
		{
			if ( CurLevelSeed->MyGame != 0 )
			{
				CurLevelSeed->MyGame->Release();
				CurLevelSeed->Release();
			}
		}

		// Release the next level
		if ( NextLevelSeed != 0 )
		{
            if ( LevelIsLoaded( NextLevelSeed ) )
            {
				if ( NextLevelSeed->MyGame != 0 )
				{
					NextLevelSeed->MyGame->Release();
				}
                NextLevelSeed->Release();
            }
            else
                NextLevelSeed->ReleaseWhenLoaded = true;
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

		if ( Tools::WorldMap == shared_from_this() )
			Tools::WorldMap.reset();

		GameData::Release();
	}

	boost::shared_ptr<LevelSeedData> StringWorldGameData::GetSeed( int Index )
	{
		if ( GetSeedFunc == 0 )
			return 0;
		else
			return GetSeedFunc->Apply( Index );
	}

	bool StringWorldGameData::NextIsReady()
	{
		if ( NextLevelSeed == 0 )
			return false;

		bool val = false;
		NextLevelSeed->Loaded->MyMutex.Lock();
		{
			 val = NextLevelSeed->Loaded->getval();
		}
		NextLevelSeed->Loaded->MyMutex.Unlock();

		return val;
	}

	void StringWorldGameData::LevelBegin( const boost::shared_ptr<Level> &level )
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
			level->MyGame->AddToDo( boost::make_shared<StartOfLevelLambda>( boost::static_pointer_cast<StringWorldGameData>( shared_from_this() ), level, Hold_FirstLevelHasBegun ) );

			level->MyGame->PhsxStepsToDo += 2;
		}

		FirstLevelHasBegun = true;
	}

	void StringWorldGameData::DefaultStartLevelMusic( const boost::shared_ptr<StringWorldGameData> &stringworld )
	{
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		Tools::SongWad->Shuffle();

		if ( !stringworld->FirstLevelHasLoaded )
			Tools::SongWad->Next();
	}

	void StringWorldGameData::BeginningCloseDoor( const boost::shared_ptr<Level> &level )
	{
		// Find the initial door
		boost::shared_ptr<Door> door = boost::static_pointer_cast<Door>( level->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 == door )
			return;

		// Close the door
		door->SetLock( true, true, false );
		door->HideBobs();

		level->Finished = true;
	}

	void StringWorldGameData::StartOfLevelDoorAction( const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<GameData> game = level->MyGame;

		if ( game == 0 )
			return;

		// Find the initial door
		boost::shared_ptr<Door> door = boost::static_pointer_cast<Door>( level->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 == door )
		{

			return;
		}

		// Open the door and show players
		int Wait = WaitLengthToOpenDoor_FirstLevel;

		if ( CurLevelIndex > 0 || CurLevelSeed->AlwaysOverrideWaitDoorLength )
			Wait = CurLevelSeed->WaitLengthToOpenDoor;
		game->WaitThenDo( Wait, boost::make_shared<OpenAndShowLambda>( boost::static_pointer_cast<StringWorldGameData>( shared_from_this() ), level, door, CurLevelSeed ) );
	}

	void StringWorldGameData::_StartOfLevelDoorAction__OpenAndShow( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Door> &door, bool OpenDoorSound )
	{
		// Whether to play a sound for the door opening
		bool sound = false;
		if ( CurLevelIndex == StartIndex || OpenDoorSound )
			sound = true;

		level->Finished = false;
		door->SetLock( false, false, sound );
		door->ShowBobs();
	}

	bool StringWorldGameData::LevelIsLoaded( const boost::shared_ptr<LevelSeedData> &data )
	{
		bool val = false;
		data->Loaded->MyMutex.Lock();
		{
			val = data->Loaded->getval();
		}
		data->Loaded->MyMutex.Unlock();

		return val;
	}

	void StringWorldGameData::AdditionalSetLevel()
	{
	}

	void StringWorldGameData::SetLevel()
	{
		if ( NextLevelSeed->MyGame != 0 )
		{
			// Check for last level
			if ( NextIsLast() )
			{
				boost::shared_ptr<ObjectBase> obj = NextLevelSeed->MyGame->MyLevel->FindIObject( LevelConnector::EndOfLevelCode );

				boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( obj );
				if ( 0 != door )
					door->setOnOpen( boost::make_shared<EOG_StandardDoorActionProxy>() );
			}

			// Replace all Bobs with new Bobs (to handle newly joined players)
			AdditionalSetLevel();
			NextLevelSeed->MyGame->UpdateBobs();
			NextLevelSeed->MyGame->Reset();
		}

		NextLevelSeed->Loaded->MyMutex.Lock();
		{
			// If game hasn't loaded yet, bring loading screen
			if ( !NextLevelSeed->Loaded->getval() )
			{
				if ( !NextLevelSeed->LoadingBegun )
					Tools::Break();

				if ( !Tools::ShowLoadingScreen )
				{
					Tools::CurLevel = MyLevel;
					Tools::CurGameData = shared_from_this();
					Tools::BeginLoadingScreen( true );
				}
			}
			else
			{
				SwapToLevel();
				Tools::WorldMap = shared_from_this();
			}
		}
		NextLevelSeed->Loaded->MyMutex.Unlock();
	}

	void StringWorldGameData::Finish( bool Replay )
	{
		GameData::Finish( Replay );
	}

	bool StringWorldGameData::NextIsLast()
	{
		return NextLevelSeed->Name == std::wstring( L"Last" );
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
		GameObjVec ObjectsToSave = GameObjVec();

		if ( CurLevelSeed != 0 && NextLevelSeed != CurLevelSeed )
		{
			// FIXME: forget about throwing exceptions?
			//if ( CurLevelSeed->MyGame->Loading )
			//	throw InvalidOperationException( std::wstring( L"Swapping from a level that hasn't finished loading!" ) );

			for ( GameObjVec::const_iterator obj = CurLevelSeed->MyGame->MyGameObjects.begin(); obj != CurLevelSeed->MyGame->MyGameObjects.end(); ++obj )
				if ( ( *obj )->PreventRelease )
					ObjectsToSave.push_back( *obj );

			CurLevelSeed->MyGame->Release();
			CurLevelSeed->Loaded->setval( false );
			CurLevelSeed->Release();
		}

		CurLevelSeed = NextLevelSeed;
		CurLevelIndex = NextLevelIndex;

		//Tools::CurGameData = CurLevelSeed.MyGame;
		//Tools::CurLevel = CurLevelSeed.MyGame.MyLevel;

		// Set end of game function
		Tools::CurGameData->EndGame = boost::make_shared<FinishLambda>( boost::static_pointer_cast<StringWorldGameData>( shared_from_this() ) );

		// Add the saved objects
		for ( GameObjVec::const_iterator obj = ObjectsToSave.begin(); obj != ObjectsToSave.end(); ++obj )
			Tools::CurGameData->AddGameObject( *obj );

		// Additional processing
		AdditionalSwapToLevelProcessing( Tools::CurGameData );

		if ( OnSwapToLevel != 0 )
			OnSwapToLevel->Apply( CurLevelIndex );

		// Burn one frame
		Tools::CurGameData->MyLevel->PhsxStep( true );
	}

	void StringWorldGameData::AdditionalSwapToLevelProcessing( const boost::shared_ptr<GameData> &game )
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
		boost::shared_ptr<ActionGameData> ActionGame = boost::dynamic_pointer_cast<ActionGameData>( Tools::CurGameData );
		if ( 0 != ActionGame && ActionGame->Done )
			TellGameToBringNext( 0, ActionGame );

		// The following code handles beginning the loading of new levels.
		if ( ( Tools::ShowLoadingScreen || EndLoadingImmediately ) && Tools::CurGameData != CurLevelSeed->MyGame )
		{
			// If the level is finished loading, end the loading screen
			CurLevelSeed->Loaded->MyMutex.Lock();
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
			CurLevelSeed->Loaded->MyMutex.Unlock();
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

						boost::shared_ptr<ILevelConnector> connector = boost::static_pointer_cast<ILevelConnector>( Tools::CurLevel->FindIObject( LevelConnector::EndOfLevelCode ) );
						if ( connector != 0 )
							connector->setNextLevelSeedData( NextLevelSeed );
					}
				}
			}
		}

		// If the level is finished loading, end the loading screen
		if ( !FirstLevelHasLoaded )
		{
			CurLevelSeed->Loaded->MyMutex.Lock();
			{
				if ( CurLevelSeed->Loaded->getval() )
				{
					LevelBegin( Tools::CurLevel );

					FirstLevelHasLoaded = true;
				}
			}
			CurLevelSeed->Loaded->MyMutex.Unlock();
		}
	}

	StringWorldGameData::StringWorldGameData() :
		Count( 0 )
	{
		// See StringWorldGameData_Construct.

		InitializeInstanceFields();
	}

	StringWorldGameData::StringWorldGameData( const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed ) :
		Count( 0 )
	{
		// See StringWorldGameData_Construct.

		InitializeInstanceFields();
		/*this->GetSeedFunc = GetSeed;*/
	}

	boost::shared_ptr<Level> StringWorldGameData::MakeLevel()
	{
		boost::shared_ptr<Level> level = boost::make_shared<Level>( false );
		level->setMainCamera( boost::make_shared<Camera>() );

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
		MyLevel->MyGame = shared_from_this();

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

	void StringWorldGameData::EOG_StandardDoorAction( const boost::shared_ptr<Door> &door )
	{
		Tools::CurrentAftermath = boost::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = true;

		for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			( *bob )->CollectSelf();

		//Tools::CurGameData.AddGameObject(new VictoryPanel());

		// Absorb game stats
		PlayerManager::AbsorbTempStats();
		PlayerManager::AbsorbLevelStats();
		PlayerManager::AbsorbGameStats();
	}

	void StringWorldGameData::EOL_StringWorldDoorAction( const boost::shared_ptr<Door> &door )
	{
		// Make sure that there is another level to go to
		if ( NextLevelSeed == 0 )
			return;
		else
		{
			boost::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;
			BaseDoorAction( door );

			// Close the door
			game->AddToDo( boost::make_shared<CloseDoorAndAbsorbLambda>( door ) );

			if ( door->getOnEnter() != 0 )
				door->getOnEnter()->Apply(door);
		}
	}

	void StringWorldGameData::EOL_StringWorldDoorEndAction( const boost::shared_ptr<Door> &door )
	{
		boost::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

		// Tell the current Game to perform the following
		TellGameToBringNext( 13, game );
	}

	void StringWorldGameData::EOL_StringWorldDoorEndAction_WithFade( const boost::shared_ptr<Door> &door )
	{
		boost::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

		Tools::SongWad->FadeOut();
		float fadespeed = door->getMyLevel()->MyLevelSeed == 0 ? .02f : door->getMyLevel()->MyLevelSeed->FadeOutSpeed;
		game->FadeToBlack( fadespeed, 47 );

		// Tell the current Game to perform the following
		//TellGameToBringNext(98, game);
		//TellGameToBringNext( 165, game );
		TellGameToBringNext( 115 + static_cast<int>( 1.f / fadespeed ), game);
	}

	void StringWorldGameData::TellGameToBringNext( int delay, const boost::shared_ptr<GameData> &game )
	{
		if ( WaitingForNext )
			return;

		WaitingForNext = true;

		game->WaitThenAddToToDo( delay, boost::make_shared<StartNextLevelLambda>( boost::static_pointer_cast<StringWorldGameData>( shared_from_this() ) ) );
	}

	void StringWorldGameData::BaseDoorAction( const boost::shared_ptr<Door> &door )
	{
		boost::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

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
		FirstLevelSwappedIn = false;

		Count = 0;

		NextLevelIndex = 0;
		CurLevelIndex = 0;
		FirstLevelHasLoaded = false;
		FirstLevelHasBegun = false;
		WaitLengthToOpenDoor_FirstLevel = 6;
		StartLevelMusic = boost::make_shared<DefaultStartLevelMusicProxy>();
		FirstDoorAction = true;
		OnSwapToFirstLevel = boost::make_shared<Multicaster_1<boost::shared_ptr<LevelSeedData> > >();
		OnSwapToLastLevel = boost::make_shared<Multicaster_1<boost::shared_ptr<LevelSeedData> > >();
		OnSwapToLevel = boost::make_shared<Multicaster_1<int> >();
		FirstLevelSwappedIn = false;
		EndLoadingImmediately = false;
		LastLevelSeedSet = 0;
		StartIndex = 0;
		WaitingForNext = false;
	}
}
