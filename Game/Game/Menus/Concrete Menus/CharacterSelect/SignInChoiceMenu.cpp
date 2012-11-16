#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	SignInMenu::SignInNoLambda::SignInNoLambda( const std::shared_ptr<SignInMenu> &sim )
	{
		this->sim = sim;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::SignInNoLambda::Apply( const std::shared_ptr<MenuItem> &item )
	{
		sim->MyCharacterSelect->Player->StoredName = _T( "" );
		sim->MyCharacterSelect->Player->Init();
		sim->Call( std::make_shared<SimpleMenu>( sim->getControl(), sim->MyCharacterSelect ) );
		sim->Hide();
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	SignInMenu::SignInYesLambda::SignInYesLambda( const std::shared_ptr<SignInMenu> &sim )
	{
		this->sim = sim;
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::SignInYesLambda::Apply( const std::shared_ptr<MenuItem> &item )
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
	SignInMenu::SignInMenu( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	{
		InitializeInstanceFields();
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();
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

		CharacterSelect::Shift( this );
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::MakeSignInChoiceMenu()
	{
		MyMenu = std::make_shared<Menu>();
		MyMenu->setControl( MyCharacterSelect->PlayerIndex );
		MyMenu->SelectIcon = std::make_shared<QuadClass>();
		MyMenu->SelectIcon->ShadowOffset = Vector2( 7.5f, 7.5f );
		MyMenu->SelectIcon->ShadowColor = Color( 30, 30, 30 );
		MyMenu->SelectIcon->Scale( 90 );
		MyMenu->SelectIcon->Quad_Renamed->MyTexture = ButtonTexture::getGo();

		MyMenu->FixedToCamera = false;

		EnsureFancy();

		MyMenu->OnB = std::make_shared<MenuReturnToCallerLambdaFunc>( this );

		Vector2 pos = Vector2( 0, 0 );
		float YSpacing = 200;

		std::shared_ptr<MenuItem> item;
		std::shared_ptr<EzFont> font = Resources::Font_Grobold42;
		float FontScale = .775f;

		item = std::make_shared<MenuItem>( std::make_shared<EzText>( _T( "Sign in?" ), font ) );
		item->Name = _T( "Header" );
		item->MyText->setScale( .89f );

		MyMenu->Add( item );
		item->Selectable = false;
		pos.Y -= 1.35f * YSpacing;

		const std::wstring tempVector[] = { _T( "Yes" ), _T( "No" ) };
		std::vector<std::wstring> ItemString = std::vector<std::wstring>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		for ( int i = 0; i < 2; i++ )
		{
			item = std::make_shared<MenuItem>( std::make_shared<EzText>( ItemString[ i ], font ) );
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

		MyMenu->Items[ 1 ]->Name = _T( "Yes" );
		MyMenu->Items[ 1 ]->setGo( std::make_shared<SignInYesLambda>( this ) );

		MyMenu->Items[ 2 ]->Name = _T( "No" );
		MyMenu->Items[ 2 ]->setGo( std::make_shared<SignInNoLambda>( this ) );

		MyMenu->MyPieceQuadTemplate.reset();

		SetPos();
	}
#endif

#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN))
	void SignInMenu::SetPos()
	{
		std::shared_ptr<MenuItem> _item;
		_item = MyMenu->FindItemByName( _T( "Header" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -416.668f, 527.7777f ) );
			_item->MyText->setScale( 0.89f );
			_item->MySelectedText->setScale( 1 );
			_item->SelectIconOffset = Vector2( 0, 0 );
		}
		_item = MyMenu->FindItemByName( _T( "Yes" ) );
		if ( _item != 0 )
		{
			_item->setSetPos( Vector2( -108.333f, 149.4445f ) );
			_item->MyText->setScale( 0.775f );
			_item->MySelectedText->setScale( 0.775f );
			_item->SelectIconOffset = Vector2( -88.88965f, -130.3333f );
		}
		_item = MyMenu->FindItemByName( _T( "No" ) );
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
			Call( std::make_shared<SimpleMenu>( getControl(), MyCharacterSelect ) );
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

	void SignInMenu::InitializeInstanceFields()
	{
#if defined(NOT_PC) && (defined(XBOX) || defined(XBOX_SIGNIN)) && defined(XBOX) || defined(XBOX_SIGNIN)
		GamerGuideUp = false;
#endif
	}
}
