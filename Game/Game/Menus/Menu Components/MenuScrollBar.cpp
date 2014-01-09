#include <small_header.h>
#include "Game/Menus/Menu Components/MenuScrollBar.h"

#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Text/EzText.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Menus/Menu Components/MenuSlider.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"

#include "Core/Texture/EzTextureWad.h"
#include "Game/Menus/Menu.h"

namespace CloudberryKingdom
{

	MenuScrollBar::MenuScrollBar() :
		MenuSlider( boost::make_shared<EzText>( std::wstring( L"" ), Resources::Font_Grobold42 ) )
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

		Normal = Tools::TextureWad->FindByName( std::wstring( L"Floater_Spikey_Forest" ) );
		Held = Tools::TextureWad->FindByName( std::wstring( L"Floater_Spikey_Forest" ) );
			
		//EndQuad = boost::make_shared<QuadClass>( L"Floater_Buzzsaw_Forest", 85, true );
		//StartQuad = boost::make_shared<QuadClass>( L"Floater_Buzzsaw_Forest", 85, true );
		EndQuad = boost::make_shared<QuadClass>( std::wstring( L"Firespinner_Base_Forest_1" ), 73.f, true );
		StartQuad = boost::make_shared<QuadClass>( std::wstring( L"Firespinner_Base_Forest_1" ), 73.f, true );
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
			Slider->ScaleYToMatchRatio( 100.f );

			Tools::QDrawer->DrawLine( Start + StartPlus, End + EndPlus, bColor( 255, 255, 255, 235 ), 85, SliderBack->Quad_Renamed.getMyTexture(), Tools::BasicEffect, 3000, 0, 0.f );
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
