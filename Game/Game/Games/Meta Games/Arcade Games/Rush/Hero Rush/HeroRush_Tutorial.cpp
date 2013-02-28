#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	void HeroRush_Tutorial::InitializeStatics()
	{
		HeroRush_Tutorial::HasWatchedOnce = false;
		HeroRush_Tutorial::TemporarySkip = false;
		HeroRush_Tutorial::ShowTitle = true;
	}

	// Statics
	bool HeroRush_Tutorial::HasWatchedOnce;
	bool HeroRush_Tutorial::TemporarySkip;
	bool HeroRush_Tutorial::ShowTitle;


	void HeroRush_Tutorial::StartMusicHelper::Apply()
	{
		Tools::SongWad->SuppressNextInfoDisplay = true;
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		Tools::SongWad->Shuffle();
		Tools::SongWad->Restart( true );
	}

	HeroRush_Tutorial::TutorialOrSkipProxy::TutorialOrSkipProxy( const boost::shared_ptr<HeroRush_Tutorial> &tutorial )
	{
		this->tutorial = tutorial;
	}

	void HeroRush_Tutorial::TutorialOrSkipProxy::Apply()
	{
		tutorial->TutorialOrSkip();
	}

	HeroRush_Tutorial::ListenerHelper::ListenerHelper( const boost::shared_ptr<HeroRush_Tutorial> &tutorial, const boost::shared_ptr<GUI_Text> &text )
	{
		this->tutorial = tutorial;
		this->text = text;
	}

	void HeroRush_Tutorial::ListenerHelper::Apply()
	{
		tutorial->MyGame->WaitThenDo( 12, boost::make_shared<TutorialOrSkipProxy>( tutorial ) );
		text->Kill( tutorial->SoundOnKill );
	}

	HeroRush_Tutorial::AddGameObjectHelper::AddGameObjectHelper( const boost::shared_ptr<HeroRush_Tutorial> &tutorial, const boost::shared_ptr<GUI_Text> &text )
	{
		this->tutorial = tutorial;
		this->text = text;
	}

	void HeroRush_Tutorial::AddGameObjectHelper::Apply()
	{
		// On (A) go to next part of the tutorial
		tutorial->MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<ListenerHelper>( tutorial, text ) ) ) );
	}

	HeroRush_Tutorial::TitleProxy::TitleProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::TitleProxy::Apply()
	{
		hrt->Title();
	}

	HeroRush_Tutorial::TitleNextTutorialHelper::TitleNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<GUI_Text> &text )
	{
		this->hrt = hrt;
		this->text = text;
	}

	void HeroRush_Tutorial::TitleNextTutorialHelper::Apply()
	{
		hrt->MyGame->WaitThenDo( 12, boost::make_shared<TutorialOrSkipProxy>( hrt ) );
		text->Kill( hrt->SoundOnKill );
	}

	HeroRush_Tutorial::HeroRushTimerShowHelper::HeroRushTimerShowHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::HeroRushTimerShowHelper::Apply()
	{
		hrt->HeroRush->Timer->Show();
	}

	HeroRush_Tutorial::PointAtDoorNextTutorialHelper::PointAtDoorNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<Arrow> &arrow, const boost::shared_ptr<GUI_Text> &text )
	{
		this->hrt = hrt;
		this->arrow = arrow;
		this->text = text;
	}

	void HeroRush_Tutorial::PointAtDoorNextTutorialHelper::Apply()
	{
		arrow->Release();
		text->Kill( hrt->SoundOnKill );

		hrt->MyGame->WaitThenDo( 7, boost::make_shared<HeroRushTimerShowHelper>( hrt ) );
		hrt->MyGame->WaitThenDo( 0, boost::make_shared<PointAtTimerProxy>( hrt ) );
	}

	HeroRush_Tutorial::PointAtTimerProxy::PointAtTimerProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::PointAtTimerProxy::Apply()
	{
		hrt->PointAtTimer();
	}

	HeroRush_Tutorial::PointAtTimerNextTutorialHelper::PointAtTimerNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<Arrow> &arrow, const boost::shared_ptr<GUI_Text> &text, const boost::shared_ptr<GUI_Text> &text2 )
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
	}

	HeroRush_Tutorial::PointAtCoinsNextTutorialHelper::PointAtCoinsNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<GUI_Text> &text, const std::vector<boost::shared_ptr<Arrow> > &arrows )
	{
		this->hrt = hrt;
		this->text = text;
		this->arrows = arrows;
	}

	void HeroRush_Tutorial::PointAtCoinsNextTutorialHelper::Apply()
	{
		hrt->PointAtScore();
		for ( std::vector<boost::shared_ptr<Arrow> >::const_iterator arrow = arrows.begin(); arrow != arrows.end(); ++arrow )
		{
			( *arrow )->Release();
		}
		text->Kill( hrt->SoundOnKill );
	}

	HeroRush_Tutorial::PointAtScoreNextTutorialHelper::PointAtScoreNextTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt, const boost::shared_ptr<Arrow> &arrow, const boost::shared_ptr<GUI_Text> &text )
	{
		this->hrt = hrt;
		this->arrow = arrow;
		this->text = text;
	}

	void HeroRush_Tutorial::PointAtScoreNextTutorialHelper::Apply()
	{
		hrt->MyGame->WaitThenDo( 0, boost::make_shared<ReadyProxy>( hrt ) );
		//Ready();
		arrow->Release();
		text->Kill( false );
	}

	HeroRush_Tutorial::ReadyProxy::ReadyProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::ReadyProxy::Apply()
	{
		hrt->Ready();
	}

	HeroRush_Tutorial::ReadyTutorialHelper::ReadyTutorialHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::ReadyTutorialHelper::Apply()
	{
		TutorialHelper::ReadyGo( hrt->MyGame, boost::make_shared<EndProxy>( hrt ) );
	}

	HeroRush_Tutorial::PauseHeroRushTimerHelper::PauseHeroRushTimerHelper( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::PauseHeroRushTimerHelper::Apply()
	{
		hrt->HeroRush->Timer->PauseOnPause = true;
	}

	HeroRush_Tutorial::EndProxy::EndProxy( const boost::shared_ptr<HeroRush_Tutorial> &hrt )
	{
		this->hrt = hrt;
	}

	void HeroRush_Tutorial::EndProxy::Apply()
	{
		hrt->End();
	}

	void HeroRush_Tutorial::WatchedOnce()
	{
		HasWatchedOnce = true;
		PlayerManager::SavePlayerData->Changed = true;
	}

	HeroRush_Tutorial::HeroRush_Tutorial( const boost::shared_ptr<Challenge_HeroRush> &HeroRush )
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
		boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( MyGame->MyLevel->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 != door )
		{
			for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
				( *bob )->getCore()->Show = false;
		}

		// Start the music
		MyGame->WaitThenDo( 20, boost::make_shared<StartMusicHelper>() );

		if ( ShowTitle || !HasWatchedOnce || CloudberryKingdomGame::AlwaysGiveTutorials )
			MyGame->WaitThenDo( 27, boost::make_shared<TitleProxy>( boost::static_pointer_cast<HeroRush_Tutorial>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ) ) ) );
		else
			MyGame->WaitThenDo( 20, boost::make_shared<ReadyProxy>( boost::static_pointer_cast<HeroRush_Tutorial>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ) ) ) );
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

		boost::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Localization::Words_HeroRush );

		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<TitleNextTutorialHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), text ) ) ) );
	}

	void HeroRush_Tutorial::PointAtDoor()
	{
		//HeroRush.Timer.Show();

		boost::shared_ptr<ObjectBase> end_door = MyGame->MyLevel->FindIObject( LevelConnector::EndOfLevelCode );
		Vector2 endpos = end_door->getCore()->Data.Position;

		boost::shared_ptr<Arrow> arrow = boost::make_shared<Arrow>();
		arrow->SetOrientation( Arrow::Orientation_RIGHT );
		arrow->Move( endpos + Vector2( -673, 0 ) );
		arrow->PointTo( endpos );
		MyGame->AddGameObject( arrow );

		boost::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( Localization::Words_GetToTheExit, arrow->getCore()->Data.Position + Vector2(-200, 400) ) );
		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<PointAtDoorNextTutorialHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), arrow, text ) ) ) );
	}

	void HeroRush_Tutorial::PointAtTimer()
	{
		//Vector2 timerpos = HeroRush.Timer.ApparentPos;
		Vector2 timerpos = MyGame->getCamPos() + Vector2(-60, 1000);

		boost::shared_ptr<Arrow> arrow = boost::make_shared<Arrow>();
		arrow->SetOrientation( Arrow::Orientation_RIGHT );
		arrow->Move( timerpos + Vector2( 30, -655 ) );
		arrow->PointTo( timerpos );
		MyGame->AddGameObject( arrow );


		std::wstring s = Format( Localization::WordString( Localization::Words_SecondsOnTheClock ).c_str(), HeroRush->Timer->getSeconds() );
		boost::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( s, arrow->getCore()->Data.Position + Vector2(0, -530) ) );

		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<PointAtTimerNextTutorialHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), arrow, text, 0 ) ) ) );
	}

	void HeroRush_Tutorial::PointAtCoins()
	{
		std::vector<boost::shared_ptr<Arrow> > arrows;
		ObjectVec vec = MyGame->MyLevel->GetObjectList( ObjectType_COIN );
		for ( ObjectVec::const_iterator coin = vec.begin(); coin != vec.end(); ++coin )
		{
			Vector2 coinpos = ( *coin )->getCore()->Data.Position;

			boost::shared_ptr<Arrow> arrow = boost::make_shared<Arrow>();
			arrow->SetScale( 300 );
			arrow->SetOrientation( Arrow::Orientation_LEFT );
			arrow->Move( coinpos + Vector2( 120, 200 ) * 1.04f );
			arrow->PointTo( coinpos );
			MyGame->AddGameObject( arrow );
			arrows.push_back( arrow );
		}

		boost::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( Localization::Words_CoinsAddSeconds, Tools::CurLevel->getMainCamera()->Data.Position + Vector2(0, -750) ) );
		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<PointAtCoinsNextTutorialHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), text, arrows ) ) ) );
	}

	void HeroRush_Tutorial::PointAtScore()
	{
		boost::shared_ptr<GUI_Score> score = 0;
		for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
		{
			if ( boost::dynamic_pointer_cast<GUI_Score>( *obj ) != 0 )
			{
				score = boost::dynamic_pointer_cast<GUI_Score>( *obj );
				break;
			}
		}
		if ( 0 == score )
		{
			End();
			return;
		}

		Vector2 scorepos = score->MyPile->FancyPos->AbsVal + Vector2( -60, 40 );

		boost::shared_ptr<Arrow> arrow = boost::make_shared<Arrow>();
		arrow->SetOrientation( Arrow::Orientation_RIGHT );
		arrow->Move( scorepos + Vector2( -510, -430 ) );
		arrow->PointTo( scorepos );
		MyGame->AddGameObject( arrow );

		boost::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( Localization::Words_GetAHighScore, arrow->getCore()->Data.Position + Vector2(-500, -100) + Vector2(-38.88892f, -150) ) );
		MyGame->AddGameObject( text );

		// On (A) go to next part of the tutorial
		MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<PointAtScoreNextTutorialHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ), arrow, text ) ) ) );
	}

	void HeroRush_Tutorial::Ready()
	{
		int Wait = 5 + 22;
		if ( HeroRush->Timer->Hid )
			Wait = 28 + 12;

		HeroRush->Timer->Show();
		HeroRush->Timer->PauseOnPause = false; // Start the timer

		MyGame->WaitThenDo( Wait, boost::make_shared<ReadyTutorialHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ) ) );
	}

	void HeroRush_Tutorial::End()
	{
		setPauseGame( false );
		MyGame->WaitThenDo( 25, boost::make_shared<PauseHeroRushTimerHelper>( boost::static_pointer_cast<HeroRush_Tutorial>( shared_from_this() ) ) );

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
