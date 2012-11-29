#include <global_header.h>


namespace CloudberryKingdom
{

	void HeroRush_Tutorial::StartMusicHelper::Apply()
	{
		Tools::SongWad->SuppressNextInfoDisplay = true;
		Tools::SongWad->SetPlayList( Tools::Song_140mph );
		Tools::SongWad->Restart( true );
	}

	HeroRush_Tutorial::TutorialOrSkipProxy::TutorialOrSkipProxy( const std::shared_ptr<HeroRush_Tutorial> &tutorial )
	{
		this->tutorial = tutorial;
	}

	void HeroRush_Tutorial::TutorialOrSkipProxy::Apply()
	{
		tutorial->TutorialOrSkip();
	}

	HeroRush_Tutorial::ListenerHelper::ListenerHelper( const std::shared_ptr<HeroRush_Tutorial> &tutorial, const std::shared_ptr<GUI_Text> &text )
	{
		this->tutorial = tutorial;
		this->text = text;
	}

	void HeroRush_Tutorial::ListenerHelper::Apply()
	{
		tutorial->MyGame->WaitThenDo( 12, std::make_shared<TutorialOrSkipProxy>( tutorial ) );
		text->Kill( tutorial->SoundOnKill );
	}

	HeroRush_Tutorial::AddGameObjectHelper::AddGameObjectHelper( const std::shared_ptr<HeroRush_Tutorial> &tutorial, const std::shared_ptr<GUI_Text> &text )
	{
		this->tutorial = tutorial;
		this->text = text;
	}

	void HeroRush_Tutorial::AddGameObjectHelper::Apply()
	{
		// On (A) go to next part of the tutorial
		tutorial->MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<ListenerHelper>( tutorial, text ) ) );
	}

	HeroRush_Tutorial::TitleProxy::TitleProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::TitleProxy::Apply()
	{
		hrt->Title();
	}

	HeroRush_Tutorial::TitleNextTutorialHelper::TitleNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<GUI_Text> &text )
	{
		this->hrt = hrt;
		this->text = text;
	}

	void HeroRush_Tutorial::TitleNextTutorialHelper::Apply()
	{
		hrt->MyGame->WaitThenDo( 12, std::make_shared<TutorialOrSkipProxy>( hrt ) );
		text->Kill( hrt->SoundOnKill );
	}

	HeroRush_Tutorial::HeroRushTimerShowHelper::HeroRushTimerShowHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::HeroRushTimerShowHelper::Apply()
	{
		hrt->HeroRush->Timer->Show();
	}

	HeroRush_Tutorial::PointAtDoorNextTutorialHelper::PointAtDoorNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text )
	{
		this->hrt = hrt;
		this->arrow = arrow;
		this->text = text;
	}

	void HeroRush_Tutorial::PointAtDoorNextTutorialHelper::Apply()
	{
		arrow->Release();
		text->Kill( hrt->SoundOnKill );

		hrt->MyGame->WaitThenDo( 7, std::make_shared<HeroRushTimerShowHelper>( hrt ) );
		hrt->MyGame->WaitThenDo( 0, std::make_shared<PointAtTimerProxy>( hrt ) );
	}

	HeroRush_Tutorial::PointAtTimerProxy::PointAtTimerProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::PointAtTimerProxy::Apply()
	{
		hrt->PointAtTimer();
	}

	HeroRush_Tutorial::PointAtTimerNextTutorialHelper::PointAtTimerNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text, const std::shared_ptr<GUI_Text> &text2 )
	{
		this->hrt = hrt;
		this->arrow = arrow;
		this->text = text;
		this->text2 = text2;
	}

	void HeroRush_Tutorial::PointAtTimerNextTutorialHelper::Apply()
	{
		hrt->PointAtCoins();
		arrow->Release();
		text->Kill( hrt->SoundOnKill );
		text2->Kill( false );
	}

	HeroRush_Tutorial::PointAtCoinsNextTutorialHelper::PointAtCoinsNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<GUI_Text> &text, std::vector<Arrow*> &arrows )
	{
		this->hrt = hrt;
		this->text = text;
		this->arrows = arrows;
	}

	void HeroRush_Tutorial::PointAtCoinsNextTutorialHelper::Apply()
	{
		hrt->PointAtScore();
		for ( std::vector<Arrow*>::const_iterator arrow = arrows.begin(); arrow != arrows.end(); ++arrow )
		{
			( *arrow )->Release();
		}
		text->Kill( hrt->SoundOnKill );
	}

	HeroRush_Tutorial::PointAtScoreNextTutorialHelper::PointAtScoreNextTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt, const std::shared_ptr<Arrow> &arrow, const std::shared_ptr<GUI_Text> &text )
	{
		this->hrt = hrt;
		this->arrow = arrow;
		this->text = text;
	}

	void HeroRush_Tutorial::PointAtScoreNextTutorialHelper::Apply()
	{
		hrt->MyGame->WaitThenDo( 0, std::make_shared<ReadyProxy>( hrt ) );
		//Ready();
		arrow->Release();
		text->Kill( false );
	}

	HeroRush_Tutorial::ReadyProxy::ReadyProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::ReadyProxy::Apply()
	{
		hrt->Ready();
	}

	HeroRush_Tutorial::ReadyTutorialHelper::ReadyTutorialHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::ReadyTutorialHelper::Apply()
	{
		TutorialHelper::ReadyGo( hrt->MyGame, std::make_shared<EndProxy>( hrt ) );
	}

	HeroRush_Tutorial::PauseHeroRushTimerHelper::PauseHeroRushTimerHelper( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::PauseHeroRushTimerHelper::Apply()
	{
		hrt->HeroRush->Timer->PauseOnPause = true;
	}

	HeroRush_Tutorial::EndProxy::EndProxy( const std::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::EndProxy::Apply()
	{
		hrt->End();
	}

bool HeroRush_Tutorial::HasWatchedOnce = false;

	void HeroRush_Tutorial::WatchedOnce()
	{
		HasWatchedOnce = true;
		PlayerManager::SavePlayerData->Changed = true;
	}

bool HeroRush_Tutorial::TemporarySkip = false;
bool HeroRush_Tutorial::ShowTitle = true;

	HeroRush_Tutorial::HeroRush_Tutorial( const std::shared_ptr<Challenge_HeroRush> &HeroRush )
	{
		InitializeInstanceFields();
		this->HeroRush = HeroRush;

		HeroRush->Timer->Hide();
	}

	void HeroRush_Tutorial::OnAdd()
	{
		GameObject::OnAdd();

		setPauseGame( true );

		// Find the initial door
		std::shared_ptr<Door> door = dynamic_cast<Door*>( MyGame->MyLevel->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 != door )
		{
			for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
				( *bob )->getCore()->Show = false;
		}

		// Start the music
		MyGame->WaitThenDo( 20, std::make_shared<StartMusicHelper>() );

		if ( ShowTitle || !HasWatchedOnce || CloudberryKingdomGame::AlwaysGiveTutorials )
			MyGame->WaitThenDo( 27, std::make_shared<TitleProxy>( this ) );
		else
			MyGame->WaitThenDo( 20, std::make_shared<ReadyProxy>( this ) );
	}

	void HeroRush_Tutorial::TutorialOrSkip()
	{
		if ( !CloudberryKingdomGame::AlwaysGiveTutorials && ( HasWatchedOnce || TemporarySkip ) )
			Ready();
		else
		{
			StartTutorial();

			WatchedOnce();
		}

		TemporarySkip = false;
	}

	void HeroRush_Tutorial::StartTutorial()
	{
		PointAtDoor();
	}

	void HeroRush_Tutorial::Title()
	{
		ShowTitle = false;

		std::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Localization::Words_HERO_RUSH );

		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<TitleNextTutorialHelper>( this, text ) ) );
	}

	void HeroRush_Tutorial::PointAtDoor()
	{
		//HeroRush.Timer.Show();

		std::shared_ptr<ObjectBase> end_door = MyGame->MyLevel->FindIObject( LevelConnector::EndOfLevelCode );
		Vector2 endpos = end_door->getCore()->Data.Position;

		std::shared_ptr<Arrow> arrow = std::make_shared<Arrow>();
		arrow->SetOrientation( Arrow::Orientation_RIGHT );
		arrow->Move( endpos + Vector2( -673, 0 ) );
		arrow->PointTo( endpos );
		MyGame->AddGameObject( arrow );

		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( Localization::Words_GET_TO_THE_EXIT, arrow->getCore()->Data.Position + Vector2(-200, 400) );
		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<PointAtDoorNextTutorialHelper>( this, arrow, text ) ) );
	}

	void HeroRush_Tutorial::PointAtTimer()
	{
		//Vector2 timerpos = HeroRush.Timer.ApparentPos;
		Vector2 timerpos = MyGame->getCamPos() + Vector2(-60, 1000);

		std::shared_ptr<Arrow> arrow = std::make_shared<Arrow>();
		arrow->SetOrientation( Arrow::Orientation_RIGHT );
		arrow->Move( timerpos + Vector2( 30, -655 ) );
		arrow->PointTo( timerpos );
		MyGame->AddGameObject( arrow );


		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( Localization::Words_SECONDS_ON_THE_CLOCK, arrow->getCore()->Data.Position + Vector2(830, -130) );

		std::shared_ptr<GUI_Text> text2 = std::make_shared<GUI_Text>( StringConverterHelper::toString( HeroRush->Timer->getSeconds() ), arrow->getCore()->Data.Position + Vector2(830, -130) + Vector2(-150, 0) );

		MyGame->AddGameObject( text );
		MyGame->AddGameObject( text2 );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<PointAtTimerNextTutorialHelper>( this, arrow, text, text2 ) ) );
	}

	void HeroRush_Tutorial::PointAtCoins()
	{
		std::vector<Arrow*> arrows = std::vector<Arrow*>();
		for ( ObjectVec::const_iterator coin = MyGame->MyLevel->GetObjectList( ObjectType_COIN ).begin(); coin != MyGame->MyLevel->GetObjectList(ObjectType_COIN).end(); ++coin )
		{
			Vector2 coinpos = ( *coin )->getCore()->Data->Position;

			std::shared_ptr<Arrow> arrow = std::make_shared<Arrow>();
			arrow->SetScale( 300 );
			arrow->SetOrientation( Arrow::Orientation_LEFT );
			arrow->Move( coinpos + Vector2( 120, 200 ) * 1.04f );
			arrow->PointTo( coinpos );
			MyGame->AddGameObject( arrow );
			arrows.push_back( arrow );
		}

		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( Localization::Words_COINS_ADD_SECONDS, Tools::CurLevel->getMainCamera()->Data.Position + Vector2(0, -750) );
		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<PointAtCoinsNextTutorialHelper>( this, text, arrows ) ) );
	}

	void HeroRush_Tutorial::PointAtScore()
	{
		std::shared_ptr<GUI_Score> score = 0;
		for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
		{
			if ( dynamic_cast<GUI_Score*>( *obj ) != 0 )
			{
				score = dynamic_cast<GUI_Score*>( *obj );
				break;
			}
		}
		if ( 0 == score )
		{
			End();
			return;
		}

		Vector2 scorepos = score->MyPile->FancyPos->AbsVal + Vector2( -60, 40 );

		std::shared_ptr<Arrow> arrow = std::make_shared<Arrow>();
		arrow->SetOrientation( Arrow::Orientation_RIGHT );
		arrow->Move( scorepos + Vector2( -510, -430 ) );
		arrow->PointTo( scorepos );
		MyGame->AddGameObject( arrow );

		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( Localization::Words_GET_AHIGH_SCORE, arrow->getCore()->Data.Position + Vector2(-500, -100) + Vector2(-38.88892f, -150) );
		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<PointAtScoreNextTutorialHelper>( this, arrow, text ) ) );
	}

	void HeroRush_Tutorial::Ready()
	{
		int Wait = 5 + 22;
		if ( HeroRush->Timer->Hid )
			Wait = 28 + 12;

		HeroRush->Timer->Show();
		HeroRush->Timer->PauseOnPause = false; // Start the timer

		MyGame->WaitThenDo( Wait, std::make_shared<ReadyTutorialHelper>( this ) );
	}

	void HeroRush_Tutorial::End()
	{
		setPauseGame( false );
		MyGame->WaitThenDo( 25, std::make_shared<PauseHeroRushTimerHelper>( this ) );

		Release();
	}

	void HeroRush_Tutorial::MyPhsxStep()
	{
	}

	void HeroRush_Tutorial::InitializeInstanceFields()
	{
		SoundOnKill = false;
	}
}
