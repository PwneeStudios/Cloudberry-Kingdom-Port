#include <global_header.h>

namespace CloudberryKingdom
{

	LengthSlider::LengthSlider()
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<LengthSlider> LengthSlider::LengthSlider_Construct()
	{
		MenuSliderBase::MenuSliderBase_Construct();

		return boost::static_pointer_cast<LengthSlider>( shared_from_this() );
	}

	LengthSlider::LengthSlider( const boost::shared_ptr<EzText> &Text )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<LengthSlider> LengthSlider::LengthSlider_Construct( const boost::shared_ptr<EzText> &Text )
	{
		MenuSliderBase::MenuSliderBase_Construct();

		Init( Text, Text->Clone() );
		InitializeSlider();

		return boost::static_pointer_cast<LengthSlider>( shared_from_this() );
	}

	LengthSlider::LengthSlider( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<LengthSlider> LengthSlider::LengthSlider_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText )
	{
		MenuSliderBase::MenuSliderBase_Construct();

		Init( Text, SelectedText );
		InitializeSlider();

		return boost::static_pointer_cast<LengthSlider>( shared_from_this() );
	}

	void LengthSlider::InitializeSlider()
	{
		MenuSliderBase::InitializeSlider();

	#if defined(PC_VERSION)
		BL_HitPadding = Vector2( 200, 30 );
	#endif
		LengthBar = boost::make_shared<ProgressBar>( std::wstring( L"Length" ), std::wstring( L"LengthBack" ), 850.f );
		LengthBar->MyType = ProgressBar::BarType_REVEAL;

		LengthBar->Outline->Shadow = false;
		//LengthBar->MyPile->MyOscillateParams.Set( 2,.99f,.05f );
		LengthBar->MyPile->MyOscillateParams.Set( 1.85f, .99f, .0205f );

		setMyFloat( boost::make_shared<WrappedFloat>( 8000.f, 3000.f, 15000.f ) );
		PerceivedMin = 500;
		InitialSlideSpeed = 120;
		MaxSlideSpeed = 550;
	}

	const Vector2 LengthSlider::getBL() const
	{
		return LengthBar->getFull_BL();
	}

	const Vector2 LengthSlider::getTR() const
	{
		return LengthBar->getFull_TR();
	}

	const Vector2 LengthSlider::getSlider_TR() const
	{
		return LengthBar->getCurrent_TR();
	}

	void LengthSlider::SetCallback()
	{
		MenuSliderBase::SetCallback();

		LengthBar->SetPercent( 100 * ( getMyFloat()->getVal() - PerceivedMin ) / (getMyFloat()->MaxVal - PerceivedMin) );
	}

	void LengthSlider::CalcEndPoints()
	{
		float min_ratio = ( getMyFloat()->MinVal - PerceivedMin ) / (getMyFloat()->MaxVal - PerceivedMin);
		Start = LengthBar->getFull_BL();
		End = LengthBar->getFull_TR();

		Start = Start + min_ratio * ( End - Start );
	}

	void LengthSlider::Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected )
	{
		MenuSliderBase::Draw( Text, cam, Selected );

		if ( MyDrawLayer != MyMenu->CurDrawLayer )
			return;

		if ( !Text )
		{
			LengthBar->setPos( Pos + PosOffset );
			LengthBar->Draw( Selected );
		}
	}

	void LengthSlider::InitializeInstanceFields()
	{
		PerceivedMin = 0;
	}
}
