#include <global_header.h>

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

		std::shared_ptr<GUI_Text> text = MakeMagic( GUI_Text, ( word, pos1, style ) );
		text->FixedToCamera = true;

		text->MyPile->FancyPos->LerpTo( pos1, pos2, 70, LerpStyle_LINEAR );
		text->MyPile->FancyPos->Loop = true;
		return text;
	}

	GUI_Text::GUI_Text() :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct()
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
	}

	GUI_Text::GUI_Text( Localization::Words word, Vector2 pos ) :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct( Localization::Words word, Vector2 pos )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( word, pos, true, Style_BUBBLE, Resources::Font_Grobold42 );

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
	}

	GUI_Text::GUI_Text( Localization::Words word, Vector2 pos, bool centered ) :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct( Localization::Words word, Vector2 pos, bool centered )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( word, pos, centered, Style_BUBBLE, Resources::Font_Grobold42 );

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
	}

	GUI_Text::GUI_Text( Localization::Words word, Vector2 pos, Style style ) :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct( Localization::Words word, Vector2 pos, Style style )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( word, pos, true, style, Resources::Font_Grobold42 );

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
	}

	GUI_Text::GUI_Text( const std::wstring &text, Vector2 pos ) :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct( const std::wstring &text, Vector2 pos )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( text, pos, true, Style_BUBBLE, Resources::Font_Grobold42 );

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
	}

	GUI_Text::GUI_Text( const std::wstring &text, Vector2 pos, bool centered ) :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct( const std::wstring &text, Vector2 pos, bool centered )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( text, pos, centered, Style_BUBBLE, Resources::Font_Grobold42 );

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
	}

	GUI_Text::GUI_Text( const std::wstring &text, Vector2 pos, bool centered, const std::shared_ptr<EzFont> &font ) :
		MyStyle( Style_BUBBLE ),
		NoPosMod( false ),
		Oscillate_Renamed( false ),
		OscillationHeight( 0 ),
		OscillationSpeed( 0 )
	{
	}
	std::shared_ptr<GUI_Text> GUI_Text::GUI_Text_Construct( const std::wstring &text, Vector2 pos, bool centered, const std::shared_ptr<EzFont> &font )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( text, pos, centered, Style_BUBBLE, font );

		return std::static_pointer_cast<GUI_Text>( shared_from_this() );
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
		return std::make_shared<EzText>( word, font, 1900.f, true, true, .575f );
	}

	std::shared_ptr<EzText> GUI_Text::MakeText( const std::wstring &text, bool centered, const std::shared_ptr<EzFont> &font )
	{
		return std::make_shared<EzText>( text, font, 1900.f, true, true, .575f );
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
