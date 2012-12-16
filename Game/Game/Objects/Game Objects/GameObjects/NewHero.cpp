#include <global_header.h>

namespace CloudberryKingdom
{

	void NewHero::OnAdd()
	{
		GUI_Panel::OnAdd();

		Vector2 shift = Vector2( 0, -.5f * 2000 + 380 );

		// Add the text
		text->setPos( shift );
		MyPile->Add( text );

		// Scale to fit
		Vector2 size = text->GetWorldSize();
		float max = MyGame->getCam()->GetWidth() - 400;
		if ( size.X > max )
			text->setScale( text->getScale() * max / size.X );

		// Slide out
		this->SlideOut( PresetPos_LEFT, 0 );

		if ( Perma )
			this->SlideIn( 0 );
	}

	NewHero::NewHero( const std::wstring &str ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<NewHero> NewHero::NewHero_Construct( const std::wstring &str )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( str, Vector2(), 1, false );

		return boost::static_pointer_cast<NewHero>( shared_from_this() );
	}

	NewHero::NewHero( const std::wstring &str, Vector2 shift, float scale, bool perma ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<NewHero> NewHero::NewHero_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( str, shift, scale, perma );

		return boost::static_pointer_cast<NewHero>( shared_from_this() );
	}

	boost::shared_ptr<NewHero> NewHero::HeroTitle( const std::wstring &str )
	{
		boost::shared_ptr<NewHero> title = MakeMagic( NewHero, ( str, Vector2( 150, -130 ), 1.f, false ) );
		title->SlideInLength = 55;

		return title;
	}

	void NewHero::Init( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		SlideInLength = 84;

		this->Perma = perma;

		//Core.DrawLayer++; // Draw above cheering berries
		PauseOnPause = true;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();
		MyPile->setPos( MyPile->getPos() + shift );

		Tools::Warning(); // May be text, rather than Localization.Words
		text = boost::make_shared<EzText>( str, Resources::Font_Grobold42, true, true );
		text->setScale( text->getScale() * scale );

		text->MyFloatColor = ( bColor( 26, 188, 241 ) ).ToVector4();
		text->OutlineColor = ( bColor( 255, 255, 255 ) ).ToVector4();

		text->Shadow = true;
		text->ShadowOffset = Vector2( 10.5f, 10.5f );
		text->ShadowColor = bColor( 30, 30, 30 );
	}

	void NewHero::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;

		// Make sure we're on top
		if ( !getCore()->Released && getCore()->MyLevel != 0 )
			getCore()->MyLevel->MoveToTopOfDrawLayer( shared_from_this() );

		// Do nothing if this is permanent
		if ( Perma )
			return;

		// Otherwise show and hide
		if ( Count == 4 )
			SlideIn();

		if ( Count == 180 )
		{
			SlideOut( PresetPos_RIGHT, 160 );
			ReleaseWhenDone = true;
		}
	}

	void NewHero::InitializeInstanceFields()
	{
		Count = 0;
	}
}
