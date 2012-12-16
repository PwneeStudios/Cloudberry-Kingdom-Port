#include <global_header.h>


namespace CloudberryKingdom
{

	void Escalation_Tutorial::ConfigureSongsHelper::Apply()
	{
		Tools::SongWad->SuppressNextInfoDisplay = true;
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		//Tools.SongWad.SetPlayList(Tools.Song_140mph);
		Tools::SongWad->Restart( true );
	}

	Escalation_Tutorial::PreventThingsHelper::PreventThingsHelper( const boost::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::PreventThingsHelper::Apply()
	{
		et->MyGame->MyLevel->PreventHelp = false;
		et->MyGame->MyLevel->setPreventReset( false );
		et->MyGame->MyLevel->Finished = false;
	}

	Escalation_Tutorial::TitleProxy::TitleProxy( const boost::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::TitleProxy::Apply()
	{
		et->Title();
	}

	Escalation_Tutorial::TutorialOrSkipProxy::TutorialOrSkipProxy( const boost::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::TutorialOrSkipProxy::Apply()
	{
		et->TutorialOrSkip();
	}

	Escalation_Tutorial::NextTutorialHelper::NextTutorialHelper( const boost::shared_ptr<Escalation_Tutorial> &et, const boost::shared_ptr<GUI_Text> &text )
	{
		this->et = et;
		this->text = text;
	}

	void Escalation_Tutorial::NextTutorialHelper::Apply()
	{
		et->MyGame->WaitThenDo( 12, boost::make_shared<TutorialOrSkipProxy>( et ) );
		text->Kill( et->SoundOnKill );
	}

	Escalation_Tutorial::TextKillHelper::TextKillHelper( const boost::shared_ptr<Escalation_Tutorial> &et, const boost::shared_ptr<GUI_Text> &text )
	{
		this->et = et;
		this->text = text;
	}

	void Escalation_Tutorial::TextKillHelper::Apply()
	{
		text->Kill( et->SoundOnKill );
	}

	Escalation_Tutorial::ReadyProxy::ReadyProxy( const boost::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::ReadyProxy::Apply()
	{
		et->Ready();
	}

	Escalation_Tutorial::TutorialHelperReadyGo::TutorialHelperReadyGo( const boost::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::TutorialHelperReadyGo::Apply()
	{
		TutorialHelper::ReadyGo( et->MyGame, boost::make_shared<EndProxy>( et ) );
	}

	Escalation_Tutorial::EndProxy::EndProxy( const boost::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::EndProxy::Apply()
	{
		et->End();
	}

	const bool &Escalation_Tutorial::getWatchedOnce()
	{
		return _WatchedOnce;
	}

	void Escalation_Tutorial::setWatchedOnce( const bool &value )
	{
		_WatchedOnce = value;
		PlayerManager::SavePlayerData->Changed = true;
	}

bool Escalation_Tutorial::_WatchedOnce = false;
bool Escalation_Tutorial::ShowTitle = true;

	Escalation_Tutorial::Escalation_Tutorial( const boost::shared_ptr<Challenge_Escalation> &Escalation )
	{
		InitializeInstanceFields();
		this->Escalation = Escalation;
	}

	void Escalation_Tutorial::OnAdd()
	{
		GameObject::OnAdd();

		if ( MyGame->MyLevel->getStartDoor() == 0 )
			setWatchedOnce( true );

		// Add the princess
		if ( !getWatchedOnce() )
		{
			boost::shared_ptr<Level> lvl = MyGame->MyLevel;

			lvl->setPreventReset( true );
		}
		else
			setPauseGame( true );

		if ( MyGame->MyLevel->getStartDoor() != 0 )
			MyGame->HideBobs();
		MyGame->PhsxStepsToDo += 2;

		// Start the music
		MyGame->WaitThenDo( 20, boost::make_shared<ConfigureSongsHelper>() );

		if ( HeroRush_Tutorial::ShowTitle || !getWatchedOnce() )
		//if (ShowTitle || !WatchedOnce)
			MyGame->WaitThenDo( 27, boost::make_shared<TitleProxy>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ) ) );
		else
			MyGame->WaitThenDo( 20, boost::make_shared<ReadyProxy>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ) ) );
	}

	void Escalation_Tutorial::TutorialOrSkip()
	{
		if ( !getWatchedOnce() && MyGame->MyLevel->getStartDoor() != 0 )
		{
			MyGame->MyLevel->setPreventReset( MyGame->MyLevel->PreventHelp = true );

			int wait = MyGame->DramaticEntry( MyGame->MyLevel->getStartDoor(), 90 );
			MyGame->MyLevel->SetBack( wait + 90 );
			MyGame->WaitThenDo( wait, boost::make_shared<PreventThingsHelper>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ) ) );
		}
		else
			Ready();

		setWatchedOnce( true );
	}

	void Escalation_Tutorial::Title()
	{
		ShowTitle = false;

		if ( getWatchedOnce() )
		{
			boost::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Escalation->Name );
			CkColorHelper::_x_x_HappyBlueColor( text->MyText );

			MyGame->AddGameObject( text );

			// On (A) go to next part of the tutorial
			MyGame->AddGameObject( MakeMagic( Listener, ( ControllerButtons_A, boost::make_shared<NextTutorialHelper>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ), text ) ) ) );
		}
		else
		{
			boost::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Escalation->Name );
			CkColorHelper::_x_x_HappyBlueColor( text->MyText );
			text->Pos->RelVal.Y -= 800;

			MyGame->AddGameObject( text );

			MyGame->WaitThenDo( 120, boost::make_shared<TextKillHelper>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ), text ) );
			MyGame->WaitThenDo( 40, boost::make_shared<TutorialOrSkipProxy>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ) ) );
		}
	}

	void Escalation_Tutorial::Ready()
	{
		int Wait = 5 + 22;

		MyGame->WaitThenDo( Wait, boost::make_shared<TutorialHelperReadyGo>( boost::static_pointer_cast<Escalation_Tutorial>( shared_from_this() ) ) );
	}

	void Escalation_Tutorial::End()
	{
		setPauseGame( false );

		Release();
	}

	void Escalation_Tutorial::MyPhsxStep()
	{
	}

	void Escalation_Tutorial::InitializeInstanceFields()
	{
		SoundOnKill = false;
	}
}
