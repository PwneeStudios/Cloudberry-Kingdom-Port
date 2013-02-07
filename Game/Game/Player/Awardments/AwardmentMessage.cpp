#include <global_header.h>



namespace CloudberryKingdom
{

    HeroUnlockedMessage::HeroUnlockedMessage() : AwardmentMessage( 0 )
	{
	}

	boost::shared_ptr<HeroUnlockedMessage> HeroUnlockedMessage::HeroUnlockedMessage_Construct()
    {
		AwardmentMessage::AwardmentMessage_Construct( 0 );

        MakeText( L"", Localization::WordString( Localization::Words_NewHeroUnlocked ) );

        boost::shared_ptr<EzText> _t;
        _t = MyPile->FindEzText( L"Title" ); if (_t != 0 ) { _t->setPos( Vector2(-1726.192f, 300.f ) ); _t->setScale( 0.6f ); }
        _t = MyPile->FindEzText( L"Description" ); if (_t != 0 ) { _t->setPos( Vector2( 19.44458f, 36.11111f ) ); _t->setScale( 0.6f ); }

        boost::shared_ptr<QuadClass> _q;
        _q = MyPile->FindQuad( L"ArcadeBox" ); if (_q != 0 ) { _q->setPos( Vector2( 4.763306f, 0.f ) ); _q->setSize( Vector2( 919.4252f, 163.4914f ) ); }

        MyPile->setPos( Vector2( 36.11108f, 827.7778f ) );

		return boost::static_pointer_cast<HeroUnlockedMessage>( shared_from_this() );
    }

	AwardmentMessage::AwardmentMessage( const boost::shared_ptr<Awardment> &award ) { InitializeInstanceFields(); }
	boost::shared_ptr<AwardmentMessage> AwardmentMessage::AwardmentMessage_Construct( const boost::shared_ptr<Awardment> &award )
	{
		InitializeInstanceFields();
		CkBaseMenu::CkBaseMenu_Construct();

		getCore()->DrawLayer += 2;

		PauseOnPause = false;
		setPauseLevel( false );
		FixedToCamera = true;
		getCore()->RemoveOnReset = false;

		MyPile = boost::make_shared<DrawPile>();

		MakeBackdrop();

        if ( award != 0 )
        {
            MakeText(award->TitleType, Localization::WordString( award->Description ) );
		}

		return boost::static_pointer_cast<AwardmentMessage>( shared_from_this() );
	}

	void AwardmentMessage::MakeText(std::wstring TitleWord, std::wstring DescriptionWord)
    {
		boost::shared_ptr<EzText> Title, Description;

        Title = boost::make_shared<EzText>( TitleWord, Resources::Font_Grobold42_2, 1800.f, false, false, .575f );
        Title->setPos( Vector2(-1726.192f, 300) );
        Title->_Scale *= .6f;
        MyPile->Add( Title, L"Title" );

        Description = boost::make_shared<EzText>( DescriptionWord, Resources::Font_Grobold42_2, 1800.f, true, true, .575f);
        Description->setPos( Vector2(0, 100) );
        Description->_Scale *= .6f;
        MyPile->Add(Description, L"Description");
	}

	void AwardmentMessage::MakeBackdrop()
	{
        Backdrop = boost::make_shared<QuadClass>( 0, true, true );
        //Backdrop->setTextureName( L"MessageBoxThin" );
		Backdrop->setTextureName( L"WidePlaque" );
        Backdrop->SetSize( Vector2(1750.f, 284.8255f) );
        Backdrop->setPos( Vector2(-11.9043f, 59.52365f) );
        Backdrop->setDegrees( 0 );

        MyPile->Add(Backdrop, L"ArcadeBox");
        MyPile->setPos( Vector2(0, -800) );
	}

	void AwardmentMessage::SlideIn( int Frames )
	{
		Pos->RelVal = Vector2( 0, 0 );
		Active = true;
		MyPile->BubbleUp( true );
	}

	void AwardmentMessage::SlideOut( PresetPos Preset, int Frames )
	{
		if ( Frames == 0 )
			return;

		Kill( true );
		Active = false;
	}

	void AwardmentMessage::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;

		Step++;
		if ( Step < 40 )
			return;

		if ( ShouldDie() )
		{
			ReturnToCaller( false );
			setPauseLevel( false );
		}
	}

	bool AwardmentMessage::ShouldDie()
	{
		return Step > Duration;
	}

	void AwardmentMessage::Kill()
	{
		Kill( true );
	}

	void AwardmentMessage::Kill( bool sound )
	{
		MyPile->BubbleDownAndFade( sound );
		ReleaseWhenDone = false;
		ReleaseWhenDoneScaling = true;
	}

	void AwardmentMessage::InitializeInstanceFields()
	{
		Step = 0;
	}
}
