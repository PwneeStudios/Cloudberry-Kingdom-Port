#include <global_header.h>




















namespace Forms = System::Windows::Forms;

namespace CloudberryKingdom
{

	XnaGameClass::XnaGameClass()
	{
		Tools::GameClass = this;
		MyGame = std::make_shared<CloudberryKingdomGame>();

	#if defined(PC_VERSION)
	#elif defined(XBOX) || defined(XBOX_SIGNIN)
		getComponents()->Add(std::make_shared<GamerServicesComponent>(this));
	#endif
		getContent()->RootDirectory = _T("Content");
	}

	void XnaGameClass::Initialize()
	{
		MyGame->Initialize();

		getWindow()->Title = _T("Cloudberry Kingdom ");

		Game::Initialize();
	}

	void XnaGameClass::LoadContent()
	{
		MyGame->LoadContent();

		Game::LoadContent();
	}

	void XnaGameClass::UnloadContent()
	{
		// TODO: Unload any non ContentManager content here
	}

	void XnaGameClass::Update( const std::shared_ptr<GameTime> &gameTime )
	{
		this->setIsFixedTimeStep( Tools::FixedTimeStep );

		MyGame->RunningSlowly = gameTime->IsRunningSlowly;

		MyGame->Update();

		Game::Update( gameTime );
	}

	void XnaGameClass::Draw( const std::shared_ptr<GameTime> &gameTime )
	{
		MyGame->Draw( gameTime );

		Game::Draw( gameTime );
	}

#if defined(WINDOWS)
	void XnaGameClass::SetBorder( bool Show )
	{
		void* hWnd = Tools::GameClass->getWindow()->Handle;
		std::shared_ptr<Forms::Control> control = Control::FromHandle( hWnd );
		std::shared_ptr<Forms::Form> form = control->FindForm();
		form->FormBorderStyle = Show ? FormBorderStyle::FixedSingle : FormBorderStyle::None;
	}
#endif
}
