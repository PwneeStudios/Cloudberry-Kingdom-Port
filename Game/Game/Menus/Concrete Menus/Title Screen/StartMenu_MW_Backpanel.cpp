#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void StartMenu_MW_Backpanel::Hide( const std::shared_ptr<PresetPos> &pos, int frames )
	{
		CkBaseMenu::Hide( pos, frames );
		ButtonCheck::PreLogIn = false;
	}

	void StartMenu_MW_Backpanel::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Backpanel::SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames )
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
		Scene->FancyScale = std::make_shared<FancyVector2>();
		Scene->FancyScale->LerpTo( 1.025f * size, size, 120, LerpStyle_DECAY_NO_OVERSHOOT );
	}

	void StartMenu_MW_Backpanel::Init()
	{
		 CkBaseMenu::Init();

		MyPile = std::make_shared<DrawPile>();

		EnsureFancy();

		Scene = std::make_shared<QuadClass>( _T( "Title_Screen" ), 1778 );
		MyPile->Add( Scene, _T( "Scene" ) );

		Title = std::make_shared<QuadClass>( _T( "Title" ), 1778 );
		//MyPile.Add(Title, "Title");

		Title_Trim = std::make_shared<QuadClass>( _T( "Title_Trim" ), 1778 * 783 / 1280 );
		MyPile->Add( Title_Trim, _T( "Title_Trim" ) );

		Scene_NoBob_Blur = std::make_shared<QuadClass>( _T( "Title_NoBob_Blur" ), 1778 );
		MyPile->Add( Scene_NoBob_Blur, _T( "Scene_NoBob_Blur" ) );

		Scene_NoBob_Brighten = std::make_shared<QuadClass>( _T( "Title_NoBob_Brighten" ), 1778 );
		MyPile->Add( Scene_NoBob_Brighten, _T( "Scene_NoBob_Brighten" ) );

		Scene_Blur = std::make_shared<QuadClass>( _T( "Title_Blur" ), 1778 );
		MyPile->Add( Scene_Blur, _T( "Scene_Blur" ) );

		Scene_Princess = std::make_shared<QuadClass>( _T( "Scene_Princess" ), 1778 );
		MyPile->Add( Scene_Princess, _T( "Scene_Princess" ) );

		Scene_Kobbler = std::make_shared<QuadClass>( _T( "Scene_Kobbler" ), 1778 );
		MyPile->Add( Scene_Kobbler, _T( "Scene_Kobbler" ) );

		Scene_Kobbler_Blur = std::make_shared<QuadClass>( _T( "Scene_Kobbler_Blur" ), 1778 );
		MyPile->Add( Scene_Kobbler_Blur, _T( "Scene_Kobbler_Blur" ) );

		BlackBox();
	}

	void StartMenu_MW_Backpanel::SetState( State state )
	{
		for ( std::vector<QuadClass*>::const_iterator quad = MyPile->MyQuadList.begin(); quad != MyPile->MyQuadList.end(); ++quad )
		{
			( *quad )->ResetFade();
			( *quad )->Show = false;
		}

		switch ( state )
		{
			case State_NONE:
				Title->Show = Scene->Show = Scene_Princess->Show = Scene_Kobbler->Show = false;
				break;

			case State_SCENE_TITLE:
				Title->Show = Scene->Show = true;
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

		Title_Trim->Show = Title->Show;
	}

	void StartMenu_MW_Backpanel::BlackBox()
	{
		std::shared_ptr<QuadClass> _q;
		_q = MyPile->FindQuad( _T( "Scene" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1000.125f ) );
		}
		_q = MyPile->FindQuad( _T( "Title" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1000.125f ) );
		}
		_q = MyPile->FindQuad( _T( "Title_Trim" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( -155.5557f, 536.1109f ) );
			_q->setSize( Vector2( 1087.636f, 373.6578f ) );
		}
		_q = MyPile->FindQuad( _T( "Scene_NoBob_Blur" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1778 ) );
		}
		_q = MyPile->FindQuad( _T( "Scene_NoBob_Brighten" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1778 ) );
		}
		_q = MyPile->FindQuad( _T( "Scene_Blur" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1000.125f ) );
		}
		_q = MyPile->FindQuad( _T( "Scene_Princess" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1000.125f ) );
		}
		_q = MyPile->FindQuad( _T( "Scene_Kobbler" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1000.125f ) );
		}
		_q = MyPile->FindQuad( _T( "Scene_Kobbler_Blur" ) );
		if ( _q != 0 )
		{
			_q->setPos( Vector2( 0, 0 ) );
			_q->setSize( Vector2( 1778, 1000.125f ) );
		}

		MyPile->setPos( Vector2( 0, 0 ) );

	}

	void StartMenu_MW_Backpanel::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		//if (ButtonCheck.AnyKey()) Title_Trim.Show = !Title_Trim.Show;
	}

	void StartMenu_MW_Backpanel::MyDraw()
	{
		// Fade to black/from black for blurred background
		float black = Scene_Blur->Quad_Renamed->MySetColor->R / 255;
		if ( MyState == State_SCENE_BLUR_DARK )
			black = CoreMath::Restrict( .7f, 1, black - .33f );
		else
			black = CoreMath::Restrict( .7f, 1, black + .33f );
		Scene_Blur->Quad_Renamed->SetColor( ColorHelper::Gray( black ) );

		// Oscillate title color
		if ( Title->Show )
		{
			t += .01f;

			//Scene.Size = new Vector2(1069.027f, 429.9995f) * Tools.SmoothLerp(.85f, 1f, t);

			Vector4 c1 = Vector4( 0 );
			Vector4 c2 = Vector4( 1 );
			Title->Quad_Renamed->SetColor( Vector4::Lerp( c1, c2, t ) );
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
}
