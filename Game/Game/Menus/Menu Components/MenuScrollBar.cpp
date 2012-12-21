#include <global_header.h>

namespace CloudberryKingdom
{

	MenuScrollBar::MenuScrollBar()
	{
		InitializeInstanceFields();
	}

	boost::shared_ptr<MenuScrollBar> MenuScrollBar::MenuScrollBar_Construct()
	{
		MenuSlider::MenuSlider_Construct( boost::make_shared<EzText>( std::wstring( L"" ), Resources::Font_Grobold42 ) );
		return boost::static_pointer_cast<MenuScrollBar>( shared_from_this() );
	}

	void MenuScrollBar::InitializeSlider()
	{
		MenuSlider::InitializeSlider();

		Normal = Tools::TextureWad->FindByName( std::wstring( L"BouncyBlock1" ) );
		Held = Tools::TextureWad->FindByName( std::wstring( L"BouncyBlock2" ) );

		EndQuad = boost::make_shared<QuadClass>( std::wstring( L"Joint" ), 85.f, true );
		StartQuad = boost::make_shared<QuadClass>( std::wstring( L"Joint" ), 85.f, true );
	}

	void MenuScrollBar::Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected )
	{
		Slider->Show = SliderBack->Show = false;
		MenuSlider::Draw( Text, cam, Selected );

		if ( MyMenu->CurDrawLayer != 0 || !Show )
			return;

		if ( !Text )
		{
	#if defined(PC_VERSION)
			if ( Selected && Tools::Mouse.LeftButton == ButtonState_Pressed )
				Slider->Quad_Renamed.setMyTexture( Held );
			else
				Slider->Quad_Renamed.setMyTexture( Normal );
	#else
			if ( Selected )
				Slider->Quad_Renamed.setMyTexture( Held );
			else
				Slider->Quad_Renamed.setMyTexture( Normal );
	#endif

			Tools::QDrawer->DrawLine( Start + StartPlus, End + EndPlus, bColor( 255, 255, 255, 235 ), 85, SliderBack->Quad_Renamed.getMyTexture(), Tools::BasicEffect, 85, 0, 0.f );
						//new Color(255, 255, 255, 215),
			StartQuad->setPos( Start );
			EndQuad->setPos( End );

			StartQuad->Draw();
			EndQuad->Draw();
			Slider->Show = true;
			Slider->Draw();

			Tools::QDrawer->Flush();

			if ( Tools::DrawBoxes )
			{
				Tools::QDrawer->DrawCircle( End, 5, Color::Red );
				Tools::QDrawer->DrawCircle( Start, 5, Color::Red );
			}
		}
	}

	void MenuScrollBar::InitializeInstanceFields()
	{
		StartPlus = Vector2( 0, -600 );
		EndPlus = Vector2( 0, 600 );
		DrawEnds = false;
	}
}
