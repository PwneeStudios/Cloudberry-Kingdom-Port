#include <global_header.h>

namespace CloudberryKingdom
{

	void StartMenu_MW_Backpanel::Hide( PresetPos pos, int frames )
	{
		CkBaseMenu::Hide( pos, frames );
		ButtonCheck::PreLogIn = false;
	}

	void StartMenu_MW_Backpanel::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Backpanel::SlideOut( PresetPos Preset, int Frames )
	{
		//base.SlideOut(Preset, 0);
		CkBaseMenu::SlideOut( Preset, Frames );
	}

	void StartMenu_MW_Backpanel::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void StartMenu_MW_Backpanel::InitialZoomIn()
	{
		Vector2 size = Scene->getSize();
		Scene->FancyScale = boost::make_shared<FancyVector2>();
		Scene->FancyScale->LerpTo( 1.025f * size, size, 120, LerpStyle_DECAY_NO_OVERSHOOT );
	}

	void StartMenu_MW_Backpanel::Init()
	{
		CkBaseMenu::Init();

		MyPile = boost::make_shared<DrawPile>();

		EnsureFancy();

		Scene = boost::make_shared<QuadClass>( std::wstring( L"Title_Screen" ), 1778.f );
		MyPile->Add( Scene, std::wstring( L"Scene" ) );

		TM = boost::make_shared<QuadClass>( std::wstring( L"TradeMarkSymbol" ) );
		MyPile->Add(TM, std::wstring( L"TM" ) );

		Title = boost::make_shared<QuadClass>( std::wstring( L"Title" ), 1778.f );

		Title_Trim = boost::make_shared<QuadClass>( std::wstring( L"Title_Trim" ), 1778 * 783.f / 1280.f );
		MyPile->Add( Title_Trim, std::wstring( L"Title_Trim" ) );

		Scene_NoBob_Blur = boost::make_shared<QuadClass>( std::wstring( L"Title_NoBob_Blur" ), 1778.f );
		MyPile->Add( Scene_NoBob_Blur, std::wstring( L"Scene_NoBob_Blur" ) );

		Scene_NoBob_Brighten = boost::make_shared<QuadClass>( std::wstring( L"Title_NoBob_Brighten" ), 1778.f );
		MyPile->Add( Scene_NoBob_Brighten, std::wstring( L"Scene_NoBob_Brighten" ) );

		Scene_Blur = boost::make_shared<QuadClass>( std::wstring( L"Title_Blur" ), 1778.f );
		MyPile->Add( Scene_Blur, std::wstring( L"Scene_Blur" ) );

		Scene_Princess = boost::make_shared<QuadClass>( std::wstring( L"Scene_Princess" ), 1778.f );
		MyPile->Add( Scene_Princess, std::wstring( L"Scene_Princess" ) );

		Scene_Kobbler = boost::make_shared<QuadClass>( std::wstring( L"Scene_Kobbler" ), 1778.f );
		MyPile->Add( Scene_Kobbler, std::wstring( L"Scene_Kobbler" ) );

		Scene_Kobbler_Blur = boost::make_shared<QuadClass>( std::wstring( L"Scene_Kobbler_Blur" ), 1778.f );
		MyPile->Add( Scene_Kobbler_Blur, std::wstring( L"Scene_Kobbler_Blur" ) );

		BlackBox();
	}

	void StartMenu_MW_Backpanel::SetState( State state )
	{
		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyPile->MyQuadList.begin(); quad != MyPile->MyQuadList.end(); ++quad )
		{
			( *quad )->ResetFade();
			( *quad )->Show = false;
		}

		switch ( state )
		{
			case State_NONE:
				TM->Show = Title->Show = Scene->Show = Scene_Princess->Show = Scene_Kobbler->Show = false;
				break;

			case State_SCENE_TITLE:
				TM->Show = Title->Show = Scene->Show = true;
				break;

			case State_SCENE:
				Scene->Show = true;
				break;

			case State_SCENE_PRINCESS:
				Scene_Princess->Show = true;
				break;

			case State_SCENE_KOBBLER:
				Scene_Kobbler->Show = true;
				break;

			case State_SCENE_KOBBLER_BLUR:
				Scene_Kobbler_Blur->Show = true;
				break;

			case State_SCENE_BLUR:
				if ( MyState == State_SCENE_TITLE )
					Scene->Show = true;
				if ( MyState == State_SCENE_PRINCESS )
					Scene_Princess->Show = true;
				if ( MyState == State_SCENE_NO_BOB_BRIGHTEN )
					Scene_NoBob_Brighten->Show = true;
				Scene_Blur->setAlpha( .01f );
				Scene_Blur->Fade( .25f );
				Scene_Blur->Show = true;
				break;

			case State_SCENE_BLUR_DARK:
				if ( MyState == State_SCENE_TITLE )
					Scene->Show = true;
				if ( MyState == State_SCENE_PRINCESS )
					Scene_Princess->Show = true;
				if ( MyState == State_SCENE_NO_BOB_BRIGHTEN )
					Scene_NoBob_Brighten->Show = true;

				if ( MyState == State_NONE )
				{
					Scene_Blur->setAlpha( 0 );
					Scene_Blur->Fade( .025f );
					Scene_Blur->Show = true;
				}
				else if ( MyState == State_SCENE_BLUR )
				{
					Scene_Blur->Fade( .25f );
					Scene_Blur->Show = true;
				}
				else
				{
					Scene_Blur->setAlpha( .01f );
					Scene_Blur->Fade( .25f );
					Scene_Blur->Show = true;
				}
				break;

			case State_SCENE_NO_BOB_BRIGHTEN:
				//if (MyState == State.Scene_Blur) { Scene_Blur.Show = true; Scene_Blur.Alpha = 1f; Scene_Blur.Fade(-.25f); }
				if ( MyState == State_SCENE_TITLE )
					//{ Scene.Show = true; Scene.Alpha = 1f; }
				{
						Scene_NoBob_Blur->Show = true;
						Scene_NoBob_Blur->setAlpha( 1 );
				}
				Scene_NoBob_Brighten->Show = true;
				Scene_NoBob_Brighten->setAlpha( 0 );
				Scene_NoBob_Brighten->Fade( .125f );
				break;
		}
		MyState = state;

		TM->Show = Title_Trim->Show = Title->Show;
	}

	void StartMenu_MW_Backpanel::BlackBox()
	{
		boost::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( L"Scene" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1000.125f ) ); }
		_q = MyPile->FindQuad( L"TM" ); if (_q != 0 ) { _q->setPos( Vector2( 574.9999f, 469.4444f ) ); _q->setSize( Vector2( 42.55546f, 31.9166f ) ); }
		_q = MyPile->FindQuad( L"Title_Trim" ); if (_q != 0 ) { _q->setPos( Vector2(-155.5557f, 536.1109f ) ); _q->setSize( Vector2( 1087.636f, 373.6578f ) ); }
		_q = MyPile->FindQuad( L"Scene_NoBob_Blur" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1778.f ) ); }
		_q = MyPile->FindQuad( L"Scene_NoBob_Brighten" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1778.f ) ); }
		_q = MyPile->FindQuad( L"Scene_Blur" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1000.125f ) ); }
		_q = MyPile->FindQuad( L"Scene_Princess" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1000.125f ) ); }
		_q = MyPile->FindQuad( L"Scene_Kobbler" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1000.125f ) ); }
		_q = MyPile->FindQuad( L"Scene_Kobbler_Blur" ); if (_q != 0 ) { _q->setPos( Vector2( 0.f, 0.f ) ); _q->setSize( Vector2( 1778.f, 1000.125f ) ); }

		MyPile->setPos( Vector2( 0.f, 0.f ) );
	}

	void StartMenu_MW_Backpanel::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		//if (ButtonCheck.AnyKey()) Title_Trim.Show = !Title_Trim.Show;
	}

	void StartMenu_MW_Backpanel::MyDraw()
	{
		// Fade to black/from black for blurred background
		float black = Scene_Blur->Quad_Renamed.MySetColor.R / 255.f;
		if ( MyState == State_SCENE_BLUR_DARK )
			black = CoreMath::RestrictVal( .7f, 1.f, black - .33f );
		else
			black = CoreMath::RestrictVal( .7f, 1.f, black + .33f );
		Scene_Blur->Quad_Renamed.SetColor( ColorHelper::Gray( black ) );

		// Oscillate title color
		if ( Title->Show )
		{
			t += .01f;

			//Scene.Size = new Vector2(1069.027f, 429.9995f) * Tools::SmoothLerp(.85f, 1f, t);

			Vector4 c1 = Vector4( 0 );
			Vector4 c2 = Vector4( 1 );
			Title->Quad_Renamed.SetColor( Vector4::Lerp( c1, c2, t ) );
		}

		CkBaseMenu::MyDraw();
	}

	void StartMenu_MW_Backpanel::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();
	}

	void StartMenu_MW_Backpanel::InitializeInstanceFields()
	{
		t = 0;
	}

	StartMenu_MW_Backpanel::StartMenu_MW_Backpanel() :
		MyState( static_cast<State>( 0 ) ),
		t( 0 )
	{
	}

	boost::shared_ptr<StartMenu_MW_Backpanel> StartMenu_MW_Backpanel::StartMenu_MW_Backpanel_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();

		return boost::static_pointer_cast<StartMenu_MW_Backpanel>( shared_from_this() );
	}
}
