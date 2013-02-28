#include <global_header.h>

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
		Play->MyFloatColor = ( Color( static_cast<unsigned char>( 67 ), static_cast<unsigned char>( 198 ), static_cast<unsigned char>( 48 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		Play->Name = std::wstring( L"Play" );
		SetHeaderProperties( Play );
	#endif

	#if defined(PC_VERSION)
		AdditionalAdd = Vector2( -2, 0 );
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 140.f, static_cast<std::wstring>( std::wstring( L"Button_Back" ) ) ) );
		End = boost::make_shared<EzText>( Localization::Words_Done, ItemFont, true );
		End->Name = std::wstring( L"Back" );
		SetGrayHeaderProperties( End );
	#else
		MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getBack(), 85.f, static_cast<std::wstring>( std::wstring( L"Button_Back" ) ) ) );
		End = boost::make_shared<EzText>( Localization::Words_Done, ItemFont, true );
		End->MyFloatColor = ( Color( static_cast<unsigned char>( 239 ), static_cast<unsigned char>( 41 ), static_cast<unsigned char>( 41 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		End->Name = std::wstring( L"Back" );
		SetHeaderProperties( End );
	#endif

		if ( Type == ReplayGUIType_REPLAY )
		{
			MyPile->Add( boost::make_shared<QuadClass>( ButtonTexture::getX(), 90.f, static_cast<std::wstring>( std::wstring( L"Button_X" ) ) ) );
			Toggle = boost::make_shared<EzText>( Localization::Words_Single, ItemFont, true );
			Toggle->Name = std::wstring( L"Toggle" );
	#if defined(PC_VERSION)
			SetGrayHeaderProperties( Toggle );
	#else
			SetHeaderProperties( Toggle );
			Toggle->MyFloatColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
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



			if ( Type == ReplayGUIType_COMPUTER )
			{
if ( ButtonCheck::ControllerInUse )
{
#if XBOX || PC_VERSION
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-721.1783f, -832.2222f ) ); _t->setScale( 0.44f ); }
				_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-120.0003f, -832.2223f ) ); _t->setScale( 0.44f ); }
				_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 264.0002f, -832.2222f ) ); _t->setScale( 0.44f ); }
				_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 954.3328f, -846.1111f ) ); _t->setScale( 0.3934999f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
				_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
				_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5562f, -911.1113f ) ); _q->setSize( Vector2( 69.64276f, 69.64276f ) ); }
				_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-347.2227f, -911.1112f ) ); _q->setSize( Vector2( 71.76664f, 71.76664f ) ); }
				_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 186.1109f, -911.1112f ) ); _q->setSize( Vector2( 77.89992f, 77.89992f ) ); }
				_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 655.555f, -908.3333f ) ); _q->setSize( Vector2( 152.0833f, 152.0833f ) ); }

				MyPile->setPos( Vector2( 0.f, 0.f ) );
#else
				boost::shared_ptr<EzText> _t;
				_t = MyPile->FindEzText( L"Play" ); if (_t != 0 ) { _t->setPos( Vector2(-721.1783f, -832.2222f ) ); _t->setScale( 0.44f ); }
				_t = MyPile->FindEzText( L"Back" ); if (_t != 0 ) { _t->setPos( Vector2(-120.0003f, -832.2223f ) ); _t->setScale( 0.44f ); }
				_t = MyPile->FindEzText( L"Speed" ); if (_t != 0 ) { _t->setPos( Vector2( 264.0002f, -832.2222f ) ); _t->setScale( 0.44f ); }
				_t = MyPile->FindEzText( L"Reset" ); if (_t != 0 ) { _t->setPos( Vector2( 1001.555f, -843.3333f ) ); _t->setScale( 0.3934999f ); }

				boost::shared_ptr<QuadClass> _q;
				_q = MyPile->FindQuad( L"Backdrop2" ); if (_q != 0 ) { _q->setPos( Vector2( 55.55542f, -2058.333f ) ); _q->setSize( Vector2( 1230.664f, 1230.664f ) ); }
				_q = MyPile->FindQuad( L"Backdrop" ); if (_q != 0 ) { _q->setPos( Vector2( 52.77765f, -2058.333f ) ); _q->setSize( Vector2( 1219.997f, 1219.997f ) ); }
				_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-930.5562f, -911.1113f ) ); _q->setSize( Vector2( 69.64276f, 69.64276f ) ); }
				_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-347.2227f, -911.1112f ) ); _q->setSize( Vector2( 71.76664f, 71.76664f ) ); }
				_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 186.1109f, -911.1112f ) ); _q->setSize( Vector2( 77.89992f, 77.89992f ) ); }
				_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 613.8885f, -916.6666f ) ); _q->setSize( Vector2( 91.65893f, 61.58334f ) ); }

				MyPile->setPos( Vector2( 0.f, 0.f ) );
#endif
}
else
{
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
				_q = MyPile->FindQuad( L"Button_Go" ); if (_q != 0 ) { _q->setPos( Vector2(-1200.f, -905.5555f ) ); _q->setSize( Vector2( 64.55943f, 64.55943f ) ); }
				_q = MyPile->FindQuad( L"Button_Back" ); if (_q != 0 ) { _q->setPos( Vector2(-688.8887f, -911.111f ) ); _q->setSize( Vector2( 67.34993f, 67.34993f ) ); }
				_q = MyPile->FindQuad( L"Button_X" ); if (_q != 0 ) { _q->setPos( Vector2(-213.8887f, -908.3332f ) ); _q->setSize( Vector2( 65.58324f, 65.58324f ) ); }
				_q = MyPile->FindQuad( L"Button_LR" ); if (_q != 0 ) { _q->setPos( Vector2( 352.7776f, -905.5555f ) ); _q->setSize( Vector2( 69.04251f, 64.89996f ) ); }
				_q = MyPile->FindQuad( L"Button_LB" ); if (_q != 0 ) { _q->setPos( Vector2( 727.7779f, -902.7776f ) ); _q->setSize( Vector2( 103.1499f, 103.1499f ) ); }
				_q = MyPile->FindQuad( L"Button_RB" ); if (_q != 0 ) { _q->setPos( Vector2( 1155.556f, -902.7778f ) ); _q->setSize( Vector2( 107.5665f, 107.5665f ) ); }
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1210.557f, 791.1111f ) ); _q->setSize( Vector2( 300.f, 105.f ) ); }
				_q = MyPile->FindQuad( L"" ); if (_q != 0 ) { _q->setPos( Vector2( 1277.222f, 774.4444f ) ); _q->setSize( Vector2( 255.f, 128.775f ) ); }

				MyPile->setPos( Vector2( 0.f, 0.f ) );
}
else
{
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
