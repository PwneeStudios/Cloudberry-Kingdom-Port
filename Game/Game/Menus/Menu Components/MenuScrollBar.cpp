#include <global_header.h>

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Input;

namespace CloudberryKingdom
{

	MenuScrollBar::MenuScrollBar() : MenuSlider(std::make_shared<EzText>(_T(""), Resources::Font_Grobold42))
	{
		InitializeInstanceFields();
	}

	void MenuScrollBar::InitializeSlider()
	{
		MenuSlider::InitializeSlider();

		Normal = Tools::TextureWad->FindByName( _T( "BouncyBlock1" ) );
		Held = Tools::TextureWad->FindByName( _T( "BouncyBlock2" ) );

		EndQuad = std::make_shared<QuadClass>( _T( "Joint" ), 85, true );
		StartQuad = std::make_shared<QuadClass>( _T( "Joint" ), 85, true );
	}

	void MenuScrollBar::Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected )
	{
		Slider->Show = SliderBack->Show = false;
		MenuSlider::Draw( Text, cam, Selected );

		if ( MyMenu->CurDrawLayer != 0 || !Show )
			return;

		if ( !Text )
		{
	#if defined(PC_VERSION)
			if ( Selected && Tools::Mouse.LeftButton == ButtonState::Pressed )
				Slider->Quad_Renamed->MyTexture = Held;
			else
				Slider->Quad_Renamed->MyTexture = Normal;
	#else
			if ( Selected )
				Slider->Quad_Renamed->MyTexture = Held;
			else
				Slider->Quad_Renamed->MyTexture = Normal;
	#endif

			Tools::QDrawer->DrawLine( Start + StartPlus, End + EndPlus, Color( 255, 255, 255, 235 ), 85, SliderBack->Quad_Renamed->MyTexture, Tools::BasicEffect, 85, 0, 0 );
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
