#include <global_header.h>

#include "CloudberryKingdom.XnaGameClass.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <Core.h>

namespace CloudberryKingdom
{

	XnaGameClass::XnaGameClass()
	{
		Content = boost::make_shared<ContentManager>( std::wstring( L"Content" ) );

		//Tools::GameClass = shared_from_this();
		MyGame = boost::make_shared<CloudberryKingdomGame>();
		Tools::TheGame = MyGame;

	#if defined(PC_VERSION)
	#elif defined(XBOX) || defined(XBOX_SIGNIN)
		getComponents()->Add(boost::make_shared<GamerServicesComponent>(this));
	#endif
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

		//getWindow()->Title = _T("Cloudberry Kingdom ");
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
