#include <global_header.h>

namespace CloudberryKingdom
{

	ScrollBar::ScrollBarReleaseLambda::ScrollBarReleaseLambda( const std::shared_ptr<ScrollBar> &sb )
	{
		this->sb = sb;
	}

	void ScrollBar::ScrollBarReleaseLambda::Apply()
	{
		sb->Release();
	}

	ScrollBar::SliderSetProxy::SliderSetProxy( const std::shared_ptr<ScrollBar> &sb )
	{
		Sb = sb;
	}

	void ScrollBar::SliderSetProxy::Apply()
	{
		Sb->SliderSet();
	}

	ScrollBar::SliderGetLambda::SliderGetLambda( const std::shared_ptr<ScrollBar> &sb )
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

	ScrollBar::ScrollBar( const std::shared_ptr<LongMenu> &AttachedMenu, const std::shared_ptr<GUI_Panel> &Parent ) : CkBaseMenu( false ) { }
	void ScrollBar::ScrollBar_Construct( const std::shared_ptr<LongMenu> &AttachedMenu, const std::shared_ptr<GUI_Panel> &Parent )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->AttachedMenu = AttachedMenu;
		this->Parent = Parent;
		this->Parent->OnRelease->Add( std::make_shared<ScrollBarReleaseLambda>( std::static_pointer_cast<ScrollBar>( shared_from_this() ) ) );

		Constructor();
	}

	void ScrollBar::Init()
	{
		CkBaseMenu::Init();

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->CheckForOutsideClick = false;
		MyMenu->AffectsOutsideMouse = false;

		MyMenu->OnB.reset();
		MyMenu->MouseOnly = true;
		setControl( -1 );

		EnsureFancy();

		slider = std::make_shared<MenuScrollBar>();
		slider->setSliderBackSize( Vector2(1.15f,.72f) * slider->getSliderBackSize() );
		slider->CustomEndPoints = true;
		slider->CustomStart = Vector2( 0, -800 );
		slider->CustomEnd = Vector2( 0, 800 );
	#if defined(PC_VERSION)
		slider->BL_HitPadding.X += 50;
		slider->TR_HitPadding.X += 50;
	#endif
		slider->Slider->setTextureName( _T( "BouncyBlock_Castle" ) );
		slider->Slider->ScaleYToMatchRatio( 90 );
		slider->SliderBack->setTextureName( _T( "Chain_Tile" ) );
		slider->TabOffset = Vector2( 0, 28 );
		slider->setMyFloat( std::make_shared<WrappedFloat>( 0.f, 0.f, 9.f ) );

		Height = AttachedMenu->Height();
		slider->getMyFloat()->GetCallback = std::make_shared<SliderGetLambda>( std::static_pointer_cast<ScrollBar>( shared_from_this() ) );
		slider->getMyFloat()->SetCallback = std::make_shared<SliderSetProxy>( std::static_pointer_cast<ScrollBar>( shared_from_this() ) );
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
