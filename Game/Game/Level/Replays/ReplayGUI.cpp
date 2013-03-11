#include <global_header.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

namespace CloudberryKingdom
{

	void ReplayGUI::ReturnToCaller()
	{
		InGameStartMenu::PreventMenu = false;
		CkBaseMenu::ReturnToCaller();
	}

	ReplayGUI::ReplayGUI()
	{
		InitializeInstanceFields();
	}

	boost::shared_ptr<ReplayGUI> ReplayGUI::ReplayGUI_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<ReplayGUI>( shared_from_this() );
	}

	void ReplayGUI::SetGrayHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		CkBaseMenu::SetHeaderProperties( text );

		text->Shadow = false;

		text->setScale( FontScale );
		MyPile->Add( text );
	}

	void ReplayGUI::SetHeaderProperties( const boost::shared_ptr<EzText> &text )
	{
		text->setScale( FontScale );
		MyPile->Add( text );
	}

	void ReplayGUI::Init()
	{
		CkBaseMenu::Init();

		SlideInFrom = SlideOutTo = PresetPos_BOTTOM;
		//SlideOutLength = 0;
	}

	void ReplayGUI::OnAdd()
	{
		CkBaseMenu::OnAdd();

		InGameStartMenu::PreventMenu = true;

		FontScale = .5f;

		MyPile = boost::make_shared<DrawPile>();

		// Backrop
		boost::shared_ptr<QuadClass> backdrop2 = boost::make_shared<QuadClass>( std::wstring( L"White" ), 1500.f );
		backdrop2->Quad_Renamed.SetColor( ColorHelper::GrayColor( .1f ) );
		backdrop2->setAlpha( .45f );
		MyPile->Add( backdrop2, std::wstring( L"Backdrop2" ) );

		boost::shared_ptr<QuadClass> backdrop = boost::make_shared<QuadClass>( std::wstring( L"White" ), 1500.f );
		backdrop->Quad_Renamed.SetColor( ColorHelper::GrayColor( .25f ) );
		backdrop->setAlpha( .35f );
		MyPile->Add( backdrop, std::wstring( L"Backdrop" ) );

		Vector2 AdditionalAdd = Vector2();
	#if defined(PC_VERSION)
		AdditionalAdd = Vector2( -2, 0 );
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getGo(), 140.f, static_cast<std::wstring>( std::wstring( L"Button_Go" ) ) ) );
		Play = boost::make_shared<EzText>( Localization::Words_Play, ItemFont, true );
		Play->Name = std::wstring( L"Play" );
		SetGrayHeaderProperties( Play );
	#else
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getGo(), 90.f, std::wstring( L"Button_Go" ) ) );
		Play = boost::make_shared<EzText>( Localization::Words_Play, ItemFont, true );
		//Play->MyFloatColor = ( Color( static_cast<unsigned char>( 67 ), static_cast<unsigned char>( 198 ), static_cast<unsigned char>( 48 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		Play->Name = std::wstring( L"Play" );
		//SetHeaderProperties( Play );
		SetGrayHeaderProperties( Play );
	#endif


	Localization::Words back_word = Localization::Words_Done;
	if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
		back_word = Localization::Words_Back;

	#if defined(PC_VERSION)
		AdditionalAdd = Vector2( -2, 0 );
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 140.f, static_cast<std::wstring>( std::wstring( L"Button_Back" ) ) ) );
		End = boost::make_shared<EzText>( back_word, ItemFont, true );
		End->Name = std::wstring( L"Back" );
		SetGrayHeaderProperties( End );
	#else
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 85.f, static_cast<std::wstring>( std::wstring( L"Button_Back" ) ) ) );
		End = boost::make_shared<EzText>( back_word, ItemFont, true );
		//End->MyFloatColor = ( Color( static_cast<unsigned char>( 239 ), static_cast<unsigned char>( 41 ), static_cast<unsigned char>( 41 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		End->Name = std::wstring( L"Back" );
		//SetHeaderProperties( End );
		SetGrayHeaderProperties( End );
	#endif

		if ( Type == ReplayGUIType_REPLAY )
		{
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, static_cast<std::wstring>( std::wstring( L"Button_X" ) ) ) );
			Toggle = boost::make_shared<EzText>( Localization::Words_Single, ItemFont, true );
			Toggle->Name = std::wstring( L"Toggle" );
	#if defined(PC_VERSION)
			SetGrayHeaderProperties( Toggle );
	#else
			//SetHeaderProperties( Toggle );
			//Toggle->MyFloatColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
			//Toggle->MyFloatColor = Menu::DefaultMenuInfo::UnselectedXColor;
			SetGrayHeaderProperties( Toggle );
	#endif
			SetToggleText();
		}

		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getLeftRight(), 85.f, static_cast<std::wstring>( std::wstring( L"Button_LR" ) ) ) );
		Speed = boost::make_shared<EzText>( Localization::Words_Speed, ItemFont );
		Speed->Name = std::wstring( L"Speed" );
		SetGrayHeaderProperties( Speed );

		if ( Type == ReplayGUIType_COMPUTER )
		{
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getLeftBumper(), 85.f, static_cast<std::wstring>( std::wstring( L"Button_LB" ) ) ) );
			LB = boost::make_shared<EzText>( Localization::Words_Reset, ItemFont, true );
			LB->Name = std::wstring( L"Reset" );
			SetGrayHeaderProperties( LB );
		}
		else
		{
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getLeftBumper(), 85.f, static_cast<std::wstring>( std::wstring( L"Button_LB" ) ) ) );
			LB = boost::make_shared<EzText>( Localization::Words_Previous, ItemFont, true );
			LB->Name = std::wstring( L"Prev" );
			SetGrayHeaderProperties( LB );

			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getRightBumper(), 85.f, static_cast<std::wstring>( std::wstring( L"Button_RB" ) ) ) );
			RB = boost::make_shared<EzText>( Localization::Words_Next, ItemFont, true );
			RB->Name = std::wstring( L"Next" );
			SetGrayHeaderProperties( RB );
		}
		SetSpeed();

		BigPaused = boost::make_shared<QuadClass>();
		BigPaused->SetToDefault();
		BigPaused->Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"Paused" ) ) );
		BigPaused->ScaleYToMatchRatio( 355 );
		MyPile->Add( BigPaused );
		BigPaused->setPos( Vector2( 1210.557f, 791.1111f ) );

		BigEnd = boost::make_shared<QuadClass>();
		BigEnd->SetToDefault();
		BigEnd->Quad_Renamed.setMyTexture( Tools::TextureWad->FindByName( std::wstring( L"End" ) ) );
		BigEnd->ScaleYToMatchRatio( 255 );
		//BigPaused->ScaleYToMatchRatio( 300 );
		MyPile->Add( BigEnd );
		BigEnd->setPos( Vector2( 1277.222f, 774.4444f ) );

		SetPlayText();



			// SetPos()
			if ( Type == ReplayGUIType_COMPUTER )
			{
				if ( ButtonCheck::ControllerInUse )
				{
					////////////////////////////////////////////////////////////////////////////////
					/////// Console version, computer replay ////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////
					if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-779.512f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-239.4449f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 147.3335f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 946.f, -840.5555f ) ); _t->setScale( 0.3969166f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1038.89f, -911.1113f ) ); _q->setSize( Vector2( 69.64276f, 69.64276f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-508.3335f, -911.1113f ) ); _q->setSize( Vector2( 71.76664f, 71.76664f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 63.88873f, -911.1113f ) ); _q->setSize( Vector2( 83.48316f, 83.48316f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 499.9998f, -911.1113f ) ); _q->setSize( Vector2( 152.0833f, 152.0833f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-837.8453f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-258.8895f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 136.2224f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 932.1111f, -840.5555f ) ); _t->setScale( 0.3969166f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1038.89f, -911.1113f ) ); _q->setSize( Vector2( 69.64276f, 69.64276f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-508.3335f, -911.1113f ) ); _q->setSize( Vector2( 71.76664f, 71.76664f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 63.88873f, -911.1113f ) ); _q->setSize( Vector2( 83.48316f, 83.48316f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 499.9998f, -911.1113f ) ); _q->setSize( Vector2( 152.0833f, 152.0833f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-693.4005f, -810.0001f ) ); _t->setScale( 0.5253334f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-92.22247f, -810.0001f ) ); _t->setScale( 0.5253334f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 264.0002f, -815.5556f ) ); _t->setScale( 0.4885834f ); }
						_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 971.0002f, -815.5556f ) ); _t->setScale( 0.5030003f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5562f, -911.1113f ) ); _q->setSize( Vector2( 69.64276f, 69.64276f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-347.2227f, -911.1113f ) ); _q->setSize( Vector2( 71.76664f, 71.76664f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 186.1109f, -911.1113f ) ); _q->setSize( Vector2( 83.48316f, 83.48316f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 655.555f, -911.1113f ) ); _q->setSize( Vector2( 152.0833f, 152.0833f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-721.1783f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-120.0003f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 264.0002f, -832.2222f ) ); _t->setScale( 0.44f ); }
						_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 948.7776f, -837.7778f ) ); _t->setScale( 0.4176667f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5562f, -911.1113f ) ); _q->setSize( Vector2( 69.64276f, 69.64276f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-347.2227f, -911.1113f ) ); _q->setSize( Vector2( 71.76664f, 71.76664f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 186.1109f, -911.1113f ) ); _q->setSize( Vector2( 83.48316f, 83.48316f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 655.555f, -911.1113f ) ); _q->setSize( Vector2( 152.0833f, 152.0833f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
				}
				else
				{
					////////////////////////////////////////////////////////////////////////////////
					/////// PC version, compuer replay /////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////

					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-662.845f, -832.2222f ) ); _t->setScale( 0.44f ); }
					_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-103.3335f, -835.0001f ) ); _t->setScale( 0.44f ); }
					_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 344.5559f, -832.2222f ) ); _t->setScale( 0.44f ); }
					_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 1051.556f, -840.5555f ) ); _t->setScale( 0.44f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
					_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5562f, -911.1113f ) ); _q->setSize( Vector2( 130.9643f, 62.80939f ) ); }
					_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-325.0003f, -911.1112f ) ); _q->setSize( Vector2( 73.5106f, 69.09996f ) ); }
					_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 244.4444f, -913.8889f ) ); _q->setSize( Vector2( 73.20911f, 68.81656f ) ); }
					_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 783.3331f, -913.8888f ) ); _q->setSize( Vector2( 76.22305f, 71.64967f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
			}
			else
			{
				if ( ButtonCheck::ControllerInUse )
				{
					////////////////////////////////////////////////////////////////////////////////
					/////// Console version, player replay /////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////
					if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_SPANISH )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1069.445f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-563.889f, -827.778f ) ); _t->setScale( 0.4147499f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-77.77845f, -827.778f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 274.9997f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 830.5556f, -836.1113f ) ); _t->setScale( 0.3769997f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1399.998f, -836.1113f ) ); _t->setScale( 0.3787504f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1269.445f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-772.2219f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-313.8887f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 222.2214f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 575.0005f, -905.5554f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1091.667f, -902.7777f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_FRENCH )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1097.222f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-625.0001f, -827.778f ) ); _t->setScale( 0.4147499f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-216.6671f, -827.778f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 122.2222f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 772.2219f, -847.2224f ) ); _t->setScale( 0.3271667f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1405.553f, -841.6669f ) ); _t->setScale( 0.3494168f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1272.223f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-786.1104f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-405.5551f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55546f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 469.4445f, -908.3332f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1141.667f, -905.5555f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_ITALIAN )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1097.222f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-652.778f, -827.778f ) ); _t->setScale( 0.4147499f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-166.6671f, -827.778f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 197.2224f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 811.111f, -847.2224f ) ); _t->setScale( 0.3271667f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1411.109f, -841.6669f ) ); _t->setScale( 0.3494168f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1305.556f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-852.7772f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-416.666f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 133.3333f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 500.f, -908.3332f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1138.89f, -905.5555f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_RUSSIAN )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1305.556f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-824.9996f, -827.778f ) ); _t->setScale( 0.4147499f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-261.1112f, -827.778f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 113.8889f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 766.667f, -847.2224f ) ); _t->setScale( 0.304f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1469.442f, -841.6669f ) ); _t->setScale( 0.3178333f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77763f, -2327.78f ) ); _q->setSize( Vector2( 1691.408f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 27.77833f, -2330.556f ) ); _q->setSize( Vector2( 1670.826f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1538.889f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-1055.555f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-572.2219f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 63.88873f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 380.5562f, -908.3332f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1155.556f, -905.5555f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_GERMAN )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1086.111f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-563.8888f, -827.778f ) ); _t->setScale( 0.4147499f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-80.55579f, -827.778f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 261.1111f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 869.4445f, -847.2224f ) ); _t->setScale( 0.3271667f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1430.553f, -841.6669f ) ); _t->setScale( 0.3494168f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1275.f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-791.6664f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-308.333f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 183.3333f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 569.4448f, -908.3332f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1183.334f, -905.5555f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_CHINESE )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1050.f, -819.4447f ) ); _t->setScale( 0.4576671f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-586.1115f, -816.6666f ) ); _t->setScale( 0.4578336f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-133.3344f, -819.4445f ) ); _t->setScale( 0.4533335f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 169.4441f, -830.5552f ) ); _t->setScale( 0.3993336f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 850.0007f, -827.7777f ) ); _t->setScale( 0.4095834f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1391.665f, -824.9999f ) ); _t->setScale( 0.4487502f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1200.f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-777.7773f, -905.5554f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-333.3335f, -908.3333f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 113.8885f, -902.7777f ) ); _q->setSize( Vector2( 72.98328f, 72.98328f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 552.7781f, -908.3331f ) ); _q->setSize( Vector2( 121.4832f, 121.4832f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1166.667f, -908.3333f ) ); _q->setSize( Vector2( 120.8164f, 120.8164f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_KOREAN )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-986.1114f, -811.1114f ) ); _t->setScale( 0.4778334f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-513.8888f, -813.8892f ) ); _t->setScale( 0.4779999f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-41.66737f, -813.8892f ) ); _t->setScale( 0.4771666f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 291.6665f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 897.2226f, -816.6669f ) ); _t->setScale( 0.4539167f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1372.221f, -819.4447f ) ); _t->setScale( 0.4569168f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1213.889f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-711.1108f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-233.333f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 230.5552f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 675.0005f, -908.3332f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1155.556f, -905.5555f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_JAPANESE )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-991.6671f, -827.778f ) ); _t->setScale( 0.4328336f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-530.5558f, -824.9999f ) ); _t->setScale( 0.4330001f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-52.77869f, -827.7778f ) ); _t->setScale( 0.4285f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 333.333f, -838.8885f ) ); _t->setScale( 0.3993336f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 886.1116f, -827.7777f ) ); _t->setScale( 0.4390835f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1369.443f, -824.9999f ) ); _t->setScale( 0.4487502f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1200.f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-730.5552f, -905.5554f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-300.f, -908.3333f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 261.1111f, -902.7777f ) ); _q->setSize( Vector2( 72.98328f, 72.98328f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 661.1114f, -908.3331f ) ); _q->setSize( Vector2( 121.4832f, 121.4832f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1155.556f, -908.3333f ) ); _q->setSize( Vector2( 120.8164f, 120.8164f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
					else if ( Localization::CurrentLanguage->MyLanguage == Localization::Language_PORTUGUESE )
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-991.6671f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-497.2223f, -830.5555f ) ); _t->setScale( 0.4136664f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2(-0.000617981f, -833.3333f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 352.7771f, -836.1108f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 883.333f, -836.111f ) ); _t->setScale( 0.3584168f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1422.221f, -838.8887f ) ); _t->setScale( 0.354f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 144.4434f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 141.6667f, -2327.778f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1200.f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-722.2222f, -911.111f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-230.5555f, -911.111f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 274.9993f, -899.9999f ) ); _q->setSize( Vector2( 79.48331f, 79.48331f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 641.6671f, -905.5554f ) ); _q->setSize( Vector2( 126.1499f, 126.1499f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1138.889f, -900.f ) ); _q->setSize( Vector2( 128.233f, 128.233f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1307.777f, 779.9999f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1321.666f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2(-55.55542f, 0.f ) );
					}
					else
					{
						boost::shared_ptr<EzText> _t;
						_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-1013.889f, -827.778f ) ); _t->setScale( 0.4145834f ); }
						_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-488.8888f, -827.778f ) ); _t->setScale( 0.4147499f ); }
						_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2( 2.777214f, -827.778f ) ); _t->setScale( 0.4139166f ); }
						_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 355.5554f, -827.778f ) ); _t->setScale( 0.3873335f ); }
						_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 900.0002f, -827.778f ) ); _t->setScale( 0.4208333f ); }
						_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1380.554f, -827.778f ) ); _t->setScale( 0.4238334f ); }

						boost::shared_ptr<QuadClass> _q;
						_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
						_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
						_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1213.889f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
						_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-711.1108f, -905.5555f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
						_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-233.333f, -905.5555f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
						_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 294.4441f, -902.7777f ) ); _q->setSize( Vector2( 79.56668f, 79.56668f ) ); }
						_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 675.0005f, -908.3332f ) ); _q->setSize( Vector2( 116.8998f, 116.8998f ) ); }
						_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1155.556f, -905.5555f ) ); _q->setSize( Vector2( 113.7331f, 113.7331f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }
						_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

						MyPile->setPos( Vector2( 0.f, 0.f ) );
					}
				}
				else
				{
					////////////////////////////////////////////////////////////////////////////////
					/////// PC version, player replay //////////////////////////////////////////////
					////////////////////////////////////////////////////////////////////////////////
					boost::shared_ptr<EzText> _t;
					_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-991.6671f, -827.778f ) ); _t->setScale( 0.4145834f ); }
					_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-472.2223f, -838.8888f ) ); _t->setScale( 0.4147499f ); }
					_t = MyPile->FindEzText( L"Toggle" ); if (_t != 0 ) { _t->setPos( Vector2( 11.11071f, -836.1111f ) ); _t->setScale( 0.4139166f ); }
					_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 436.1108f, -836.1108f ) ); _t->setScale( 0.3873335f ); }
					_t = MyPile->FindEzText( L"Prev" ); if (_t != 0 ) { _t->setPos( Vector2( 941.667f, -830.5555f ) ); _t->setScale( 0.4208333f ); }
					_t = MyPile->FindEzText( L"Next" ); if (_t != 0 ) { _t->setPos( Vector2( 1361.11f, -833.3332f ) ); _t->setScale( 0.4238334f ); }

					boost::shared_ptr<QuadClass> _q;
					_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3328f, -2327.78f ) ); _q->setSize( Vector2( 1517.832f, 1517.832f ) ); }
					_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 108.3335f, -2330.556f ) ); _q->setSize( Vector2( 1500.f, 1500.f ) ); }
					_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1244.444f, -908.3333f ) ); _q->setSize( Vector2( 116.7162f, 55.97613f ) ); }
					_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-688.8887f, -911.111f ) ); _q->setSize( Vector2( 66.06374f, 62.09991f ) ); }
					_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-213.8887f, -908.3332f ) ); _q->setSize( Vector2( 64.18431f, 60.33325f ) ); }
					_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 352.7776f, -905.5555f ) ); _q->setSize( Vector2( 69.04251f, 64.89996f ) ); }
					_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 727.7779f, -902.7776f ) ); _q->setSize( Vector2( 63.90063f, 60.0666f ) ); }
					_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1155.556f, -902.7778f ) ); _q->setSize( Vector2( 64.96447f, 61.0666f ) ); }

					MyPile->setPos( Vector2( 0.f, 0.f ) );
				}
			}


			// Extra push up
			float MoveUp = 28 * CloudberryKingdomGame::GuiSqueeze;
			Vector2 MoveUp_Back = Vector2( 0, 10 ) * CloudberryKingdomGame::GuiSqueeze;

			MyPile->setPos( Vector2( MyPile->getPos().X, MyPile->getPos().Y + MoveUp ) );
			boost::shared_ptr<QuadClass> __q;
			__q = MyPile->FindQuad( L"Backdrop2" ); if (__q != 0 ) { __q->setPos( __q->getPos() + MoveUp_Back ); }
			__q = MyPile->FindQuad( L"Backdrop" ); if (__q != 0 ) { __q->setPos( __q->getPos() + MoveUp_Back) ; }
	}

	void ReplayGUI::StartUp()
	{
		SkipPhsxStep = true;
	}

	void ReplayGUI::ResetReplay( const boost::shared_ptr<Level> &level )
	{
		if ( Type == ReplayGUIType_REPLAY )
			level->SetReplay();

		level->setSetToReset( true );
		level->ReplayPaused = false;
		level->FreeReset = true;
	}

	void ReplayGUI::SetToggleText()
	{
		if ( MyGame->MyLevel->SingleOnly )
			Toggle->SubstituteText( Localization::Words_All );
		else
			Toggle->SubstituteText( Localization::Words_Single );
	}

	void ReplayGUI::SetPlayText()
	{
		if ( StepControl )
			Play->SubstituteText( Localization::Words_Step );
		else
		{
			if ( PauseSelected )
				Play->SubstituteText( Localization::Words_Play );
			else
				Play->SubstituteText( Localization::Words_Pause );
		}
	}

	void ReplayGUI::SetSpeed()
	{
		switch ( SpeedVal )
		{
			case 0:
				StepControl = true; // Start step control
				Tools::setPhsxSpeed( 1 );
				Speed->SubstituteText( std::wstring( L"x 0" ) );
				break;
			case 1:
				Tools::setPhsxSpeed( 0 );
				Speed->SubstituteText( std::wstring( L"x .5" ) );
				break;
			case 2:
				Tools::setPhsxSpeed( 1 );
				Speed->SubstituteText( std::wstring( L"x 1" ) );
				break;
			case 3:
				Tools::setPhsxSpeed( 2 );
				Speed->SubstituteText( std::wstring( L"x 2" ) );
				break;
			case 4:
				Tools::setPhsxSpeed( 3 );
				Speed->SubstituteText( std::wstring( L"x 4" ) );
				break;
		}

		// Ensure the game is unpaused if we aren't step controlling and we aren't soliciting a pause
		// We set this to false elsewhere in this case, but not soon enough for the game to realize
		// we aren't paused and set the PhsxSpeed to 1
		if ( !PauseSelected && !StepControl )
			setPauseGame( false );
	}

	void ReplayGUI::ProcessInput()
	{
		boost::shared_ptr<Level> level = MyGame->MyLevel;

		if ( SkipPhsxStep )
		{
			SkipPhsxStep = false;
			return;
		}

		if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed )
		{
			if ( level->ReplayPaused && ReplayIsOver() )
			{
				PauseSelected = false;
				SetPlayText();

				level->ReplayPaused = false;

				// Reset
				ResetReplay( level );
				setPauseGame( false );
			}
		}

		if ( Type == ReplayGUIType_COMPUTER )
		{
			// Check for reset
			if ( ButtonCheck::State( ControllerButtons_LS, -1 ).Pressed )
			{
				ResetReplay( level );
				setPauseGame( false );
			}
		}
		else
		{
			// Check for switching
			int SwarmIndex = level->MySwarmBundle->getSwarmIndex();
			if ( ButtonCheck::State( ControllerButtons_LS, -1 ).Pressed )
			{
				if ( StepControl && level->CurPhsxStep < 36 || Tools::DrawCount - TimeStamp < 36 )
					level->MySwarmBundle->SetSwarm( level, SwarmIndex - 1 );
				ResetReplay( level );
				setPauseGame( false );
			}
			if ( SwarmIndex < level->MySwarmBundle->getNumSwarms() - 1 && ButtonCheck::State(ControllerButtons_RS, -1).Pressed )
			{
				level->MySwarmBundle->SetSwarm( level, SwarmIndex + 1 );
				ResetReplay( level );
				setPauseGame( false );
			}
		}

		float Dir = ButtonCheck::GetDir( -1 ).X;// ButtonCheck.State(ControllerButtons.LJ, -1).Dir.X;
		if ( PrevDir != ::Sign( Dir ) )
			Delay = 0;
		if ( Delay == 0 )
		{
			bool Change = false;
			if ( Dir < -ButtonCheck::ThresholdSensitivity )
			{
				SpeedVal--;
				Change = true;
			}
			else if ( Dir > ButtonCheck::ThresholdSensitivity )
			{
				SpeedVal++;
				Change = true;
			}

			if ( Change )
			{
				SpeedVal = CoreMath::RestrictVal( 0, 4, SpeedVal );

				//if (SpeedVal == 1) Delay = 30;
				//else if (SpeedVal == 2) Delay = 30;
				//else Delay = 15;
				Delay = 1000;

				StepControl = false;

				SetSpeed();

				SetPlayText();

				//if (!StepControl) PauseGame = false;
			}
		}
		else
		{
			Delay--;
		}
		PrevDir = ::Sign( Dir );

		// Switch between swarm and single view (Toggle)
		if ( Type == ReplayGUIType_REPLAY )
		{
			if ( ButtonCheck::State( ControllerButtons_X, -1 ).Pressed )
			{
				level->SingleOnly = !level->SingleOnly;
				level->MainReplayOnly = level->SingleOnly;
				SetToggleText();
			}
		}

		// End the replay
		bool EndReplay = false;
	#if defined(PC_VERSION)
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Escape ) )
			EndReplay = true;
	#endif

		if ( ButtonCheck::State( ControllerButtons_B, -1 ).Pressed )
			EndReplay = true;

		if ( EndReplay )
		{
			setPauseGame( false );
			Tools::setPhsxSpeed( 1 );

			ReturnToCaller();

			level->FreeReset = true;
			if ( Type == ReplayGUIType_REPLAY )
			{
				level->EndReplay();
			}
			else
				level->EndComputerWatch();
		}
	}

	void ReplayGUI::Reset( bool BoxesOnly )
	{
		CkBaseMenu::Reset( BoxesOnly );

		TimeStamp = Tools::DrawCount;
	}

	void ReplayGUI::MyPhsxStep()
	{
		boost::shared_ptr<Level> level = MyGame->MyLevel;

		if ( level->SuppressReplayButtons )
			return;

		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		InGameStartMenu::PreventMenu = true;

		if ( StepControl && !PauseSelected )
		{
			if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed || ButtonStats::All->DownCount( ControllerButtons_A ) > 30 && Tools::DrawCount % 2 == 0 )
				setPauseGame( false );
			else
				setPauseGame( true );
		}
		else
		{
			if ( ButtonCheck::State( ControllerButtons_A, -1 ).Pressed )
			{
				PauseSelected = !PauseSelected;
				SetPlayText();

				SetSpeed();
			}

			setPauseGame( PauseSelected );
		}

		ProcessInput();
	}

	void ReplayGUI::MyDraw()
	{
		if ( MyGame == 0 )
		{
			Release();
			return;
		}

		boost::shared_ptr<Level> level = MyGame->MyLevel;

		if ( level->SuppressReplayButtons )
			return;

		CkBaseMenu::MyDraw();

		BigEnd->Show = BigPaused->Show = false;
		if ( level->ReplayPaused )
		{
			if ( ReplayIsOver() )
				BigEnd->Show = true;
		}
		else
		{
			if ( PauseSelected )
			{
				BigPaused->ScaleYToMatchRatio( 300 );
				BigPaused->Show = true;
			}
		}
	}

	bool ReplayGUI::ReplayIsOver()
	{
		boost::shared_ptr<Level> level = MyGame->MyLevel;

		if ( Type == ReplayGUIType_COMPUTER && level->EndOfReplay() )
			return true;

		if ( Type == ReplayGUIType_REPLAY )
			if ( level->MySwarmBundle->EndCheck( level ) && !level->MySwarmBundle->GetNextSwarm( level ) )
				return true;

		return false;
	}

	void ReplayGUI::InitializeInstanceFields()
	{
		Type = static_cast<ReplayGUIType>( 0 );
		SkipPhsxStep = false;


		StepControl = false;
		SpeedVal = 2;
		Delay = 10;
		PrevDir = 0;
		PauseSelected = false;
		TimeStamp = 0;
	}
}
