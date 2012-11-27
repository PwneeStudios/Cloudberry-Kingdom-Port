#include <global_header.h>


namespace CloudberryKingdom
{

	LengthSlider::LengthSlider()
	{
		InitializeInstanceFields();
	}

	LengthSlider::LengthSlider( const std::shared_ptr<EzText> &Text )
	{
		InitializeInstanceFields();
		Init( Text, Text->Clone() );
		InitializeSlider();
	}

	LengthSlider::LengthSlider( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText )
	{
		InitializeInstanceFields();
		Init( Text, SelectedText );
		InitializeSlider();
	}

	void LengthSlider::InitializeSlider()
	{
		MenuSliderBase::InitializeSlider();

	#if defined(PC_VERSION)
		BL_HitPadding = Vector2( 200, 30 );
	#endif
		LengthBar = std::make_shared<ProgressBar>( _T( "Length" ), _T( "LengthBack" ), 850 );
		LengthBar->MyType = ProgressBar::BarType_REVEAL;

		LengthBar->Outline->Shadow = false;
		LengthBar->MyPile->MyOscillateParams.Set( 2,.99f,.05f );

		setMyFloat( std::make_shared<WrappedFloat>( 8000, 3000, 15000 ) );
		PerceivedMin = 500;
		InitialSlideSpeed = 120;
		MaxSlideSpeed = 550;
	}

	const Vector2 &LengthSlider::getBL() const
	{
		return LengthBar->getFull_BL();
	}

	const Vector2 &LengthSlider::getTR() const
	{
		return LengthBar->getFull_TR();
	}

	const Vector2 &LengthSlider::getSlider_TR() const
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

	void LengthSlider::Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected )
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
