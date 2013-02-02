#include <global_header.h>

namespace CloudberryKingdom
{

	void NewHero_GUI::OnAdd()
	{
		GUI_Panel::OnAdd();

		Vector2 shift = Vector2( 0.f, -.5f * 2000 + 380 + 500 );

		// Add the text
		text->setPos( shift );
		MyPile->Add( text );

		// Scale to fit
		Vector2 size = text->GetWorldSize();
		float max = MyGame->getCam()->GetWidth() - 400;
		if ( size.X > max )
			text->setScale( text->getScale() * max / size.X );

		// Slide out
		//this->SlideOut( PresetPos_LEFT, 0 );
		SlideIn(0);
		MyPile->setAlpha( 0 );

        // Sound
        Tools::SoundWad->FindByName( L"HeroUnlockedSound" )->Play();

		if ( Perma )
			this->SlideIn( 0 );
	}

	NewHero_GUI::NewHero_GUI( const std::wstring &str ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<NewHero_GUI> NewHero_GUI::NewHero_GUI_Construct( const std::wstring &str )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( str, Vector2(), 1, false );

		return boost::static_pointer_cast<NewHero_GUI>( shared_from_this() );
	}

	NewHero_GUI::NewHero_GUI( const std::wstring &str, Vector2 shift, float scale, bool perma ) :
		Perma( false ),
		Count( 0 )
	{
	}
	boost::shared_ptr<NewHero_GUI> NewHero_GUI::NewHero_GUI_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		InitializeInstanceFields();
		GUI_Panel::GUI_Panel_Construct();

		Init( str, shift, scale, perma );

		return boost::static_pointer_cast<NewHero_GUI>( shared_from_this() );
	}

	boost::shared_ptr<NewHero_GUI> NewHero_GUI::HeroTitle( const std::wstring &str )
	{
		boost::shared_ptr<NewHero_GUI> title = MakeMagic( NewHero_GUI, ( str, Vector2( 150, -130 ), 1.f, false ) );
		title->SlideInLength = 55;

		return title;
	}

	void NewHero_GUI::Init( const std::wstring &str, Vector2 shift, float scale, bool perma )
	{
		shift += Vector2( 0, -350 );

		SlideInLength = 84;

		this->Perma = perma;

		//Core.DrawLayer++; // Draw above cheering berries
		PauseOnPause = true;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();
		MyPile->setPos( MyPile->getPos() + shift );

		Tools::Warning(); // May be text, rather than Localization.Words
		text = boost::make_shared<EzText>( str, Resources::Font_Grobold42, 3000, true, true, .55f );
		text->setScale( text->getScale() * scale );

		text->MyFloatColor = ( bColor( 26, 188, 241 ) ).ToVector4();
		text->OutlineColor = ( bColor( 255, 255, 255 ) ).ToVector4();

		text->Shadow = true;
		text->ShadowOffset = Vector2( 10.5f, 10.5f );
		text->ShadowColor = bColor( 30, 30, 30 );
	}

	void NewHero_GUI::MyPhsxStep()
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
		if (getMyLevel()->MyLevelSeed->ShowChapterName  && Count == 120 ||
			!getMyLevel()->MyLevelSeed->ShowChapterName && Count == 40)
        {
                //SlideIn();
				//SlideIn(0);
				//MyPile->BubbleUp(false);
				MyPile->FadeIn(.02f);
		}

		if (getMyLevel()->MyLevelSeed->ShowChapterName && Count == 180 ||
			!getMyLevel()->MyLevelSeed->ShowChapterName && Count == 150)
        {
            //SlideOut(PresetPos.Right, 160);
            //ReleaseWhenDone = true;

            //MyPile->BubbleDownAndFade(true);
            //ReleaseWhenDoneScaling = true;
			MyPile->FadeOut(.025f);
        }

		if (Count == 400)
			Release();

	}

	void NewHero_GUI::InitializeInstanceFields()
	{
		Count = 0;
	}
}
