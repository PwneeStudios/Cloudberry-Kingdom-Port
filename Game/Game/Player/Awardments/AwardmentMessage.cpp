#include <global_header.h>



namespace CloudberryKingdom
{

	AwardmentMessage::AwardmentMessage( const std::shared_ptr<Awardment> &award ) { }
	std::shared_ptr<AwardmentMessage> AwardmentMessage::AwardmentMessage_Construct( const std::shared_ptr<Awardment> &award )
	{

		CkBaseMenu::CkBaseMenu_Construct();

		InitializeInstanceFields();
		getCore()->DrawLayer += 2;

		PauseOnPause = false;
		setPauseLevel( false );
		FixedToCamera = true;
		getCore()->RemoveOnReset = false;

		MyPile = std::make_shared<DrawPile>();

		MakeBackdrop();

		SetText( award );

		std::shared_ptr<EzText> Title;
		if ( award->Unlockable == 0 )
			Title = std::make_shared<EzText>( _T( "" ), Resources::Font_Grobold42_2, 1800.f, false, false,.575f );
		else
			Title = std::make_shared<EzText>( award->Name, Resources::Font_Grobold42_2, 1800.f, false, false,.575f );
		Title->setPos( Vector2( -1726.192f, 369.0475f ) );
		Title->setScale( Title->getScale() * .79f );
		MyPile->Add( Title );

		return std::static_pointer_cast<AwardmentMessage>( shared_from_this() );
	}

	void AwardmentMessage::MakeBackdrop()
	{
		Backdrop = std::make_shared<QuadClass>( std::shared_ptr<EzTexture>(), true, false );
		Backdrop->setTextureName( _T( "WidePlaque" ) );
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

	void AwardmentMessage::SlideOut( const PresetPos &Preset, int Frames )
	{
		if ( Frames == 0 )
			return;

		Kill( true );
		Active = false;
	}

	void AwardmentMessage::SetText( const std::shared_ptr<Awardment> &award )
	{
		std::wstring text = award->Name;

		// Erase previous text
		MyPile->MyTextList.clear();

		// Add the new text
		Text = std::make_shared<EzText>( text, ItemFont, 1800.f, false, false, .575f );

		if ( award->Unlockable == 0 )
		{
			Text->setScale( Text->getScale() * 1.15f );
			MyPile->Add( Text );

			Vector2 size = Text->GetWorldSize();
			Text->setPos( Vector2( -size.X / 2 - 350, size.Y *.85f ) + Vector2( 38, 32 ) );
		}
		else
		{
			Text->setScale( Text->getScale() * .74f );
			MyPile->Add( Text );
			SizeAndPosition();
		}
	}

	void AwardmentMessage::SizeAndPosition()
	{
		Vector2 size = Text->GetWorldSize();
		float MaxSize = 1200;
		if ( size.X > MaxSize )
			Text->setScale( Text->getScale() * MaxSize / size.X );

		size = Text->GetWorldSize();
		Text->setPos( Vector2( -size.X / 2 - 350, size.Y *.85f ) );

		Text->setPos( Text->getPos() + Vector2(0, -42) );
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
