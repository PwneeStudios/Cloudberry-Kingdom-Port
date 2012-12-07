#include <global_header.h>

namespace CloudberryKingdom
{

	XnaGameClass::XnaGameClass()
	{
		Tools::GameClass = shared_from_this();
		MyGame = std::make_shared<CloudberryKingdomGame>();

	#if defined(PC_VERSION)
	#elif defined(XBOX) || defined(XBOX_SIGNIN)
		getComponents()->Add(std::make_shared<GamerServicesComponent>(this));
	#endif
		getContent()->RootDirectory = _T("Content");
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

		// This called the XNA base game class method. Should not be needed.
		//Game::Initialize();
	}

	void XnaGameClass::LoadContent()
	{
		MyGame->LoadContent();

		// This called the XNA base game class method. Should not be needed.
		//Game::LoadContent();
	}

	void XnaGameClass::UnloadContent()
	{
	}

	void XnaGameClass::Update( const std::shared_ptr<GameTime> &gameTime )
	{
		// FIXME: Make sure game is using a Fixed Time Step!
		//this->setIsFixedTimeStep( Tools::FixedTimeStep );

		MyGame->Update();

		// This called the XNA base game class method. Should not be needed.
		//Game::Update( gameTime );
	}

	void XnaGameClass::Draw( const std::shared_ptr<GameTime> &gameTime )
	{
		MyGame->Draw( gameTime );

		// This called the XNA base game class method. Should not be needed.
		//Game::Draw( gameTime );
	}

	void XnaGameClass::Exit()
	{
		// FIXME
	}

#if defined(WINDOWS)
	void XnaGameClass::SetBorder( bool Show )
	{
		// FIXME: Make game window borderless or not. Here was the C# code:
		//void* hWnd = Tools::GameClass->getWindow()->Handle;
		//std::shared_ptr<Forms::Control> control = Control::FromHandle( hWnd );
		//std::shared_ptr<Forms::Form> form = control->FindForm();
		//form->FormBorderStyle = Show ? FormBorderStyle::FixedSingle : FormBorderStyle::None;
	}
#endif
}
