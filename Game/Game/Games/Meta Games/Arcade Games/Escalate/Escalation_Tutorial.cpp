#include "Escalation_Tutorial.h"
#include "Game/Tools/Tools.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Games/TutorialHelper.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Tools/CkColorHelper.h"
#include "Game/Objects/Game Objects/GameObjects/Listener.h"
#include "Core/Input/ButtonCheck.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	void Escalation_Tutorial::ConfigureSongsHelper::Apply()
	{
		Tools::SongWad->SuppressNextInfoDisplay = true;
		Tools::SongWad->SetPlayList( Tools::SongList_Standard );
		//Tools.SongWad.SetPlayList(Tools.Song_140mph);
		Tools::SongWad->Restart( true );
	}

	Escalation_Tutorial::PreventThingsHelper::PreventThingsHelper( const std::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::PreventThingsHelper::Apply()
	{
		et->MyGame->MyLevel->PreventHelp = false;
		et->MyGame->MyLevel->setPreventReset( false );
		et->MyGame->MyLevel->Finished = false;
	}

	Escalation_Tutorial::TitleProxy::TitleProxy( const std::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::TitleProxy::Apply()
	{
		et->Title();
	}

	Escalation_Tutorial::TutorialOrSkipProxy::TutorialOrSkipProxy( const std::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::TutorialOrSkipProxy::Apply()
	{
		et->TutorialOrSkip();
	}

	Escalation_Tutorial::NextTutorialHelper::NextTutorialHelper( const std::shared_ptr<Escalation_Tutorial> &et, const std::shared_ptr<GUI_Text> &text )
	{
		this->et = et;
		this->text = text;
	}

	void Escalation_Tutorial::NextTutorialHelper::Apply()
	{
		et->MyGame->WaitThenDo( 12, std::make_shared<TutorialOrSkipProxy>( et ) );
		text->Kill( et->SoundOnKill );
	}

	Escalation_Tutorial::TextKillHelper::TextKillHelper( const std::shared_ptr<Escalation_Tutorial> &et, const std::shared_ptr<GUI_Text> &text )
	{
		this->et = et;
		this->text = text;
	}

	void Escalation_Tutorial::TextKillHelper::Apply()
	{
		text->Kill( et->SoundOnKill );
	}

	Escalation_Tutorial::ReadyProxy::ReadyProxy( const std::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::ReadyProxy::Apply()
	{
		et->Ready();
	}

	Escalation_Tutorial::TutorialHelperReadyGo::TutorialHelperReadyGo( const std::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::TutorialHelperReadyGo::Apply()
	{
		TutorialHelper::ReadyGo( et->MyGame, std::make_shared<EndProxy>( et ) );
	}

	Escalation_Tutorial::EndProxy::EndProxy( const std::shared_ptr<Escalation_Tutorial> &et )
	{
		this->et = et;
	}

	void Escalation_Tutorial::EndProxy::Apply()
	{
		et->End();
	}

	const bool &Escalation_Tutorial::getWatchedOnce() const
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

	Escalation_Tutorial::Escalation_Tutorial( const std::shared_ptr<Challenge_Escalation> &Escalation )
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
			std::shared_ptr<Level> lvl = MyGame->MyLevel;

			lvl->setPreventReset( true );
		}
		else
			setPauseGame( true );

		if ( MyGame->MyLevel->getStartDoor() != 0 )
			MyGame->HideBobs();
		MyGame->PhsxStepsToDo += 2;

		// Start the music
		MyGame->WaitThenDo( 20, std::make_shared<ConfigureSongsHelper>() );

		if ( HeroRush_Tutorial::ShowTitle || !getWatchedOnce() )
		//if (ShowTitle || !WatchedOnce)
			MyGame->WaitThenDo( 27, std::make_shared<TitleProxy>( this ) );
		else
			MyGame->WaitThenDo( 20, std::make_shared<ReadyProxy>( this ) );
	}

	void Escalation_Tutorial::TutorialOrSkip()
	{
		if ( !getWatchedOnce() && MyGame->MyLevel->getStartDoor() != 0 )
		{
			MyGame->MyLevel->setPreventReset( MyGame->MyLevel->PreventHelp = true );

			int wait = MyGame->DramaticEntry( MyGame->MyLevel->getStartDoor(), 90 );
			MyGame->MyLevel->SetBack( wait + 90 );
			MyGame->WaitThenDo( wait, std::make_shared<PreventThingsHelper>( this ) );
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
			std::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Escalation->Name );
			CkColorHelper::_x_x_HappyBlueColor( text->MyText );

			MyGame->AddGameObject( text );

			// On (A) go to next part of the tutorial
			MyGame->AddGameObject( std::make_shared<Listener>( ControllerButtons_A, std::make_shared<NextTutorialHelper>( this, text ) ) );
		}
		else
		{
			std::shared_ptr<GUI_Text> text = GUI_Text::SimpleTitle( Escalation->Name );
			CkColorHelper::_x_x_HappyBlueColor( text->MyText );
			text->Pos->RelVal.Y -= 800;

			MyGame->AddGameObject( text );

			MyGame->WaitThenDo( 120, std::make_shared<TextKillHelper>( this, text ) );
			MyGame->WaitThenDo( 40, std::make_shared<TutorialOrSkipProxy>( this ) );
		}
	}

	void Escalation_Tutorial::Ready()
	{
		int Wait = 5 + 22;

		MyGame->WaitThenDo( Wait, std::make_shared<TutorialHelperReadyGo>( this ) );
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
