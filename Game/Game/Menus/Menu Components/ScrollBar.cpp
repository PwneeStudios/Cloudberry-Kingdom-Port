#include <global_header.h>

namespace CloudberryKingdom
{

	ScrollBar::ScrollBarReleaseLambda::ScrollBarReleaseLambda( const boost::shared_ptr<ScrollBar> &sb )
	{
		this->sb = sb;
	}

	void ScrollBar::ScrollBarReleaseLambda::Apply()
	{
		sb->Release();
	}

	ScrollBar::SliderSetProxy::SliderSetProxy( const boost::shared_ptr<ScrollBar> &sb )
	{
		Sb = sb;
	}

	void ScrollBar::SliderSetProxy::Apply()
	{
		Sb->SliderSet();
	}

	ScrollBar::SliderGetLambda::SliderGetLambda( const boost::shared_ptr<ScrollBar> &sb )
	{
		this->sb = sb;
	}

	float ScrollBar::SliderGetLambda::Apply()
	{
		return sb->SliderGet();
	}

	void ScrollBar::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		AttachedMenu.reset();
		Parent.reset();
	}

	ScrollBar::ScrollBar( const boost::shared_ptr<LongMenu> &AttachedMenu, const boost::shared_ptr<GUI_Panel> &Parent ) :
		CkBaseMenu( false ),
		Height( 0 )
	{
	}
	boost::shared_ptr<ScrollBar> ScrollBar::ScrollBar_Construct( const boost::shared_ptr<LongMenu> &AttachedMenu, const boost::shared_ptr<GUI_Panel> &Parent )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->AttachedMenu = AttachedMenu;
		this->Parent = Parent;
		this->Parent->OnRelease->Add( boost::make_shared<ScrollBarReleaseLambda>( boost::static_pointer_cast<ScrollBar>( shared_from_this() ) ) );

		boost::shared_ptr<CkBaseMenu> ck = boost::dynamic_pointer_cast<CkBaseMenu>( Parent );
		if ( 0 != ck && ck->UseBounce )
		{
			EnableBounce();
			zoom = ck->zoom;
		}

		Constructor();

		return boost::static_pointer_cast<ScrollBar>( shared_from_this() );
	}

	void ScrollBar::Init()
	{
		CkBaseMenu::Init();

		// Make the menu
		MyMenu = boost::make_shared<Menu>( false );
		MyMenu->CheckForOutsideClick = false;
		MyMenu->AffectsOutsideMouse = false;

		MyMenu->OnB.reset();
		MyMenu->MouseOnly = true;
		setControl( -1 );

		EnsureFancy();

		slider = MakeMagic( MenuScrollBar, () );
		slider->setSliderBackSize( Vector2(1.15f,.72f) * slider->getSliderBackSize() );
		slider->CustomEndPoints = true;
		slider->CustomStart = Vector2( 0, -800 );
		slider->CustomEnd = Vector2( 0, 800 );
	#if defined(PC_VERSION)
		slider->BL_HitPadding.X += 50;
		slider->TR_HitPadding.X += 50;
	#endif
		slider->Slider->setTextureName( std::wstring( L"Floater_Spikey_Castle_v2" ) );
		slider->Slider->ScaleYToMatchRatio( 90 );
		slider->SliderBack->setTextureName( std::wstring( L"Floater_Chain_Forest" ) );
		slider->TabOffset = Vector2( 0, 28 );
		slider->setMyFloat( boost::make_shared<WrappedFloat>( 0.f, 0.f, 9.f ) );

		Height = AttachedMenu->Height();
		slider->getMyFloat()->GetCallback = boost::make_shared<SliderGetLambda>( boost::static_pointer_cast<ScrollBar>( shared_from_this() ) );
		slider->getMyFloat()->SetCallback = boost::make_shared<SliderSetProxy>( boost::static_pointer_cast<ScrollBar>( shared_from_this() ) );
		slider->getMyFloat()->MaxVal = Height;
		slider->getMyFloat()->MinVal = 0;

		MyMenu->Add( slider );

		slider->Pos = slider->PosOffset = slider->SelectedPos = Vector2();
	}

	float ScrollBar::SliderGet()
	{
		return Height - AttachedMenu->FancyPos->RelVal.Y;
	}

	void ScrollBar::SliderSet()
	{
		AttachedMenu->FancyPos->RelVal = Vector2( AttachedMenu->FancyPos->RelVal.X, Height - slider->getMyFloat()->MyFloat );
	}

	void ScrollBar::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

	#if defined(WINDOWS)
		slider->getMyFloat()->setVal(slider->getMyFloat()->getVal() + Tools::DeltaScroll *.9f); // .68f;
	#endif
	}

	const Vector2 &ScrollBar::getBarPos() const
	{
		return slider->Pos;
	}

	void ScrollBar::setBarPos( const Vector2 &value )
	{
		slider->Pos = value;
	}

	void ScrollBar::MyDraw()
	{
		CkBaseMenu::MyDraw();
	}

	void ScrollBar::OnAdd()
	{
		CkBaseMenu::OnAdd();

		Pos->SetCenter( Parent->Pos );
		SlideIn( 0 );
	}
}
