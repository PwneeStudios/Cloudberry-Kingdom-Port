#include <global_header.h>

namespace CloudberryKingdom
{

	HintBlurb::HintBlurb() :
		Step( 0 )
	{
	}
	boost::shared_ptr<HintBlurb> HintBlurb::HintBlurb_Construct()
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct();
		
		PauseOnPause = false;
		setPauseLevel( false );
		FixedToCamera = true;
		getCore()->RemoveOnReset = false;

		MyPile = boost::make_shared<DrawPile>();

		MakeBackdrop();

		SetText( std::wstring( L"Hold {pXbox_A,85,?} to jump higher!" ) );

		return boost::static_pointer_cast<HintBlurb>( shared_from_this() );
	}

	void HintBlurb::MakeBackdrop()
	{
		Backdrop = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true, false );
		Backdrop->setTextureName( std::wstring( L"WidePlaque" ) );
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

			boost::shared_ptr<HintBlurb> blurb = boost::dynamic_pointer_cast<HintBlurb>( *obj );
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

	void HintBlurb::SlideOut( PresetPos Preset, int Frames )
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
		Text = boost::make_shared<EzText>( text, ItemFont, 1800.f, false, false, .575f );
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
		return ButtonCheck::AllState( -1 ).Down && Step > 95 || ButtonCheck::GetDir( -1 ).Length() > .5f && Step > 140 || ButtonCheck::State(ControllerButtons_B, -2).Pressed;
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
