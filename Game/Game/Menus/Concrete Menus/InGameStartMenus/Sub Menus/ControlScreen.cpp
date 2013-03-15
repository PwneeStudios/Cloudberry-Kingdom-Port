#include <global_header.h>

namespace CloudberryKingdom
{

	ControlScreen::ControlScreen( int Control ) : CkBaseMenu( false ) { }
	boost::shared_ptr<ControlScreen> ControlScreen::ControlScreen_Construct( int Control )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		EnableBounce();

		this->setControl( Control );

		Constructor();

		return boost::static_pointer_cast<ControlScreen>( shared_from_this() );
	}

#if defined(PC_VERSION)
	boost::shared_ptr<QuadClass> ControlScreen::MakeQuad( Keys key )
	{
		boost::shared_ptr<QuadClass> quad = boost::make_shared<QuadClass>( ButtonString::KeyToTexture( key ), 90.f );
		MyPile->Add( quad );
		quad->Quad_Renamed.SetColor( CustomControlsMenu::SecondaryKeyColor );
		return quad;
	}
#endif

	void ControlScreen::Init()
	{
		 CkBaseMenu::Init();

		setPauseGame( true );

		SlideInFrom = SlideOutTo = PresetPos_LEFT;

		//ReturnToCallerDelay = SlideLength = 0;
		setSlideLength( 23 );
		DestinationScale *= 1.02f;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		boost::shared_ptr<QuadClass> Backdrop;
        if (UseSimpleBackdrop)
            Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Arcade_BoxLeft" ), 1500.f, true );
        else		
			Backdrop = boost::make_shared<QuadClass>( std::wstring( L"Backplate_1230x740" ), 1500.f, true );
		Backdrop->Name = std::wstring( L"Backdrop" );
		MyPile->Add( Backdrop );

		if ( !UseSimpleBackdrop )
		{
			EpilepsySafe( .9f );
		}

		ReturnToCallerDelay = 7;

		boost::shared_ptr<EzText> text;

#if defined(PC_VERSION)
		text = boost::make_shared<EzText>( Localization::Words_QuickSpawn, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"quickspawn" ) );
		text->MyFloatColor = ColorHelper::Gray( .955f );

		text = boost::make_shared<EzText>( Localization::Words_PowerUpMenu, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"powerups" ) );
		text->MyFloatColor = ColorHelper::Gray( .955f );

		text = boost::make_shared<EzText>( Localization::Words_Menu, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"menu" ) );
		text->MyFloatColor = CampaignHelper::DifficultyColor[ 1 ].ToVector4();

		text = boost::make_shared<EzText>( Localization::Words_Accept, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"accept" ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedNextColor;
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedNextColor;

		text = boost::make_shared<EzText>( Localization::Words_Back, Resources::Font_Grobold42 );
		MyPile->Add( text, std::wstring( L"back" ) );
		text->MyFloatColor = Menu::DefaultMenuInfo::SelectedBackColor;
		text->MyFloatColor = Menu::DefaultMenuInfo::UnselectedBackColor;

		text = boost::make_shared<EzText>( std::wstring( L"b" ), Resources::Font_Grobold42 );
		text->SubstituteText( std::wstring( L"<" ) );
		MyPile->Add( text, std::wstring( L"split" ) );

		boost::shared_ptr<QuadClass> q;

		q = boost::make_shared<QuadClass>( std::wstring( L"Enter_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"enter" ) );

		q = boost::make_shared<QuadClass>( std::wstring( L"Esc_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"esc" ) );

		q = boost::make_shared<QuadClass>( std::wstring( L"Backspace_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"backspace" ) );

		q = boost::make_shared<QuadClass>( std::wstring( L"Space_Key" ) );
		q->ScaleXToMatchRatio( 130 );
		MyPile->Add( q, std::wstring( L"space" ) );

		SetPos();
#else
        text = boost::make_shared<EzText>( L"+", Resources::Font_Grobold42, true);
        MyPile->Add(text, L"plus");
        text->MyFloatColor = ColorHelper::Gray(.955f);
		bool center = false;

        text = boost::make_shared<EzText>(Localization::Words_QuickSpawn, Resources::Font_Grobold42, center);
        MyPile->Add(text, L"quickspawn");
        text->MyFloatColor = ColorHelper::Gray(.955f);

        text = boost::make_shared<EzText>(Localization::Words_Jump, Resources::Font_Grobold42, center);
        MyPile->Add(text, L"jump");
        text->MyFloatColor = ColorHelper::Gray(.955f);

        text = boost::make_shared<EzText>(Localization::Words_PowerUpMenu, Resources::Font_Grobold42, center);
        MyPile->Add(text, L"powerups");
        text->MyFloatColor = ColorHelper::Gray(.955f);

        text = boost::make_shared<EzText>(Localization::Words_Accept, Resources::Font_Grobold42, center);
        MyPile->Add(text, L"accept");

        text = boost::make_shared<EzText>(Localization::Words_Back, Resources::Font_Grobold42, center);
        MyPile->Add(text, L"back");

        boost::shared_ptr<QuadClass> q;

#ifdef CAFE
		if ( !ButtonTexture::UseGamepad )
			q = boost::make_shared<QuadClass>( ButtonTexture::getBack() );
		else
#endif
			q = boost::make_shared<QuadClass>( ButtonTexture::getX() );
		q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"x");

        q = boost::make_shared<QuadClass>( L"door_castle_1" ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"door");

        q = boost::make_shared<QuadClass>( L"door_cave_1" ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"door_cave");

        q = boost::make_shared<QuadClass>( L"door_cloud_1" ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"door_cloud");

        q = boost::make_shared<QuadClass>( L"door_forest_1" ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"door_forest");

        q = boost::make_shared<QuadClass>(ButtonTexture::getY() ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"y");

        q = boost::make_shared<QuadClass>(ButtonTexture::getLeftBumper() ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"lb");
        q = boost::make_shared<QuadClass>(ButtonTexture::getRightBumper() ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"rb");


        q = boost::make_shared<QuadClass>(ButtonTexture::getGo() ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"jump");

        q = boost::make_shared<QuadClass>(ButtonTexture::getGo() ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"accep");

        q = boost::make_shared<QuadClass>(ButtonTexture::getBack() ); q->ScaleXToMatchRatio(130);
        MyPile->Add(q, L"back");

        SetPos();
#endif
	}


#ifdef PC_VERSION
        void ControlScreen::SetPos()
        {
            boost::shared_ptr<EzText> _t;
            _t = MyPile->FindEzText( L"quickspawn" ); if (_t != 0 ) { _t->setPos( Vector2(-288.0965f, 435.3178f ) ); _t->setScale( 1.06f ); }
            _t = MyPile->FindEzText( L"powerups" ); if (_t != 0 ) { _t->setPos( Vector2(-267.0644f, 133.7302f ) ); _t->setScale( 1.06f ); }
            _t = MyPile->FindEzText( L"menu" ); if (_t != 0 ) { _t->setPos( Vector2(-280.1582f, 731.7462f ) ); _t->setScale( 1.06f ); }
            _t = MyPile->FindEzText( L"accept" ); if (_t != 0 ) { _t->setPos( Vector2(-286.109f, -156.3493f ) ); _t->setScale( 1.06f ); }
            _t = MyPile->FindEzText( L"back" ); if (_t != 0 ) { _t->setPos( Vector2(-264.2847f, -432.5391f ) ); _t->setScale( 1.06f ); }
            _t = MyPile->FindEzText( L"split" ); if (_t != 0 ) { _t->setPos( Vector2(-536.5085f, 14.28584f ) ); _t->setScale( 1.46f ); }

            boost::shared_ptr<QuadClass> _q;
            _q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1500.f, 902.2556f ) ); }
            _q = MyPile->FindQuad( L"enter" ); if (_q != 0 ) { _q->setPos( Vector2(-771.4287f, -234.9209f ) ); _q->setSize( Vector2( 271.0638f, 130.f ) ); }
            _q = MyPile->FindQuad( L"esc" ); if (_q != 0 ) { _q->setPos( Vector2(-638.8887f, 520.2384f ) ); _q->setSize( Vector2( 138.2979f, 130.f ) ); }
            _q = MyPile->FindQuad( L"backspace" ); if (_q != 0 ) { _q->setPos( Vector2(-773.8103f, -603.5712f ) ); _q->setSize( Vector2( 271.0638f, 130.f ) ); }
            _q = MyPile->FindQuad( L"space" ); if (_q != 0 ) { _q->setPos( Vector2(-768.6523f, 205.9521f ) ); _q->setSize( Vector2( 271.0638f, 130.f ) ); }

            MyPile->setPos( Vector2( 0.f, 0.f ) );
        }
#else
        void ControlScreen::SetPos()
        {
#ifdef CAFE
			if ( !ButtonTexture::UseGamepad )
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"plus" ); if (_t != 0 ) { _t->setPos( Vector2(-777.7777f, -2455.555f ) ); _t->setScale( 0.5140832f ); }
				_t = MyPile->FindEzText( L"quickspawn" ); if (_t != 0 ) { _t->setPos( Vector2(-305.5554f, -2384.126f ) ); _t->setScale( 0.7971667f ); }
				_t = MyPile->FindEzText( L"jump" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 824.9998f ) ); _t->setScale( 0.7969999f ); }
				_t = MyPile->FindEzText( L"powerups" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 512.3021f ) ); _t->setScale( 0.7926666f ); }
				_t = MyPile->FindEzText( L"accept" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 180.9535f ) ); _t->setScale( 0.7982503f ); }
				_t = MyPile->FindEzText( L"back" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, -136.5063f ) ); _t->setScale( 0.7832497f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1500.f, 902.2556f ) ); }
				_q = MyPile->FindQuad( L"x" ); if (_q != 0 ) { _q->setPos( Vector2(-908.3336f, -630.5556f ) ); _q->setSize( Vector2( 91.58332f, 91.58332f ) ); }
				_q = MyPile->FindQuad( L"door" ); if (_q != 0 ) { _q->setPos( Vector2(-205.5555f, -630.5555f ) ); _q->setSize( Vector2( 177.7416f, 126.6664f ) ); }
				_q = MyPile->FindQuad( L"door_cave" ); if (_q != 0 ) { _q->setPos( Vector2( 225.f, -622.2222f ) ); _q->setSize( Vector2( 183.0986f, 130.f ) ); }
				_q = MyPile->FindQuad( L"door_cloud" ); if (_q != 0 ) { _q->setPos( Vector2( 600.f, -630.5555f ) ); _q->setSize( Vector2( 155.f, 130.f ) ); }
				_q = MyPile->FindQuad( L"door_forest" ); if (_q != 0 ) { _q->setPos( Vector2( 969.4446f, -619.4445f ) ); _q->setSize( Vector2( 164.4898f, 130.f ) ); }
				_q = MyPile->FindQuad( L"y" ); if (_q != 0 ) { _q->setPos( Vector2(-913.8889f, 344.4442f ) ); _q->setSize( Vector2( 97.74995f, 97.74995f ) ); }
				_q = MyPile->FindQuad( L"lb" ); if (_q != 0 ) { _q->setPos( Vector2(-1005.556f, -2541.666f ) ); _q->setSize( Vector2( 175.4162f, 175.4162f ) ); }
				_q = MyPile->FindQuad( L"rb" ); if (_q != 0 ) { _q->setPos( Vector2(-563.889f, -2527.778f ) ); _q->setSize( Vector2( 179.2496f, 179.2496f ) ); }
				_q = MyPile->FindQuad( L"jump" ); if (_q != 0 ) { _q->setPos( Vector2(-922.222f, 661.1106f ) ); _q->setSize( Vector2( 102.0832f, 102.0832f ) ); }
				_q = MyPile->FindQuad( L"accep" ); if (_q != 0 ) { _q->setPos( Vector2(-913.8892f, 11.11126f ) ); _q->setSize( Vector2( 99.49992f, 99.49992f ) ); }
				_q = MyPile->FindQuad( L"back" ); if (_q != 0 ) { _q->setPos( Vector2(-913.889f, -308.3336f ) ); _q->setSize( Vector2( 95.41663f, 95.41663f ) ); }

				MyPile->setPos( Vector2( 0.f, 0.f ) );
			}
			else
#endif
			{
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"plus" ); if (_t != 0 ) { _t->setPos( Vector2(-911.1111f, 500.f ) ); _t->setScale( 0.5140832f ); }
				_t = MyPile->FindEzText( L"quickspawn" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 571.4288f ) ); _t->setScale( 0.7971667f ); }
				_t = MyPile->FindEzText( L"jump" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 824.9998f ) ); _t->setScale( 0.7969999f ); }
				_t = MyPile->FindEzText( L"powerups" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 317.8578f ) ); _t->setScale( 0.7926666f ); }
				_t = MyPile->FindEzText( L"accept" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, 64.28687f ) ); _t->setScale( 0.7982503f ); }
				_t = MyPile->FindEzText( L"back" ); if (_t != 0 ) { _t->setPos( Vector2(-438.8888f, -189.2841f ) ); _t->setScale( 0.7832497f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1500.f, 902.2556f ) ); }
				_q = MyPile->FindQuad( L"x" ); if (_q != 0 ) { _q->setPos( Vector2(-908.3336f, -630.5556f ) ); _q->setSize( Vector2( 91.58332f, 91.58332f ) ); }
				_q = MyPile->FindQuad( L"door" ); if (_q != 0 ) { _q->setPos( Vector2(-205.5555f, -630.5555f ) ); _q->setSize( Vector2( 177.7416f, 126.6664f ) ); }
				_q = MyPile->FindQuad( L"door_cave" ); if (_q != 0 ) { _q->setPos( Vector2( 225.f, -622.2222f ) ); _q->setSize( Vector2( 183.0986f, 130.f ) ); }
				_q = MyPile->FindQuad( L"door_cloud" ); if (_q != 0 ) { _q->setPos( Vector2( 600.f, -630.5555f ) ); _q->setSize( Vector2( 155.f, 130.f ) ); }
				_q = MyPile->FindQuad( L"door_forest" ); if (_q != 0 ) { _q->setPos( Vector2( 969.4446f, -619.4445f ) ); _q->setSize( Vector2( 164.4898f, 130.f ) ); }
				_q = MyPile->FindQuad( L"y" ); if (_q != 0 ) { _q->setPos( Vector2(-913.8889f, 149.9999f ) ); _q->setSize( Vector2( 97.74995f, 97.74995f ) ); }
				_q = MyPile->FindQuad( L"lb" ); if (_q != 0 ) { _q->setPos( Vector2(-1138.889f, 411.0f ) ); _q->setSize( Vector2( 175.4162f, 175.4162f ) ); }
				_q = MyPile->FindQuad( L"rb" ); if (_q != 0 ) { _q->setPos( Vector2(-697.2224f, 411.0f ) ); _q->setSize( Vector2( 179.2496f, 179.2496f ) ); }
				_q = MyPile->FindQuad( L"jump" ); if (_q != 0 ) { _q->setPos( Vector2(-922.222f, 661.1106f ) ); _q->setSize( Vector2( 102.0832f, 102.0832f ) ); }
				_q = MyPile->FindQuad( L"accep" ); if (_q != 0 ) { _q->setPos( Vector2(-913.8892f, -105.5554f ) ); _q->setSize( Vector2( 99.49992f, 99.49992f ) ); }
				_q = MyPile->FindQuad( L"back" ); if (_q != 0 ) { _q->setPos( Vector2(-913.889f, -355.5558f ) ); _q->setSize( Vector2( 95.41663f, 95.41663f ) ); }

				MyPile->setPos( Vector2( 0.f, 0.f ) );
			}
        }
#endif

	void ControlScreen::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed || ButtonCheck::State( ControllerButtons_B, -1 ).Pressed )
		{
			Active = false;
			ReturnToCaller();
		}
	}
}
