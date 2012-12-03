#include <global_header.h>



namespace CloudberryKingdom
{

	HintBlurb::HintBlurb()
	{
		InitializeInstanceFields();
		PauseOnPause = false;
		setPauseLevel( false );
		FixedToCamera = true;
		getCore()->RemoveOnReset = false;

		MyPile = std::make_shared<DrawPile>();

		MakeBackdrop();

		SetText( _T( "Hold {pXbox_A,85,?} to jump higher!" ) );
	}

	void HintBlurb::MakeBackdrop()
	{
		Backdrop = std::make_shared<QuadClass>( 0, true, false );
		Backdrop->setTextureName( _T( "WidePlaque" ) );
		Backdrop->setSize( Vector2( 1250, 138 ) );
		Backdrop->setPos( Vector2( 0, 0 ) );

		MyPile->Add( Backdrop );
		MyPile->setPos( Vector2( 0, -800 ) );
	}

	void HintBlurb::OnAdd()
	{
		CkBaseMenu::OnAdd();

		// Remove all other hints
		for ( GameObjVec::const_iterator obj = MyGame->MyGameObjects.begin(); obj != MyGame->MyGameObjects.end(); ++obj )
		{
			if ( ( *obj ).get() == this )
				continue;

			std::shared_ptr<HintBlurb> blurb = std::dynamic_pointer_cast<HintBlurb>( *obj );
			if ( 0 != blurb )
				blurb->Kill();
		}
	}

	void HintBlurb::SlideIn( int Frames )
	{
		Pos->RelVal = Vector2( 0, 0 );
		Active = true;
		MyPile->BubbleUp( true );
	}

	void HintBlurb::SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames )
	{
		if ( Frames == 0 )
			return;

		Kill( true );
		Active = false;
	}

	void HintBlurb::SetText( const std::wstring &text )
	{
		// Erase previous text
		MyPile->MyTextList.clear();

		// Add the new text
		Text = std::make_shared<EzText>( text, ItemFont, 1800, false, false,.575f );
		Text->setScale( Text->getScale() * .74f );

		MyPile->Add( Text );
		SizeAndPosition();
	}

	void HintBlurb::SizeAndPosition()
	{
		Vector2 size = Text->GetWorldSize();
		float MaxSize = Backdrop->getSize().X - 100;
		if ( size.X / 2 > MaxSize )
			Backdrop->setSizeX( size.X / 2 + 100 );
			//Text.Scale *= MaxSize / (size.X / 2);

		Text->setPos( Vector2( -size.X / 2, size.Y *.85f ) );
	}

	void HintBlurb::MyPhsxStep()
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

	bool HintBlurb::ShouldDie()
	{
		return ButtonCheck::AllState( -1 ).Down && Step > 95 || ButtonCheck::GetDir( -1 ).Length() > ::5 && Step > 140 || ButtonCheck::State(ControllerButtons_B, -2).Pressed;
	}

	void HintBlurb::Kill()
	{
		Kill( true );
	}

	void HintBlurb::Kill( bool sound )
	{
		MyPile->BubbleDownAndFade( sound );
		ReleaseWhenDone = false;
		ReleaseWhenDoneScaling = true;
	}

	void HintBlurb::InitializeInstanceFields()
	{
		Step = 0;
	}
}
