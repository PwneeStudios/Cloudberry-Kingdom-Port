#include <global_header.h>

#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	//JoinText::JoinText( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	JoinText::JoinText( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) { }
	boost::shared_ptr<JoinText> JoinText::JoinText_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();

#if defined(DEBUG)
		boost::shared_ptr<JoinText> This = boost::static_pointer_cast<JoinText>( shared_from_this() );
		if ( CloudberryKingdomGame::address == 0 )
		{
			CloudberryKingdomGame::address = reinterpret_cast<int>( This.px );
		}
		return This;
#else
		return boost::static_pointer_cast<JoinText>( shared_from_this() );
#endif
	}

	void JoinText::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void JoinText::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		// Press A to join
		int ButtonSize = 89;
		if  (Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
		{
			ButtonSize = 75;
		}
		else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
		{
			ButtonSize = 75;
		}
		else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
		{
			ButtonSize = 94;
		}

#ifdef PC_VERSION
		std::wstring pressa = Format( Localization::WordString( Localization::Words_PressToJoin ).c_str(), ButtonString::Go_Controller( ButtonSize ).c_str() );
#elif CAFE
		std::wstring pressa = Format( Localization::WordString( Localization::Words_PressToJoin_WiiU ).c_str(), ButtonString::Go( ButtonSize ).c_str() );
#else
        std::wstring pressa = Format( Localization::WordString( Localization::Words_PressToJoin ).c_str(), ButtonString::Go( ButtonSize ).c_str() );
#endif

		if  (Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
		{
			Text = boost::make_shared<EzText>( pressa, Resources::Font_Grobold42, 1000.0f, true, true, .5f );

			Text->setPos( Vector2( 11.11133f, 63.88889f ) ); Text->setScale( 0.9542501f );
		}
		else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
		{
			Text = boost::make_shared<EzText>( pressa, Resources::Font_Grobold42, 1000, true, true, .5f );

			Text->setPos( Vector2( 11.11133f, 63.88889f ) ); Text->setScale( 0.9542501f );
		}
		else
		{
			Text = boost::make_shared<EzText>( pressa, Resources::Font_Grobold42, true, true);

			Text->setScale( .7765f );
		}

		Text->ShadowOffset = Vector2( 7.5f, 7.5f );
		Text->ShadowColor = bColor( 30, 30, 30 );
		Text->ColorizePics = true;

		MyPile->Add( Text );

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );

		// SetPos
		if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
		{
			Text->setPos( Vector2( 0.f, 0.f ) );
			Text->setScale( 0.5720017f );
		}
		else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
		{
			Text->setPos( Vector2( 0.f, 0.f ) );
			Text->setScale( 0.570833f );
		}
		else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
		{
			Text->setPos( Vector2( 0.f, 0.f ) );
			Text->setScale( 0.575f );
		}
		else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
		{
			Text->setPos( Vector2( 0.f, 0.f ) );
			Text->setScale( 0.5195001f );
		}
	}

	void JoinText::ScaleGamerTag( const boost::shared_ptr<EzText> &GamerTag_Renamed )
	{
		GamerTag_Renamed->setScale( GamerTag_Renamed->getScale() * 850 / GamerTag_Renamed->GetWorldWidth() );

		float Height = GamerTag_Renamed->GetWorldHeight();
		float MaxHeight = 380;
		if ( Height > MaxHeight )
			GamerTag_Renamed->setScale( GamerTag_Renamed->getScale() * MaxHeight / Height );
	}

	void JoinText::SetGamerTag()
	{
		Tools::StartGUIDraw();
		if ( MyCharacterSelect->getPlayer()->Exists )
		{
			std::wstring name = MyCharacterSelect->getPlayer()->GetName();
			Text = boost::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
			ScaleGamerTag( Text );
		}
		else
		{
			Text = boost::make_shared<EzText>( std::wstring( L"ERROR" ), Resources::LilFont, true, true );
		}

		Text->Shadow = false;
		Text->PicShadow = false;

		Tools::EndGUIDraw();
	}

    void JoinText::MyDraw()
    {
        if ( CharacterSelectManager::FakeHide )
            return;

        CkBaseMenu::MyDraw();
    }

	void JoinText::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_BEGINNING;
		MyCharacterSelect->MyDoll->ShowBob = false;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = false;
		MyCharacterSelect->getPlayer()->Exists = false;

		// Use this if statement if you want keyboard to control all characters (For debugging)
		//if (ButtonCheck.State(ControllerButtons.A, -2).Pressed)

		if ( ButtonCheck::State( ControllerButtons_A, getControl() ).Pressed )
		{
	#if defined(XBOX) || defined(XBOX_SIGNIN)
			if ( MyCharacterSelect->getPlayer()->getMyGamer() != 0 )
				Call( MakeMagic( SimpleMenu, ( getControl(), MyCharacterSelect ) ) );
			else
				Call( MakeMagic( SignInMenu, ( getControl(), MyCharacterSelect ) ) );
	#else
			GUI_Panel::Call( MakeMagic( SimpleMenu, ( getControl(), MyCharacterSelect ) ) );
	#endif
			Hide();
		}
	}
}
