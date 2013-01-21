#include <global_header.h>



namespace CloudberryKingdom
{

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

		boost::shared_ptr<EzText> Title, Description;

        Title = boost::make_shared<EzText>(award->TitleType, Resources::Font_Grobold42_2, 1800.f, false, false, .575f);
        Title->setPos( Vector2(-1726.192f, 300) );
        Title->_Scale *= .6f;
        MyPile->Add(Title);

        Description = boost::make_shared<EzText>(award->Description, Resources::Font_Grobold42_2, 1800.f, true, true, .575f);
        Description->setPos( Vector2(0, 100) );
        Description->_Scale *= .6f;
        MyPile->Add(Description);

		return boost::static_pointer_cast<AwardmentMessage>( shared_from_this() );
	}

	void AwardmentMessage::MakeBackdrop()
	{
		Backdrop = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		Backdrop->setTextureName( std::wstring( L"WidePlaque" ) );
		Backdrop->setSize( Vector2( 1750, 284.8255f ) );
		Backdrop->setPos( Vector2( -11.9043f, 59.52365f ) );

		MyPile->Add( Backdrop );
		MyPile->setPos( Vector2( 0, -800 ) );
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
