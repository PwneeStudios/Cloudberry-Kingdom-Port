#include "GUI_Text.h"
#include "Core/FancyVector2.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"
#include "Core/Text/EzFont.h"
#include "Core/Graphics/Draw/DrawPile.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	std::shared_ptr<GUI_Text> GUI_Text::SimpleTitle( Localization::Words word )
	{
		return SimpleTitle( word, Style_BUBBLE );
	}

	std::shared_ptr<GUI_Text> GUI_Text::SimpleTitle( Localization::Words word, Style style )
	{
		Vector2 pos1 = Vector2( -23, -23 );
		Vector2 pos2 = Vector2( 23, 23 );

		std::shared_ptr<GUI_Text> text = std::make_shared<GUI_Text>( word, pos1, style );
		text->FixedToCamera = true;

		text->MyPile->FancyPos->LerpTo( pos1, pos2, 70, LerpStyle_LINEAR );
		text->MyPile->FancyPos->Loop = true;
		return text;
	}

	GUI_Text::GUI_Text( Localization::Words word, Vector2 pos )
	{
		InitializeInstanceFields();
		Init( word, pos, true, Style_BUBBLE, Resources::Font_Grobold42 );
	}

	GUI_Text::GUI_Text( Localization::Words word, Vector2 pos, bool centered )
	{
		InitializeInstanceFields();
		Init( word, pos, centered, Style_BUBBLE, Resources::Font_Grobold42 );
	}

	GUI_Text::GUI_Text( Localization::Words word, Vector2 pos, Style style )
	{
		InitializeInstanceFields();
		Init( word, pos, true, style, Resources::Font_Grobold42 );
	}

	GUI_Text::GUI_Text( const std::wstring &text, Vector2 pos )
	{
		InitializeInstanceFields();
		Init( text, pos, true, Style_BUBBLE, Resources::Font_Grobold42 );
	}

	GUI_Text::GUI_Text( const std::wstring &text, Vector2 pos, bool centered )
	{
		InitializeInstanceFields();
		Init( text, pos, centered, Style_BUBBLE, Resources::Font_Grobold42 );
	}

	GUI_Text::GUI_Text( const std::wstring &text, Vector2 pos, bool centered, const std::shared_ptr<EzFont> &font )
	{
		InitializeInstanceFields();
		Init( text, pos, centered, Style_BUBBLE, font );
	}

	void GUI_Text::Init( Localization::Words word, Vector2 pos, bool centered, Style style, const std::shared_ptr<EzFont> &font )
	{
		MyStyle = style;
		FixedToCamera = false;

		MyPile = std::make_shared<DrawPile>();
		MyText = MakeText( word, centered, font );
		MyPile->Add( MyText );

		MyPile->setPos( pos + Vector2( 0, MyText->GetWorldHeight() / 2 ) );

		if ( MyStyle == Style_BUBBLE )
			MyPile->BubbleUp( true );
		if ( MyStyle == Style_FADE )
			MyPile->FadeIn( .0175f );
		Active = true;
		Hid = false;
	}

	void GUI_Text::Init( const std::wstring &text, Vector2 pos, bool centered, Style style, const std::shared_ptr<EzFont> &font )
	{
		MyStyle = style;
		FixedToCamera = false;

		MyPile = std::make_shared<DrawPile>();
		MyText = MakeText( text, centered, font );
		MyPile->Add( MyText );

		MyPile->setPos( pos + Vector2( 0, MyText->GetWorldHeight() / 2 ) );

		if ( MyStyle == Style_BUBBLE )
			MyPile->BubbleUp( true );
		if ( MyStyle == Style_FADE )
			MyPile->FadeIn( .0175f );
		Active = true;
		Hid = false;
	}

	std::shared_ptr<EzText> GUI_Text::MakeText( Localization::Words word, bool centered, const std::shared_ptr<EzFont> &font )
	{
		return std::make_shared<EzText>( word, font, 1900, true, true,.575f );
	}

	std::shared_ptr<EzText> GUI_Text::MakeText( const std::wstring &text, bool centered, const std::shared_ptr<EzFont> &font )
	{
		return std::make_shared<EzText>( text, font, 1900, true, true,.575f );
	}

	void GUI_Text::Kill()
	{
		Kill( true );
	}

	void GUI_Text::Kill( bool sound )
	{
		if ( MyStyle == Style_BUBBLE )
		{
			MyPile->BubbleDown( sound );
			MyPile->FadeOut( 1 / 20 );
		}
		if ( MyStyle == Style_FADE )
			MyPile->FadeOut( .0175f );

		ReleaseWhenDoneScaling = true;
	}

	void GUI_Text::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		if ( !Active )
			return;

		if ( !NoPosMod )
		{
			if ( Oscillate_Renamed )
			{
				Pos->RelVal = getCore()->StartData.Position + Vector2(0, OscillationHeight * static_cast<float>(sin(OscillationSpeed * (getCore()->MyLevel->CurPhsxStep) + getCore()->AddedTimeStamp)));
			}
			else
			{
				getCore()->Data.Integrate();
				Pos->RelVal = getCore()->Data.Position;
			}
		}
	}

	void GUI_Text::MyDraw()
	{
		if ( Hid )
			return;

		GUI_Panel::MyDraw();
	}

	void GUI_Text::InitializeInstanceFields()
	{
		MyStyle = Style_BUBBLE;
		NoPosMod = true;
		Oscillate_Renamed = false;
		OscillationHeight = 12;
		OscillationSpeed = .0262f;
	}
}
