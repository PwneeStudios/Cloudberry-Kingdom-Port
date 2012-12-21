#include <global_header.h>

namespace CloudberryKingdom
{

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	SignInMenu::SignInNoLambda::SignInNoLambda( const boost::shared_ptr<SignInMenu> &sim )
	{
		this->sim = sim;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::SignInNoLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		sim->MyCharacterSelect->Player->StoredName = std::wstring( L"" );
		sim->MyCharacterSelect->Player->Init();
		sim->Call( MakeMagic( SimpleMenu, ( sim->getControl(), sim->MyCharacterSelect ) ) );
		sim->Hide();
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	SignInMenu::SignInYesLambda::SignInYesLambda( const boost::shared_ptr<SignInMenu> &sim )
	{
		this->sim = sim;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::SignInYesLambda::Apply( const boost::shared_ptr<MenuItem> &item )
	{
		if ( !Guide::IsVisible )
		{
	#if defined(XBOX)
			if ( !Guide::IsVisible )
				Guide::ShowSignIn( 4, false );
	#else
			Guide::ShowSignIn( 1, false );
	#endif
		}

		sim->GamerGuideUp = true;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	//SignInMenu::SignInMenu( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	SignInMenu::SignInMenu( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) { }
	boost::shared_ptr<SignInMenu> SignInMenu::SignInMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( false );
		
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();

		return boost::static_pointer_cast<SignInMenu>( shared_from_this() );
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MakeSignInChoiceMenu();

		CharacterSelect::Shift( shared_from_this() );
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::MakeSignInChoiceMenu()
	{
		MyMenu = boost::make_shared<Menu>();
		MyMenu->setControl( MyCharacterSelect->PlayerIndex );
		MyMenu->SelectIcon = boost::make_shared<QuadClass>();
		MyMenu->SelectIcon->ShadowOffset = Vector2( 7.5f, 7.5f );
		MyMenu->SelectIcon->ShadowColor = Color( 30, 30, 30 );
		MyMenu->SelectIcon->Scale( 90 );
		MyMenu->SelectIcon->Quad_Renamed.MyTexture = ButtonTexture::getGo();

		MyMenu->FixedToCamera = false;

		EnsureFancy();

		MyMenu->OnB = boost::make_shared<MenuReturnToCallerLambdaFunc>( shared_from_this() );

		Vector2 pos = Vector2( 0, 0 );
		float YSpacing = 200;

		boost::shared_ptr<MenuItem> item;
		boost::shared_ptr<EzFont> font = Resources::Font_Grobold42;
		float FontScale = .775f;

		item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( std::wstring( L"Sign in?" ), font ) ) );
		item->Name = std::wstring( L"Header" );
		item->MyText->setScale( .89f );

		MyMenu->Add( item );
		item->Selectable = false;
		pos.Y -= 1.35f * YSpacing;

		const std::wstring tempVector[] = { std::wstring( L"Yes" ), std::wstring( L"No" ) };
		std::vector<std::wstring> ItemString = VecFromArray( tempVector );
		for ( int i = 0; i < 2; i++ )
		{
			item = MakeMagic( MenuItem, ( boost::make_shared<EzText>( ItemString[ i ], font ) ) );
			item->MySelectedText->setScale( FontScale );
			item->MyText->setScale( item->MySelectedText->getScale() );
			item->SelectionOscillate = false;

			MyMenu->Add( item );
			item->SelectedPos = item->Pos = pos;
			pos.Y -= YSpacing;
			item->SelectedPos.X += 15;
			item->SelectIconOffset = Vector2( 275, 3 );
		}
		MyMenu->SelectItem( 1 );

		MyMenu->Items[ 1 ]->Name = std::wstring( L"Yes" );
		MyMenu->Items[ 1 ]->setGo( boost::make_shared<SignInYesLambda>( shared_from_this() ) );

		MyMenu->Items[ 2 ]->Name = std::wstring( L"No" );
		MyMenu->Items[ 2 ]->setGo( boost::make_shared<SignInNoLambda>( shared_from_this() ) );

		MyMenu->MyPieceQuadTemplate.reset();

		SetPos();
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::SetPos()
	{
		boost::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( std::wstring( L"Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -416.668f, 527.7777f ) );
			_item->MyText->setScale( 0.89f );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"Yes" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -108.333f, 149.4445f ) );
			_item->MyText->setScale( 0.775f );
			_item->MySelectedText->setScale( 0.775f );
			_item->SelectIconOffset = Vector2( -88.88965f, -130.3333f );
		}
		_item = MyMenu->FindItemByName( std::wstring( L"No" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -72.22559f, -108.8889f ) );
			_item->MyText->setScale( 0.775f );
			_item->MySelectedText->setScale( 0.775f );
			_item->SelectIconOffset = Vector2( -88.88965f, -130.3333f );
		}
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN)) && defined(XBOX) || defined(XBOX_SIGNIN)
	bool SignInMenu::GuideUpPhsxStep()
	{
		if ( !GamerGuideUp && !Guide::IsVisible )
			return false;

		if ( Guide::IsVisible )
		{
			GamerGuideUp = true;
			return true;
		}
		else
			GamerGuideUp = false;

		// The guide just went down. Check to see if someone signed in and act accordingly.
		if ( MyCharacterSelect->getPlayer()->getMyGamer() != 0 )
		{
			Call( MakeMagic( SimpleMenu, ( getControl(), MyCharacterSelect ) ) );
			Hide();
		}
		else
			ReturnToCaller();

		return false;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

	#if defined(XBOX) || defined(XBOX_SIGNIN)
		if ( GuideUpPhsxStep() )
			return;
	#endif

		MyCharacterSelect->MyState = CharacterSelect::SelectState_SELECTING;
		MyCharacterSelect->MyDoll->ShowBob = false;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = false;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::InitializeInstanceFields()
	{
		GamerGuideUp = false;
	}
#endif
}
