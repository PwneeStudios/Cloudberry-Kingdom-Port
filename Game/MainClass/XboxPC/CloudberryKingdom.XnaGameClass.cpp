#include <small_header.h>

#include "CloudberryKingdom.XnaGameClass.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#include "Game/Tools/WrappedFloat.h"

#include <Core.h>

namespace CloudberryKingdom
{

	XnaGameClass::XnaGameClass()
	{
		Content = boost::make_shared<ContentManager>( std::wstring( L"Content" ) );

		Tools::InitializeStatics();

		// Volume control
		Tools::SoundVolume = boost::make_shared<WrappedFloat>();
		Tools::SoundVolume->MinVal = 0;
		Tools::SoundVolume->MaxVal = 1;
		Tools::SoundVolume->setVal( .7f );

		Tools::MusicVolume = boost::make_shared<WrappedFloat>();
		Tools::MusicVolume->MinVal = 0;
		Tools::MusicVolume->MaxVal = 1;
		Tools::MusicVolume->setVal( 1 );
		Tools::MusicVolume->SetCallback = boost::make_shared<CloudberryKingdomGame::UpdateVolumeProxy>();

#if defined(DEBUG) || defined(INCLUDE_EDITOR)
		Tools::SoundVolume->setVal( 0 );
		Tools::MusicVolume->setVal( 0 );
#endif


		//Tools::GameClass = shared_from_this();
		MyGame = boost::make_shared<CloudberryKingdomGame>();
		Tools::TheGame = MyGame;
	}

	bool XnaGameClass::getIsActive()
	{
		// FIXME: should detect if game window has focus.
		return true;
	}

	void XnaGameClass::setIsMouseVisible( bool visible )
	{
		// FIXME: Should set whether the mouse cursor is visible or not.
	}

	void XnaGameClass::Initialize()
	{
		MyGame->Initialize();

		//getWindow()->Title = std::wstring( L"Cloudberry Kingdom " );
		// FIXME: Set the title of the window to "Cloudberry Kingdom "

		// This called the XNA base game struct method. Should not be needed.
		//Game::Initialize();
	}

	void XnaGameClass::LoadContent()
	{
		MyGame->LoadContent();

		// This called the XNA base game struct method. Should not be needed.
		//Game::LoadContent();
	}

	void XnaGameClass::UnloadContent()
	{
	}

	void XnaGameClass::Update( const boost::shared_ptr<GameTime> &gameTime )
	{
		// FIXME: Make sure game is using a Fixed Time Step!
		//this->setIsFixedTimeStep( Tools::FixedTimeStep );

		MyGame->Update();

		// This called the XNA base game struct method. Should not be needed.
		//Game::Update( gameTime );
	}

	void XnaGameClass::Draw( const boost::shared_ptr<GameTime> &gameTime )
	{
		MyGame->Draw( gameTime );

		// This called the XNA base game struct method. Should not be needed.
		//Game::Draw( gameTime );
	}

	void XnaGameClass::Exit()
	{
		// FIXME
		CORE.Exit();
	}

#if defined(WINDOWS)
	void XnaGameClass::SetBorder( bool Show )
	{
		// FIXME: Make game window borderless or not. Here was the C# code:
		//void* hWnd = Tools::GameClass->getWindow()->Handle;
		//boost::shared_ptr<Forms::Control> control = Control::FromHandle( hWnd );
		//boost::shared_ptr<Forms::Form> form = control->FindForm();
		//form->FormBorderStyle = Show ? FormBorderStyle::FixedSingle : FormBorderStyle::None;
	}
#endif
}
