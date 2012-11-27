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

	NewHero::NewHero( const std::wstring &str )
	{
		InitializeInstanceFields();
		Init( str, Vector2(), 1, false );
	}

	NewHero::NewHero( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		InitializeInstanceFields();
		Init( str, shift, scale, perma );
	}

	std::shared_ptr<NewHero> NewHero::HeroTitle( const std::wstring &str )
	{
		std::shared_ptr<NewHero> title = std::make_shared<NewHero>( str, Vector2( 150, -130 ), 1, false );
		title->SlideInLength = 55;

		return title;
	}

	void NewHero::Init( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		SlideInLength = 84;

		this->Perma = perma;

		//Core.DrawLayer++; // Draw above cheering berries
		PauseOnPause = true;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();
		MyPile->setPos( MyPile->getPos() + shift );

		Tools::Warning(); // May be text, rather than Localization.Words
		text = std::make_shared<EzText>( str, Resources::Font_Grobold42, true, true );
		text->setScale( text->getScale() * scale );

		text->MyFloatColor = ( Color( 26, 188, 241 ) ).ToVector4();
		text->OutlineColor = ( Color( 255, 255, 255 ) ).ToVector4();

		text->Shadow = true;
		text->ShadowOffset = Vector2( 10.5f, 10.5f );
		text->ShadowColor = Color( 30, 30, 30 );
	}

	void NewHero::MyPhsxStep()
	{
		GUI_Panel::MyPhsxStep();

		Count++;

		// Make sure we're on top
		if ( !getCore()->Released && getCore()->MyLevel != 0 )
			getCore()->MyLevel->MoveToTopOfDrawLayer(this);

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
