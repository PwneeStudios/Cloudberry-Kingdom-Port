#include <global_header.h>

#include "Hacks/List.h"
#include "Hacks/Queue.h"
#include "Hacks/String.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void GameData::InitializeStatics()
	{
		GameData::CurItemStep = 0;
		GameData::LockLevelStart = false;
	}

	// Statics
	int GameData::CurItemStep;
	bool GameData::LockLevelStart;
	std::vector<int> GameData::DramaticEntryWait;
	Vector2 GameData::DramaticEntryVel;


	std::shared_ptr<GameData> GameFactory::Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return 0;
	}

	std::shared_ptr<GameData> SimpleGameFactory::Make()
	{
		return 0;
	}

	void GameFlags::SetToDefault()
	{
		IsTethered = IsDoppleganger = IsDopplegangerInvert = false;
	}

	GameData::AddScoreLambda::AddScoreLambda( const std::shared_ptr<GameData> &game, const std::shared_ptr<Door> &door )
	{
		this->game = game;
		this->door = door;
	}

	void GameData::AddScoreLambda::Apply()
	{
		if ( game->MakeScore == 0 )
			return;

		std::shared_ptr<GameObject> ScoreObj = game->MakeScore->Apply();
		if ( ScoreObj == 0 )
			return;
		door->getCore()->MyLevel->MyGame->AddGameObject(ScoreObj);

		// Absorb game stats
		PlayerManager::AbsorbLevelStats();
		PlayerManager::AbsorbGameStats();
	}

	GameData::FinishProxy::FinishProxy( const std::shared_ptr<GameData> &gt )
	{
		this->gt = gt;
	}

	void GameData::FinishProxy::Apply( const bool &Replay )
	{
		gt->Finish( Replay );
	}

	GameData::PlayWorldMapMusicLambda::PlayWorldMapMusicLambda()
	{
	}

	void GameData::PlayWorldMapMusicLambda::Apply()
	{
		Tools::PlayHappyMusic();
	}

	GameData::PlayAgainLambda::PlayAgainLambda( const std::shared_ptr<GameData> &parentgame )
	{
		this->parentgame = parentgame;
	}

	void GameData::PlayAgainLambda::Apply()
	{
		parentgame->PlayAgain();
	}

	GameData::ReleaseThisLambda::ReleaseThisLambda( const std::shared_ptr<GameData> &game )
	{
		this->game = game;
	}

	void GameData::ReleaseThisLambda::Apply()
	{
	}

	GameData::WaitThenDoCoversion::WaitThenDoCoversion( int WaitLength, const std::shared_ptr<Lambda> &f )
	{
		WaitLength_ = WaitLength;
		f_ = f;
		Count_ = 0;
	}

	bool GameData::WaitThenDoCoversion::Apply()
	{
		if ( Count_ >= WaitLength_ )
		{
			f_->Apply();
			return true;
		}
		else
		{
			Count_++;
			return false;
		}
	}

	GameData::WaitThenAddToToDoLambda::WaitThenAddToToDoLambda( const std::shared_ptr<GameData> &game, const std::shared_ptr<LambdaFunc<bool> > &f )
	{
		this->game = game;
		this->f = f;
	}

	void GameData::WaitThenAddToToDoLambda::Apply()
	{
		game->AddToDo( f );
	}

	GameData::FadeInAndDoAction::FadeInAndDoAction( const std::shared_ptr<GameData> &game, const std::shared_ptr<Lambda> &OnBlack, float speed, float TargetOpaqueness )
	{
		this->game = game;
		this->OnBlack = OnBlack;
		this->speed = speed;
		this->TargetOpaqueness = TargetOpaqueness;
	}

	void GameData::FadeInAndDoAction::Apply()
	{
		// Fade in and do action.
		game->FadeIn( speed );
		game->BlackAlpha = TargetOpaqueness;
		if ( OnBlack != 0 )
			OnBlack->Apply();
	}

	GameData::SlideInLambda::SlideInLambda( const std::shared_ptr<StartMenu_MW_Black> &black )
	{
		this->black = black;
	}

	void GameData::SlideInLambda::Apply()
	{
		black->SlideFromRight();
	}

	GameData::FadeInAfterBlack::FadeInAfterBlack( const std::shared_ptr<StartMenu_MW_Black> &black, const std::shared_ptr<Lambda> &OnBlack, const std::shared_ptr<GameData> &game )
	{
		this->black = black;
		this->OnBlack = OnBlack;
		this->game = game;
	}

	void GameData::FadeInAfterBlack::Apply()
	{
		// Get rid of black screen swipe.
		black->MyPile->setAlpha( 0 );
		black->CollectSelf();

		// Fade in and do action.
		game->FadeIn( .025f );
		if ( OnBlack != 0 )
			OnBlack->Apply();
	}

	GameData::ConvertLambdaToLambdaFuncTrue::ConvertLambdaToLambdaFuncTrue( const std::shared_ptr<Lambda> &f )
	{
		f_ = f;
	}

	bool GameData::ConvertLambdaToLambdaFuncTrue::Apply()
	{
		f_->Apply();
		return true;
	}

	GameData::FindTargetBobLambda::FindTargetBobLambda( const std::shared_ptr<Bob> &Player )
	{
		this->Player = Player;
	}

	bool GameData::FindTargetBobLambda::Apply( const std::shared_ptr<Bob> &bob )
	{
		return bob != Player && !bob->Dying;
	}

	GameData::RemoveMarkedLambda::RemoveMarkedLambda()
	{
	}

	bool GameData::RemoveMarkedLambda::Apply( const std::shared_ptr<GameObject> &obj )
	{
		return obj->getCore()->MarkedForDeletion;
	}

	GameData::FadeToBlackLambda::FadeToBlackLambda( const std::shared_ptr<GameData> &game, float FadeOutSpeed )
	{
		game_ = game;
		FadeOutSpeed_ = FadeOutSpeed;
	}

	void GameData::FadeToBlackLambda::Apply()
	{
		game_->FadeToBlack( FadeOutSpeed_ );
	}

	GameData::GetCampaignStatsScoreLambda::GetCampaignStatsScoreLambda()
	{
	}

	float GameData::GetCampaignStatsScoreLambda::Apply( const std::shared_ptr<PlayerData> &p )
	{
		return static_cast<float>( p->CampaignStats->Score );
	}

	GameData::OpenDoorAndShowBobsLambda::OpenDoorAndShowBobsLambda( const std::shared_ptr<Level> &MyLevel, const std::shared_ptr<Door> &door, const std::shared_ptr<GameData> &game )
	{
		MyLevel_ = MyLevel;
		Door_ = door;
		Game_ = game;
	}

	void GameData::OpenDoorAndShowBobsLambda::Apply()
	{
		for ( BobVec::const_iterator bob = MyLevel_->Bobs.begin(); bob != MyLevel_->Bobs.end(); ++bob )
			( *bob )->getCore()->Show = false;

		Door_->SetLock( false, false, true );
		Door_->MoveBobs();
		Door_->ShowBobs();

		Game_->MoveAndUpdateBobs();
		Door_->MoveBobs();
	}

	GameData::DramaticEntryLambda::DramaticEntryLambda( const std::shared_ptr<GameData> &game, int Wait, const std::shared_ptr<Door> &door )
	{
		Game_ = game;
		Wait_ = Wait;
		Door_ = door;
	}

	void GameData::DramaticEntryLambda::Apply()
	{
		Game_->EnterFrom( Door_, DramaticEntryWait[ 0 ] + Wait_ );
		Game_->CinematicToDo( DramaticEntryWait[ 1 ] + Wait_, std::make_shared<Door::ShakeLambda>( Door_, 19, 11, true ) );
		Game_->CinematicToDo( DramaticEntryWait[ 2 ] + Wait_, std::make_shared<Door::ShakeLambda>( Door_, 19, 11, true ) );
		Game_->CinematicToDo( DramaticEntryWait[ 3 ] + Wait_, std::make_shared<DramaticEntryEnterLambda>( Door_ ) );
	}

	GameData::DramaticEntryEnterLambda::DramaticEntryEnterLambda( const std::shared_ptr<Door> &door )
	{
		Door_ = door;
	}

	void GameData::DramaticEntryEnterLambda::Apply()
	{
		Door_->Shake( 19, 11, true );
		for ( BobVec::const_iterator bob = Door_->getCore()->MyLevel->Bobs.begin(); bob != Door_->getCore()->MyLevel->Bobs.end(); ++bob )
		{
			( *bob )->PlayerObject->EnqueueAnimation( 2, 0, false, true, false, 10 );
			( *bob )->getCore()->Data.Velocity += DramaticEntryVel;
		}
	}

	/*void GameData::KillThread( const std::shared_ptr<Object> &sender, const std::shared_ptr<System::EventArgs> &e )
	{
		std::shared_ptr<Thread> MakeThread = Thread::CurrentThread;
		if ( MakeThread != 0 )
		{
			MakeThread->Abort();
		}
	}*/

	void GameData::EOL_DoorAction( const std::shared_ptr<Door> &door )
	{
		StatGroup group = door->getGame()->MyStatGroup;
		std::shared_ptr<GameData> game = door->getCore()->MyLevel->MyGame;

		game->HasBeenCompleted = true;

		// Give bonus to completing player
		door->getCore()->MyLevel->EndOfLevelBonus(door->InteractingBob->getMyPlayerData());

		// Close the door
		door->SetLock( true, false, true );

		// Aftermath
		Tools::CurrentAftermath = std::make_shared<AftermathData>();
		Tools::CurrentAftermath->Success = true;

		// Ensure door isn't reused
		door->getOnOpen().reset();

		// End this level
		door->getCore()->MyLevel->EndLevel();

		// Calculate level stats
		PlayerManager::AbsorbTempStats();
		if ( group == StatGroup_GAME )
			PlayerManager::AbsorbLevelStats();

		// Hide the player
		door->InteractingBob->getCore()->Show = false;

		// Add the score
		std::shared_ptr<ExplodeBobs> explode = MakeMagic( ExplodeBobs, ( ExplodeBobs::Speed_REGULAR ) );
		door->getCore()->MyLevel->MyGame->AddGameObject(std::static_pointer_cast<GameObject> ( explode ) );
		explode->OnDone = std::make_shared<AddScoreLambda>( game, door );
	}

	void GameData::Finish( bool Replay )
	{
		StandardFinish( Replay );

		// Start the world map music
		ParentGame->KillToDo( _T( "StartMusic" ) );
		ParentGame->WaitThenDo( 50, std::make_shared<PlayWorldMapMusicLambda>(), _T("StartMusic") );
	}

	void GameData::StandardFinish( bool Replay )
	{
		// Stats
		PlayerManager::CleanTempStats();
		PlayerManager::AbsorbLevelStats();
		PlayerManager::AbsorbGameStats();

		// Switch to this game (may have been in a sub-game)
		Tools::CurLevel = MyLevel;
		Tools::CurGameData = shared_from_this();

		// Fade the music
		if ( EndMusicOnFinish )
			Tools::SongWad->FadeOut();

		// Return to the parent game
		ParentGame->SetToReturnTo( 0 );

		// Release this game
		ParentGame->AddToDo( std::make_shared<ReleaseThisLambda>( shared_from_this() ) );

		// Check if we should replay the current game
		if ( Replay )
		{
			std::shared_ptr<GameData> parentgame = ParentGame;
			ParentGame->AddToDo( std::make_shared<PlayAgainLambda>( parentgame ) );
		}

		// Save everything
		ParentGame->PhsxStepsToDo = 3;
		SaveGroup::SaveAll();
	}

	void GameData::ClearPreviousLoadFunction()
	{
		PreviousLoadFunction.reset();
	}

	void GameData::PlayGame( const std::shared_ptr<Lambda> &LoadFunction )
	{
		PreviousLoadFunction = LoadFunction;

		if ( LoadFunction != 0 )
			LoadFunction->Apply();
	}

	void GameData::PlayAgain()
	{
		ExecutingPreviousLoadFunction = true;
		if ( PreviousLoadFunction != 0 )
			PreviousLoadFunction->Apply();
		ExecutingPreviousLoadFunction = false;
	}

	void GameData::WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> f )
	{
		WaitThenDo( WaitLength, f, _T( "" ) );
	}

	void GameData::WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> f, const std::wstring &Name )
	{
		WaitThenDo( WaitLength, f, Name, false, false );
	}

	void GameData::WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> f, bool PauseOnPause )
	{
		WaitThenDo( WaitLength, f, _T( "" ), PauseOnPause, false );
	}

	void GameData::WaitThenDo_Pausable( int WaitLength, const std::shared_ptr<Lambda> f )
	{
		WaitThenDo( WaitLength, f, _T( "" ), true, false );
	}

	void GameData::CinematicToDo( int WaitLength, const std::shared_ptr<Lambda> f )
	{
		WaitThenDo( WaitLength, f, _T( "" ), true, true );
	}

	void GameData::WaitThenDo( int WaitLength, const std::shared_ptr<Lambda> f, const std::wstring &Name, bool PauseOnPause, bool RemoveOnReset )
	{
		if ( WaitLength < 0 )
			return;

		AddToDo( std::make_shared<WaitThenDoCoversion>( WaitLength, f ), Name, PauseOnPause, RemoveOnReset );
	}

	void GameData::WaitThenAddToToDo( int WaitLength, const std::shared_ptr<LambdaFunc<bool> > f )
	{
		// Create a function that after the specified time will add f to the ToDo list
		WaitThenDo( WaitLength, std::make_shared<WaitThenAddToToDoLambda>( shared_from_this(), f ) );
	}

	bool GameData::QuickSpawnEnabled()
	{
		return !SuppressQuickSpawn && !SuppressQuickSpawn_External;
	}

	const std::shared_ptr<Camera> GameData::getCam() const
	{
		if ( MyLevel == 0 )
			return 0;
		return MyLevel->getMainCamera();
	}

	const std::shared_ptr<Rand> &GameData::getRnd() const
	{
		return MyLevel->getRnd();
	}

	const Vector2 GameData::getCamPos() const
	{
		if ( MyLevel == 0 )
			return Vector2();
		else
			return MyLevel->getMainCamera()->Data.Position;
	}

	bool GameData::IsFading()
	{
		return FadingToBlack || FadingIn;
	}

	void GameData::PartialFade_InAndOut( int Delay, float TargetOpaqueness, int FadeOutLength, int FadeInLength, const std::shared_ptr<Lambda> &OnBlack )
	{
		// Wait then screen partially fade to black.
		WaitThenDo( Delay, std::make_shared<FadeToBlackLambda>( shared_from_this(), TargetOpaqueness / FadeOutLength ) );

		// Wait for the apex of blackness, trigger the action and fade back in.
		WaitThenDo( Delay + FadeOutLength, std::make_shared<FadeInAndDoAction>( shared_from_this(), OnBlack, TargetOpaqueness / FadeOutLength, TargetOpaqueness ) );
	}

	void GameData::SlideOut_FadeIn( int Delay, const std::shared_ptr<Lambda> &OnBlack )
	{
		std::shared_ptr<StartMenu_MW_Black> black = MakeMagic( StartMenu_MW_Black, () );
		AddGameObject( black );

		// Wait then screen swipe to black.
		WaitThenDo( Delay, std::make_shared<SlideInLambda>( black ), _T( "SlideOut_FadeIn" ) );

		// Wait for screen to be completely black, then fade in.
		WaitThenDo( Delay + 17, std::make_shared<FadeInAfterBlack>( black, OnBlack, shared_from_this() ), _T( "SlideOut_FadeIn" ) );
	}

	void GameData::RemoveGameObjects( GameObject::Tag tag )
	{
		for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
			if ( ( *obj )->Tags->Has( tag ) )
				( *obj )->Release();
	}

	void GameData::CalculateCoinScoreMultiplier()
	{
		CoinScoreMultiplier = 1;
		if ( OnCalculateCoinScoreMultiplier != 0 )
			OnCalculateCoinScoreMultiplier->Apply( shared_from_this() );
	}

	void GameData::CalculateScoreMultiplier()
	{
		ScoreMultiplier = 1;
		if ( OnCalculateScoreMultiplier != 0 )
			OnCalculateScoreMultiplier->Apply( shared_from_this() );
	}

	void GameData::CheckpointGrabEvent( const std::shared_ptr<ObjectBase> &Checkpoint_Renamed )
	{
		if ( OnCheckpointGrab != 0 )
			OnCheckpointGrab->Apply( Checkpoint_Renamed );
	}

	void GameData::CoinGrabEvent( const std::shared_ptr<ObjectBase> &coin )
	{
		if ( OnCoinGrab != 0 )
			OnCoinGrab->Apply( coin );
	}

	void GameData::CompleteLevelEvent()
	{
		HasBeenCompleted = true;
		if ( OnCompleteLevel != 0 )
			OnCompleteLevel->Apply( MyLevel );
	}

	void GameData::LevelRetryEvent()
	{
		if ( OnLevelRetry != 0 )
			OnLevelRetry->Apply();
	}

	void GameData::ReturnToEvent()
	{
		if ( OnReturnTo != 0 )
			OnReturnTo->Apply();
		if ( OnReturnTo_OneOff != 0 )
			OnReturnTo_OneOff->Apply();
			OnReturnTo_OneOff.reset();
	}

	void GameData::AddToDo( const std::shared_ptr<LambdaFunc<bool> > &FuncToDo )
	{
		getToDo().push_back(std::make_shared<ToDoItem>(FuncToDo, _T(""), false, false));
	}

	void GameData::AddToDo( const std::shared_ptr<Lambda> &FuncToDo )
	{
		AddToDo( FuncToDo, _T( "" ), false, false );
	}

	void GameData::AddToDo( const std::shared_ptr<LambdaFunc<bool> > &FuncToDo, const std::wstring &name, bool PauseOnPause, bool RemoveOnReset )
	{
		getToDo().push_back(std::make_shared<ToDoItem>(FuncToDo, name, PauseOnPause, RemoveOnReset));
	}

	void GameData::AddToDo( const std::shared_ptr<Lambda> &FuncToDo, const std::wstring &name, bool PauseOnPause, bool RemoveOnReset )
	{
		getToDo().push_back(std::make_shared<ToDoItem>(std::make_shared<ConvertLambdaToLambdaFuncTrue>(FuncToDo), name, PauseOnPause, RemoveOnReset));
	}

	std::vector<std::shared_ptr<ToDoItem> > &GameData::getToDo()
	{
		return CurToDo;
	}

	void GameData::DoToDoOnResetList()
	{
		std::vector<std::shared_ptr<Lambda> > list = std::vector<std::shared_ptr<Lambda> >( ToDoOnReset );
		ToDoOnReset.clear();

		for ( std::vector<std::shared_ptr<Lambda> >::const_iterator f = list.begin(); f != list.end(); ++f )
			( *f )->Apply();

		list.clear();
	}

	void GameData::DoToDoList()
	{
		if ( CurToDo.size() > 0 )
		{
			DoingToDoList = true;
			NextToDo.clear();
			//NextToDo.AddRange( CurToDo );
			AddRange( NextToDo, CurToDo );

			CurToDo.clear();
			for ( std::vector<std::shared_ptr<ToDoItem> >::const_iterator item = NextToDo.begin(); item != NextToDo.end(); ++item )
			{
				// Skip deleted items
				if ( ( *item )->getMarkedForDeletion() )
					continue;

				bool Keep = true;
				if ( !( PauseGame && ( *item )->PauseOnPause ) )
				{
					// Execute the function
					CurItemStep = ( *item )->Step;
					Keep = !( *item )->MyFunc->Apply();
					( *item )->Step++;
				}

				if ( Keep )
				{
					// Keep the function if it returned false
					if ( CurToDo.size() > 0 )
						CurToDo.push_back( *item );
					else
						return;
				}
			}
			DoingToDoList = false;
		}
	}

	void GameData::KillToDo( const std::wstring &name )
	{
		for ( std::vector<std::shared_ptr<ToDoItem> >::const_iterator todo = ToDoFindAll( name ).begin(); todo != ToDoFindAll(name).end(); ++todo )
			( *todo )->Delete();
	}

	std::vector<std::shared_ptr<ToDoItem> > GameData::ToDoFindAll( const std::wstring &name )
	{
		std::vector<std::shared_ptr<ToDoItem> > l = std::vector<std::shared_ptr<ToDoItem> >();

		for ( std::vector<std::shared_ptr<ToDoItem> >::const_iterator todo = getToDo().begin(); todo != getToDo().end(); ++todo )
			if ( CompareIgnoreCase( ( *todo )->Name, name ) == 0 )
				l.push_back( *todo );

		return l;
	}

	void GameData::Release()
	{
		if ( Released )
			return;

		Released = true;

		DefaultHeroType.reset();

		ParentGame.reset();
		EndGame.reset();

		if ( MyLevel != 0 )
			MyLevel->Release();
		MyLevel.reset();

		for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
			( *obj )->Release();
		NewGameObjects.clear();
		MyGameObjects.clear();

		if ( FadeColor != 0 )
			FadeColor->Release();

		if ( BlackQuad != 0 )
			BlackQuad->Release();
			BlackQuad.reset();
		if ( CurDoor != 0 )
			CurDoor->Release();

		PreviousLoadFunction.reset();
		OnCalculateCoinScoreMultiplier.reset();
		OnCalculateScoreMultiplier.reset();
		OnCheckpointGrab.reset();
		OnCoinGrab.reset();
		OnLevelRetry.reset();
		OnReturnTo.reset();

		CurToDo.clear();
		NextToDo.clear();
		ToDoOnReset.clear();
		ToDoOnDeath.clear();
		ToDoOnDoneDying.clear();

		Recycler::ReturnRecycler( Recycle );
		Recycle.reset();
	}

	std::shared_ptr<GameData> GameData::Factory( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return 0;
	}

	GameData::GameData()
	{
		// This is now in GameData_Construct.  We welcome our C overlords.

		/*InitializeInstanceFields();

		CreationTime = Tools::TheGame->DrawCount;

		Recycle = Recycler::GetRecycler();

		EndGame = std::make_shared<FinishProxy>( shared_from_this() );

		Loading = false;

		CurToDo = std::vector<std::shared_ptr<ToDoItem> >();
		NextToDo = std::vector<std::shared_ptr<ToDoItem> >();*/
	}

	void GameData::LockGameObjects( bool Lock )
	{
		// If unlocking add new GameObjects
		if ( !Lock )
		{
			//MyGameObjects.AddRange( NewGameObjects );
			AddRange( MyGameObjects, NewGameObjects );
			NewGameObjects.clear();
		}

		GameObjectsAreLocked = Lock;
	}

	void GameData::AddGameObject( const std::shared_ptr<GameObject> &obj )
	{
		if ( GameObjectsAreLocked )
			NewGameObjects.push_back( obj );
		else
			MyGameObjects.push_back( obj );

		if ( MyLevel != 0 )
			MyLevel->AddObject( obj );

		obj->MyGame = shared_from_this();

		obj->OnAdd();
	}

	void GameData::BackgroundPhsx()
	{
	}

	const bool &GameData::getIsSetToReturnTo() const
	{
		return _IsSetToReturnTo;
	}

	void GameData::setIsSetToReturnTo( const bool &value )
	{
		_IsSetToReturnTo = value;
	}

	void GameData::SetToReturnTo( int code )
	{
		if ( getIsSetToReturnTo() )
			return;

		setIsSetToReturnTo( true );
		SetToReturnToCode = code;

		PrevGame = Tools::CurGameData;

		Tools::CurGameData = shared_from_this();
		Tools::CurLevel = MyLevel;
	}

	void GameData::ReturnTo( int code )
	{
		// Clear todo list
		if ( ClearToDoOnReturnTo )
			getToDo().clear();

		// Remove players that have left
		if ( MyLevel != 0 && MyLevel->Bobs.size() > 0 )
		{
			BobVec NewBobList = BobVec();
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			{
				if ( PlayerManager::Get( static_cast<int>( ( *bob )->MyPlayerIndex ) )->Exists )
					NewBobList.push_back( *bob );
			}
			MyLevel->Bobs = NewBobList;
		}

		// Create new players
		for ( int i = 0; i < 4; i++ )
		{
			bool All = true;
			for ( int j = 0; j < 4; j++ )
				if ( static_cast<int>( MyLevel->Bobs[ j ]->MyPlayerIndex ) == i )
					All = false;
			if ( All )
				CreateBob( i, false );
		}

		// Revive all players
		ReviveAll();

		CleanLastLevel();

		// Fire event
		ReturnToEvent();
	}

	void GameData::ReviveAll()
	{
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			PlayerManager::RevivePlayer( ( *bob )->MyPlayerIndex );
	}

	void GameData::CleanLastLevel()
	{
		std::shared_ptr<Level> PrevLevel;

		if ( !getIsSetToReturnTo() )
			PrevLevel = Tools::CurLevel;
		else
			PrevLevel = PrevGame->MyLevel;

		setIsSetToReturnTo( false );

		if ( PrevLevel != 0 )
			PrevLevel->Release();
		else
			Tools::Nothing();

		Tools::setPhsxSpeed( 1 );
		LockLevelStart = false;
	}

	void GameData::Reset()
	{
		if ( MyLevel != 0 )
			MyLevel->ResetAll( false );
	}

	void GameData::RevertCheckpoints()
	{
		for ( ObjectVec::const_iterator obj = MyLevel->Objects.begin(); obj != MyLevel->Objects.end(); ++obj )
		{
			std::shared_ptr<Checkpoint> checkpoint = std::static_pointer_cast<Checkpoint>( *obj );
			if ( 0 != checkpoint )
				checkpoint->Revert();
		}
	}

	void GameData::RevertLevel()
	{
		// Revive the checkpoints
		RevertCheckpoints();

		// Start at the first level piece
		MyLevel->SetCurrentPiece( 0 );
	}

	void GameData::GotCheckpoint( const std::shared_ptr<Bob> &CheckpointBob )
	{
		MyLevel->PieceAttempts = 0;

		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
		{
			if ( !PlayerManager::IsAlive( ( *bob )->MyPlayerIndex ) )
			{
				PlayerManager::RevivePlayer( ( *bob )->MyPlayerIndex );
				( *bob )->Dead = ( *bob )->Dying = false;

				( *bob )->Init( false, ( *bob )->MyPiece->StartData[ ( *bob )->MyPieceIndex ], shared_from_this() );
				( *bob )->Move( CheckpointBob->getCore()->Data.Position - (*bob)->getCore()->Data.Position );

				ParticleEffects::AddPop( MyLevel, ( *bob )->getCore()->Data.Position, 155 );
			}
		}

		PlayerManager::AbsorbTempStats();
	}

	void GameData::AdditionalReset()
	{
		if ( MyLevel != 0 && MyLevel->LevelReleased )
			return;

		// Remove marked todo items
		for ( std::vector<std::shared_ptr<ToDoItem> >::const_iterator todo = getToDo().begin(); todo != getToDo().end(); ++todo )
		{
			if ( ( *todo )->RemoveOnReset )
				( *todo )->setMarkedForDeletion(true);
		}

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<ToDoItem> >::const_iterator todo = NextToDo.begin(); todo != NextToDo.end(); ++todo )
		{
			if ( ( *todo )->RemoveOnReset )
				( *todo )->setMarkedForDeletion(true);
		}

		// Perform additional actions
		DoToDoOnResetList();

		FreeReset = false;

		// Revive all players
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			PlayerManager::RevivePlayer( ( *bob )->MyPlayerIndex );

		// Clear the temporary stats
		PlayerManager::CleanTempStats();
	}

	void GameData::RemovePlayer( int PlayerIndex )
	{
		PlayerManager::Get( PlayerIndex )->Exists = PlayerManager::Get( PlayerIndex )->IsAlive = false;

		if ( MyLevel != 0 && MyLevel->Bobs.size() > 0 )
		{
			BobVec NewBobList = BobVec();

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			{
				if ( !PlayerManager::Get( static_cast<int>( ( *bob )->MyPlayerIndex ) )->Exists )
				{
					ParticleEffects::AddPop( MyLevel, ( *bob )->getCore()->Data.Position );
					Tools::SoundWad->FindByName( _T( "Pop_2" ) )->Play();
				}
				else
					NewBobList.push_back( *bob );
			}
			MyLevel->Bobs = NewBobList;
		}

		if ( PlayerManager::AllDead() && !MyLevel->getPreventReset() )
			MyLevel->ResetAll( false );
	}

	void GameData::SetCreatedBobParameters( const std::shared_ptr<Bob> &bob )
	{
		bob->Immortal = true;
		bob->ScreenWrap = true;
		bob->ScreenWrapToCenter = false;
	}

	void GameData::CreateBob( int i, bool Pop )
	{
		std::shared_ptr<Bob> TemplateBob = 0;
		if ( MyLevel->Bobs.size() > 0 )
			TemplateBob = MyLevel->Bobs[ 0 ];

		PlayerManager::Get( i )->IsAlive = PlayerManager::Get( i )->Exists = true;

		//Bob Player = new Bob(Prototypes.bob[MyLevel.DefaultHeroType], false);
		std::shared_ptr<Bob> Player = std::make_shared<Bob>( MyLevel->DefaultHeroType, false );
		Bob_PostConstruct( Player, MyLevel->DefaultHeroType, false );

		Player->MyPlayerIndex = PlayerManager::Get( i )->MyPlayerIndex;
		MyLevel->AddBob( Player );

		if ( TemplateBob != 0 )
			Player->CanInteract = TemplateBob->CanInteract;

		Player->SetColorScheme( PlayerManager::Get( i )->ColorScheme_Renamed );

		PlayerManager::RevivePlayer( Player->MyPlayerIndex );

		SetCreatedBobParameters( Player );

	#if defined(INCLUDE_EDITOR)
		Player->Immortal = true;
	#endif

		Player->MyPiece = MyLevel->CurPiece;

		int _i = __min( i, static_cast<int>( MyLevel->CurPiece->StartData.size() ) - 1 );
		PhsxData StartData = MyLevel->CurPiece->StartData[ _i ];
		Player->Init( false, MyLevel->CurPiece->StartData[ 0 ], shared_from_this() );
		std::shared_ptr<Bob> TargetBob = Tools::Find<std::shared_ptr<Bob> >( MyLevel->Bobs, std::make_shared<FindTargetBobLambda>( Player ) );

		if ( TargetBob != 0 )
			Player->Move( Vector2( 20, 450 ) + TargetBob->getCore()->Data.Position - Player->getCore()->Data.Position );
		else
			Player->Move( Vector2( 0, 750 ) + MyLevel->getMainCamera()->Data.Position - Player->getCore()->Data.Position );

		if ( Pop )
		{
			ParticleEffects::AddPop( MyLevel, Player->getCore()->Data.Position );
			Tools::SoundWad->FindByName( _T( "Pop_2" ) )->Play();
		}
	}

	void GameData::UpdateBobs()
	{
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			( *bob )->Release();
		MyLevel->Bobs.clear();

		MakeBobs( MyLevel );
		SetAdditionalBobParameters( MyLevel->Bobs );
	}

	void GameData::QuickJoinPhsx()
	{
		if ( MyLevel == 0 )
			return;
		if ( MyLevel->Watching || MyLevel->Replay )
			return;
		if ( PauseGame )
			return;
		if ( PauseLevel )
			return;

		// Check for non-playing controllers pressing A
		for ( int i = 0; i < 4; i++ )
			if ( !PlayerManager::Get( i )->Exists && ButtonCheck::State( ControllerButtons_A, i ).Pressed )
			{
				CharacterSelectManager::Start( 0 );
			}
	}

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void GameData::UpdateSignedInPlayers()
	{
		if ( CharacterSelectManager::IsShowing )
			return;
		if ( MyLevel == 0 )
			return;
		if ( MyLevel->Watching || MyLevel->Replay )
			return;
		if ( PauseGame )
			return;
		if ( PauseLevel )
			return;

		for ( std::vector<std::shared_ptr<PlayerData> >::const_iterator player = PlayerManager::getExistingPlayers().begin(); player != PlayerManager::getExistingPlayers().end(); ++player )
			if ( ( *player )->StoredName.length() > 0 && (*player)->getMyGamer() == 0 )
			{
				PlayerManager::GetNumPlayers();
				if ( PlayerManager::NumPlayers > 1 )
					RemovePlayer( ( *player )->MyIndex );
			}
	}
#endif

	void GameData::UpdateGamePause()
	{
		PauseGame = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
			if ( ( *obj )->getPauseGame() )
				PauseGame = true;

		PauseGame |= CharacterSelectManager::IsShowing;
	}

	void GameData::UpdateLevelPause()
	{
		PauseLevel = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
			if ( ( *obj )->getPauseLevel() )
				PauseLevel = true;
	}

	void GameData::UpdateSoftPause()
	{
		SoftPause = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
			if ( ( *obj )->getSoftPause() )
				SoftPause = true;
	}

	void GameData::PhsxStep()
	{
		if ( Loading || Tools::ShowLoadingScreen )
			return;

		// Update the socre and coin score multiplier
		CalculateScoreMultiplier();
		CalculateCoinScoreMultiplier();

		// GameObject physics
		if ( MyLevel != 0 )
		{
			LockGameObjects( true );

			Tools::StartGUIDraw();
			for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
			{
				if ( ( *obj )->getCore()->Released || (*obj)->getCore()->MarkedForDeletion )
				{
					( *obj )->getCore()->MarkedForDeletion = true;
					continue;
				}

				// Update object if game is not paused,
				// or if object updates regardless.
				if ( ( *obj )->getCore()->Active && !(PauseGame && (*obj)->PauseOnPause) )
				{
					if ( ( *obj )->getCore()->MyLevel == 0 )
						MyLevel->AddObject( *obj );
					( *obj )->PhsxStep();
				}
			}
			Tools::EndGUIDraw();

			LockGameObjects( false );
		}

		// Clean GameObjects
		for ( GameObjVec::const_iterator obj = MyGameObjects.begin(); obj != MyGameObjects.end(); ++obj )
		{
			if ( ( *obj )->getCore()->MarkedForDeletion )
				( *obj )->Release();
		}
		CleanGameObjects();

		// Update pause
		UpdateGamePause();
		UpdateLevelPause();

		if ( PauseGame )
			Tools::setPhsxSpeed( 1 );

		// Fading
		if ( FadeColor != 0 )
		{
			FadeColor->Update();
		}

		if ( FadingToReturn && BlackAlpha > 1 )
		{
			Tools::WorldMap->SetToReturnTo( 0 );
			return;
		}

		if ( getIsSetToReturnTo() )
		{
			ReturnTo( SetToReturnToCode );
			return;
		}

		if ( MyLevel == 0 || MyLevel->LevelReleased )
			return;


		// Quick join
	//#if XBOX
		if ( AllowQuickJoin )
			QuickJoinPhsx();
	//#endif


		DoToDoList();

		if ( PauseGame )
		{
			// Clean the level, some GameObjects may have been deleted
			if ( MyLevel != 0 )
				MyLevel->CleanAllObjectLists();
		}

		if ( PauseGame )
		{
			// Return and skip further actions, unless the character select is showing
			if ( !CharacterSelectManager::IsShowing )
			{
				MyLevel->IndependentDeltaT = 0;
				return;
			}
		}

		PhsxCount++;
		if ( MyLevel != 0 )
		{
			if ( !CharacterSelectManager::IsShowing )
			{
				if ( !PauseLevel )
				{
					// Do the level's phsx, suppressing sound if necessary
					bool HoldSuppress = EzSoundWad::SuppressSounds;
					EzSoundWad::SuppressSounds |= MyLevel->SuppressSounds;
					MyLevel->PhsxStep( false );
					EzSoundWad::SuppressSounds = HoldSuppress;

	#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
					UpdateSignedInPlayers();
	#endif
				}
			}
			else
			{
				for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
				{
					if ( ( *bob )->CharacterSelect2 )
					{
						( *bob )->PhsxStep();
						( *bob )->AnimAndUpdate();
					}
				}
			}
		}
		// Character select
		CharacterSelectManager::PhsxStep();


		if ( FadingToBlack )
			BlackAlpha += FadeOutSpeed;
		if ( FadingIn )
		{
			BlackAlpha -= FadeInSpeed;
			if ( BlackAlpha < 0 || FadingToBlack )
				FadingIn = false;
		}
	}

	void GameData::CleanGameObjects()
	{
		Tools::RemoveAll<std::shared_ptr<GameObject> >( MyGameObjects, std::make_shared<RemoveMarkedLambda>() );
	}

	void GameData::Move( Vector2 shift )
	{
		if ( MyLevel != 0 )
			MyLevel->Move( shift );
	}

	void GameData::Init()
	{
		BlackQuad = std::make_shared<QuadClass>( _T( "White" ) );
		BlackQuad->Quad_Renamed.SetColor( Color::Black );

		BlackBase.e1 = Vector2( 45, 0 );
		BlackBase.e2 = Vector2( 0, 45 );

		BlackAlpha = 0;
		FadingToBlack = false;
	}

	void GameData::Black()
	{
		FadeIn( 0 );
	}

	void GameData::FadeIn( float FadeInSpeed )
	{
		BlackAlpha = 1;
		FadingIn = true;
		FadingToBlack = false;
		this->FadeInSpeed = FadeInSpeed;
	}

	void GameData::FadeToBlack()
	{
		FadeToBlack( .01f );
	}

	void GameData::FadeToBlack( float FadeOutSpeed )
	{
		this->FadeOutSpeed = FadeOutSpeed;
		FadingToBlack = true;
		FadingIn = false;
		BlackAlpha = 0;
	}

	void GameData::FadeToBlack( float FadeOutSpeed, int Delay )
	{
		WaitThenDo( Delay, std::make_shared<FadeToBlackLambda>( shared_from_this(), FadeOutSpeed ) );
	}

	void GameData::Draw()
	{
		if ( Loading )
			return;
		else
			if ( MyLevel != 0 )
			{
				if ( MyLevel->LevelReleased )
					return;

				if ( ForceLevelZoomBeforeDraw > 0 )
					getCam()->setZoom(Vector2(ForceLevelZoomBeforeDraw));

				CalculateForceZoom();

				Tools::TheGame->MyGraphicsDevice->Clear( Color::Black );

				MyLevel->Draw();
			}
	}

	void GameData::CalculateForceZoom()
	{
		if ( !DoForceZoom )
			return;

		if ( ForceLevelZoomBeforeDraw < ForceTargetZoom )
			ForceLevelZoomBeforeDraw += .00001f * static_cast<float>( pow( ( ForceTargetZoom - ForceLevelZoomBeforeDraw ) / ( .00085f - .0007f ),.5f ) );

		if ( ForceLevelZoomBeforeDraw > ForceTargetZoom )
			ForceLevelZoomBeforeDraw -= .00001f * static_cast<float>( pow( ( ForceLevelZoomBeforeDraw - ForceTargetZoom ) / ( .00085f - .0007f ),.5f ) );
	}

	void GameData::PostDraw()
	{
		Tools::StartGUIDraw();

		if ( FadingToBlack || FadingIn || FadeColor != 0 )
		{
			BlackQuad->FullScreen( getCam() );

			if ( FadeColor == 0 )
				BlackQuad->Quad_Renamed.SetColor( Color( 0, 0, 0, Tools::FloatToByte( BlackAlpha ) ) );
			else
				BlackQuad->Quad_Renamed.SetColor( FadeColor->getColor() );
			BlackQuad->Draw();
			Tools::QDrawer->Flush();
		}

		for ( int i = Level::AfterPostDrawLayer; i < Level::NumDrawLayers; i++ )
			MyLevel->DrawGivenLayer( i );

		//MyLevel.MainCamera.RevertZoom();
		Tools::EndGUIDraw();
	}

	void GameData::BobDie( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob )
	{
		if ( bob->DieSound == 0 )
			Bob::DieSound_Default->Play( .3f );
		else
			bob->DieSound->Play( .3f );

		PlayerManager::KillPlayer( bob->MyPlayerIndex );

		if ( PlayerManager::AllDead() )
			DoToDoOnDeathList();
	}

	void GameData::DoToDoOnDeathList()
	{
		std::vector<std::shared_ptr<Lambda> > list = std::vector<std::shared_ptr<Lambda> >( ToDoOnDeath );
		ToDoOnDeath.clear();

		for ( std::vector<std::shared_ptr<Lambda> >::const_iterator f = list.begin(); f != list.end(); ++f )
			( *f )->Apply();

		list.clear();
	}

	void GameData::BobDoneDying( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob )
	{
		if ( PlayerManager::AllDead() && level->ResetEnabled() )
		{
			level->setSetToReset( true );

			DoToDoOnDoneDyingList();
		}
	}

	void GameData::DoToDoOnDoneDyingList()
	{
		std::vector<std::shared_ptr<Lambda> > list = std::vector<std::shared_ptr<Lambda> >( ToDoOnDoneDying );
		ToDoOnDoneDying.clear();

		for ( std::vector<std::shared_ptr<Lambda> >::const_iterator f = list.begin(); f != list.end(); ++f )
			( *f )->Apply();

		list.clear();
	}

#if defined(XBOX) || defined(XBOX_SIGNIN)
	void GameData::OnSignOut( const std::shared_ptr<SignedOutEventArgs> &e )
	{
	}
#endif

	bool GameData::OnePast( float x )
	{
		bool OnePast = false;
		if ( MyLevel->Bobs.size() > 0 )
		{
			for ( std::vector<std::shared_ptr<Bob> >::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
				if ( ( *bob )->getCore()->Data.Position.X > x )
					OnePast = true;

			return OnePast;
		}
		else
			return false;
	}

	bool GameData::AllPast( float x )
	{
		bool AllPast = true;
		if ( MyLevel->Bobs.size() > 0 )
		{
			for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
				if ( ( *bob )->getCore()->Data.Position.X < x )
					AllPast = false;

			return AllPast;
		}
		else
			return false;
	}

	std::shared_ptr<PlayerData> GameData::getMvp() const
	{
		return Tools::ArgMax<std::shared_ptr<PlayerData> >( PlayerManager::getExistingPlayers(), std::make_shared<GetCampaignStatsScoreLambda>() );
	}

	std::shared_ptr<Bob> GameData::getMvpBob() const
	{
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			if ( ( *bob )->MyPlayerIndex == getMvp()->MyPlayerIndex )
				return ( *bob );
		return MyLevel->Bobs[ 0 ];
	}

	void GameData::MakeBobs( const std::shared_ptr<Level> &level )
	{
		MyLevel->Bobs.clear();

		int NumStarts = __max( 1, level->CurPiece->NumBobs );

		if ( MvpOnly )
		{
			CreateBob( level, 1, 0, getMvp()->MyIndex, 0 );
		}
		else
		{
			int Count = 0;
			for ( int i = 3; i >= 0; i-- )
			{
				if ( PlayerManager::Get( i )->Exists )
				{
					int NumBobs = MyGameFlags.IsDoppleganger ? 2 : 1;
					for ( int j = 0; j < NumBobs; j++ )
					{
						Count = CreateBob( level, NumStarts, Count, i, j );
					}
				}
			}
		}

		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			SetCreatedBobParameters( *bob );
	}

	int GameData::CreateBob( const std::shared_ptr<Level> &level, int NumStarts, int Count, int i, int j )
	{
		std::shared_ptr<Bob> Player = std::make_shared<Bob>( level->DefaultHeroType, false );
		Bob_PostConstruct( Player, level->DefaultHeroType, false );

		Player->MyPlayerIndex = PlayerManager::Get( i )->MyPlayerIndex;
		MyLevel->AddBob( Player );

		Player->SetColorScheme( PlayerManager::Get( i )->ColorScheme_Renamed );

		Player->MyPiece = level->CurPiece;
		Player->MyPieceIndex = Count % NumStarts;
		Player->MyPieceIndexOffset = Count / NumStarts;

		if ( MyGameFlags.IsDopplegangerInvert )
			Player->MoveData.InvertDirX = j == 0;

		Count++;

		// Check for invisible color scheme
		bool PartiallyInvisible = false, TotallyInvisible = false;
		ColorScheme scheme = PlayerManager::Get( i )->ColorScheme_Renamed;
		if ( scheme.SkinColor->Clr.A == 0 )
			PartiallyInvisible = true;
		if ( PartiallyInvisible && ( scheme.HatData == Hat::None || scheme.HatData == Hat::NoHead ) && ( scheme.CapeColor->Clr.A == 0 && scheme.CapeOutlineColor->Clr.A == 0 ) )
			TotallyInvisible = true;

		if ( !PartiallyInvisible )
			PlayerManager::PartiallyInvisible = false;
		if ( !TotallyInvisible )
			PlayerManager::TotallyInvisible = false;
		return Count;
	}

	void GameData::SetAdditionalBobParameters( BobVec &Bobs )
	{
		// Hide corpses
		Bob::ShowCorpseAfterExplode = false;

		if ( MyGameFlags.IsTethered )
		{
			// Show corpses
			Bob::ShowCorpseAfterExplode = true;

			// Clear all existing links
			for ( BobVec::const_iterator bob = Bobs.begin(); bob != Bobs.end(); ++bob )
				if ( ( *bob )->MyBobLinks.size() > 0 )
					( *bob )->MyBobLinks.clear();

			// Link bobs together
			for ( int i = 0; i < static_cast<int>( Bobs.size() ) - 1; i++ )
			{
				std::shared_ptr<BobLink> link = std::make_shared<BobLink>();
				link->Connect( Bobs[ i ], Bobs[ i + 1 ] );
			}
		}
	}

	std::shared_ptr<GameData> GameData::StartLevel( const std::shared_ptr<LevelSeedData> &LevelSeed )
	{
		return StartLevel( LevelSeed, false );
	}

	std::shared_ptr<GameData> GameData::StartLevel( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		if ( LockLevelStart )
			return 0;

		LockLevelStart = true;

		LevelSeed->LoadingBegun = true;

		LevelSeed->Init();

		if ( !MakeInBackground )
		{
			Tools::CurGameType = LevelSeed->MyGameType;
			if ( Tools::CurGameData != 0 )
			{
				Tools::CurGameData->DefaultHeroType = LevelSeed->DefaultHeroType;
			}
		}

		std::shared_ptr<GameData> MadeGame = 0;
		MadeGame = LevelSeed->MyGameType->Make( LevelSeed, MakeInBackground );

		if ( !MakeInBackground )
			Tools::CurGameData = MadeGame;

		return MadeGame;
	}

	void GameData::UseBobLighting( const std::shared_ptr<Level> &lvl, int difficulty )
	{
		lvl->setUseLighting( true );
		lvl->StickmanLighting = true;
		lvl->SetBobLightRadius( difficulty );
		Tools::SongWad->SuppressNextInfoDisplay = true;
	}

	void GameData::RemoveLastCoinText()
	{
		for ( GameObjVec::const_iterator gameobj = MyGameObjects.begin(); gameobj != MyGameObjects.end(); ++gameobj )
			if ( ( *gameobj )->getCore()->AddedTimeStamp == MyLevel->CurPhsxStep )
				( *gameobj )->Release();
	}

	void GameData::SetDeathTime( DeathTime time )
	{
		switch ( time )
		{
			case DeathTime_FOREVER:
				DoneDyingDistance = 300000;
				DoneDyingCount = 190000;
				break;

			case DeathTime_SUPER_SLOW:
				DoneDyingDistance = 3000;
				DoneDyingCount = 190;
				break;

			case DeathTime_SLOW:
				DoneDyingDistance = 1800;
				DoneDyingCount = 110;
				break;

			case DeathTime_NORMAL:
				DoneDyingDistance = 1200;
				DoneDyingCount = 60;
				break;

			case DeathTime_FAST:
				//DoneDyingDistance = 165;
				//DoneDyingCount = 36;
				DoneDyingDistance = 125;
				DoneDyingCount = 22;
				break;

			case DeathTime_SUPER_FAST:
				DoneDyingDistance = 65;
				DoneDyingCount = 12;
				break;
		}
	}

	void GameData::EnterFrom( const std::shared_ptr<Door> &door )
	{
		EnterFrom( door, 20 );
	}

	void GameData::EnterFrom( const std::shared_ptr<Door> &door, int Wait )
	{
		// Initially close door and hide bobs
		door->SetLock( true, true, false );
		door->HideBobs();
		MoveAndUpdateBobs();
		door->MoveBobs();

		// Open the door and show the bobs
		CinematicToDo( Wait, std::make_shared<OpenDoorAndShowBobsLambda>( MyLevel, door, shared_from_this() ) );
	}

	void GameData::SetDramaticEntryParams()
	{
		int tempVector[] = { 172, 30, 90, 163 };
		DramaticEntryWait = VecFromArray( tempVector );
		DramaticEntryVel = Vector2( 0, 2 );
	}

	int GameData::DramaticEntry( const std::shared_ptr<Door> &door, int Wait )
	{
		SetDramaticEntryParams();

		WaitThenDo( 1, std::make_shared<DramaticEntryLambda>( shared_from_this(), Wait, door ) );

		return DramaticEntryWait[ 0 ] + Wait;
	}

	void GameData::MoveAndUpdateBobs()
	{
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
		{
			( *bob )->getCore()->Data.Velocity = Vector2();
			( *bob )->getCore()->Data.Acceleration = Vector2();

			bool HoldShow = ( *bob )->getCore()->Show;
			( *bob )->getCore()->Show = true;
			//bob.PhsxStep();
			( *bob )->AnimAndUpdate();
			//bob.PhsxStep2();
			( *bob )->getCore()->Show = HoldShow;
		}
	}

	void GameData::HideBobs()
	{
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			( *bob )->getCore()->Show = false;
	}

	void GameData::ShowBobs()
	{
		for ( BobVec::const_iterator bob = MyLevel->Bobs.begin(); bob != MyLevel->Bobs.end(); ++bob )
			( *bob )->getCore()->Show = true;
	}

	void GameData::LoadRecording( const std::wstring &RecordingName )
	{
		std::shared_ptr<Recording> rec = std::make_shared<Recording>( 1, 10000 );
		rec->Load( RecordingName );
		MyLevel->Bobs[ 0 ]->MyRecord = rec->Recordings[ 0 ];
		MyLevel->Bobs[ 0 ]->CompControl = true;
	}

	void GameData::InitializeInstanceFields()
	{
		_IsSetToReturnTo = false;

		HasLava = false;
		HasBeenCompleted = false;
		MyStatGroup = StatGroup_LEVEL;
		Freeplay = false;
		ParentGame = 0;
		EndMusicOnFinish = true;
		PreviousLoadFunction = 0;
		ExecutingPreviousLoadFunction = false;
		ShowHelpNotes = true;
		FadeToBlackBeforeReturn = false;
		FadingToReturn = false;
		AllowQuickJoin = false;
		DrawObjectText = false;
		SuppressSongInfo = false;
		MyGameObjects = GameObjVec();
		NewGameObjects = GameObjVec();
		TakeOnce = false;
		AlwaysGiveCoinScore = false;
		CoinScoreMultiplier = 1;
		OnCalculateCoinScoreMultiplier = std::make_shared<Multicaster_1<std::shared_ptr<GameData> > >();
		ScoreMultiplier = 1;
		OnCalculateScoreMultiplier = std::make_shared<Multicaster_1<std::shared_ptr<GameData> > >();
		OnCheckpointGrab = std::make_shared<Multicaster_1<std::shared_ptr<ObjectBase> > >();
		OnCoinGrab = std::make_shared<Multicaster_1<std::shared_ptr<ObjectBase> > >();
		OnCompleteLevel = std::make_shared<Multicaster_1<std::shared_ptr<Level> > >();
		OnLevelRetry = std::make_shared<Multicaster>();
		OnReturnTo = std::make_shared<Multicaster>();
		OnReturnTo_OneOff = std::make_shared<Multicaster>();
		ToDoOnReset = std::vector<std::shared_ptr<Lambda> >();
		DoingToDoList = false;
		DefaultHeroType = BobPhsxNormal::getInstance();
		Released = false;
		MyBankType = BankType_INFINITE;
		CreationTime = 0;
		GameObjectsAreLocked = false;
		SkipBackgroundPhsx = false;
		ClearToDoOnReturnTo = true;
		FreeReset = false;
		PhsxStepsToDo = 2;
		PhsxCount = 0;
		ForceLevelZoomBeforeDraw = 0;
		DoForceZoom = false;
		ToDoOnDeath = std::vector<std::shared_ptr<Lambda> >();
		DoneDyingDistance = 1200;
		DoneDyingCount = 60;
		ToDoOnDoneDying = std::vector<std::shared_ptr<Lambda> >();
		MvpOnly = false;
		ModdedBlobGrace = false;
		BlobGraceY = 76;
	}
}
