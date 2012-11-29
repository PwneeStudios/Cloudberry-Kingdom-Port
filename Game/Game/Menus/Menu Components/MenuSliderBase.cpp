#include <global_header.h>
namespace CloudberryKingdom
{

	MenuSliderBase::SetCallbackProxy::SetCallbackProxy( const std::shared_ptr<MenuSliderBase> &msb )
	{
		Msb = msb;
	}

	void MenuSliderBase::SetCallbackProxy::Apply()
	{
		Msb->SetCallback();
	}

	const bool &MenuSliderBase::getIsMaxed() const
	{
		return getMyFloat()->getVal() == getMyFloat()->MaxVal;
	}

	void MenuSliderBase::Slide()
	{
		if ( OnSlide != 0 )
			OnSlide->Apply();
	}

	const Vector2 &MenuSliderBase::getBL() const
	{
		return Vector2();
	}

	const Vector2 &MenuSliderBase::getTR() const
	{
		return Vector2();
	}

	const Vector2 &MenuSliderBase::getSlider_TR() const
	{
		return Vector2();
	}

	const float &MenuSliderBase::getVal() const
	{
		return getMyFloat()->getVal();
	}

	void MenuSliderBase::setVal( const float &value )
	{
		getMyFloat()->setVal(value);
		if ( OnSetValue != 0 )
			OnSetValue->Apply();
	}

	const std::shared_ptr<WrappedFloat> &MenuSliderBase::getMyFloat() const
	{
		return _MyFloat;
	}

	void MenuSliderBase::setMyFloat( const std::shared_ptr<WrappedFloat> &value )
	{
		_MyFloat = value;
		_MyFloat->SetCallback = std::make_shared<SetCallbackProxy>( shared_from_this() );
		SetCallback();
	}

	MenuSliderBase::MenuSliderBase()
	{
		InitializeInstanceFields();
		std::shared_ptr<EzText> NoText = std::make_shared<EzText>( _T( "" ), Resources::Font_Grobold42 );
		Init( NoText, NoText->Clone() );
		InitializeSlider();
	}

	MenuSliderBase::MenuSliderBase( const std::shared_ptr<EzText> &Text )
	{
		InitializeInstanceFields();
		Init( Text, Text->Clone() );
		InitializeSlider();
	}

	MenuSliderBase::MenuSliderBase( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText )
	{
		InitializeInstanceFields();
		Init( Text, SelectedText );
		InitializeSlider();
	}

	void MenuSliderBase::InitializeSlider()
	{
		BaseString = MyText->MyString;
		SelectionOscillate = false;

		setOverrideA( false );
	}

	void MenuSliderBase::SetCallback()
	{
		if ( ShowText )
			UpdateText();

		if ( OnSetValue != 0 )
			OnSetValue->Apply();
	}

	void MenuSliderBase::Release()
	{
		MenuItem::Release();

		getMyFloat()->Release();
	}

#if defined(PC_VERSION)
	bool MenuSliderBase::HitTest( Vector2 pos, Vector2 padding )
	{
		CalcEndPoints();

		bool Hit = Phsx::Inside( pos, Start - Vector2( 0, 50 ) - BL_HitPadding, End + Vector2( 0, 50 ) + TR_HitPadding, padding );
		Hit |= MenuItem::HitTest( pos, padding );

		return Hit;
	}
#endif

	void MenuSliderBase::CalcEndPoints()
	{
		Start = End = Vector2();
	}

	std::wstring MenuSliderBase::ToString()
	{
		return BaseString + StringConverterHelper::toString( static_cast<int>( getMyFloat()->getVal() ) );
	}

	void MenuSliderBase::UpdateText()
	{
		MyText->SubstituteText( ToString() );
		MySelectedText->SubstituteText( ToString() );
	}

	void MenuSliderBase::SetToShowText()
	{
		ShowText = true;
		UpdateText();
	}

#if defined(PC_VERSION)
	void MenuSliderBase::PC_OnLeftMouseDown()
	{
		if ( !ButtonCheck::MouseInUse )
			return;

		MyMenu->HasSelectedThisStep = true;

		CalcEndPoints();
		Vector2 MousePos = Tools::MouseGUIPos( getMyCameraZoom() );

		Vector2 dif, tangent;

		if ( Inverted )
		{
			dif = MousePos - End;
			tangent = Start - End;
		}
		else
		{
			dif = MousePos - Start;
			tangent = End - Start;
		}

		float length = tangent.Length();
		float t = Vector2::Dot( dif, tangent ) / ( length * length );

		t = CoreMath::Restrict( 0, 1, t );

		getMyFloat()->setVal((1 - t) * getMyFloat()->MinVal + t * getMyFloat()->MaxVal);

		Slide();
	}
#endif

	void MenuSliderBase::PhsxStep( bool Selected )
	{
		MenuItem::PhsxStep( Selected );

		if ( !Selected )
			return;

		if ( Speed < InitialSlideSpeed )
			Speed = InitialSlideSpeed;

		float CurVal = getMyFloat()->getVal();

	#if defined(PC_VERSION)
		if ( ButtonCheck::State( ControllerButtons_A, Control ).Down && !ButtonCheck::KeyboardGo() )
		{
			PC_OnLeftMouseDown();
		}
	#endif

		// Quick slide
		if ( ButtonCheck::State( ControllerButtons_LS, Control ).Pressed )
		{
			getMyFloat()->setVal(getMyFloat()->MinVal);
			Slide();
		}
		if ( ButtonCheck::State( ControllerButtons_RS, Control ).Pressed )
		{
			getMyFloat()->setVal(getMyFloat()->MaxVal);
			Slide();
		}

		Vector2 Dir = Vector2();
		if ( Control < 0 )
			Dir = ButtonCheck::GetMaxDir();
		else
			Dir = ButtonCheck::GetDir( Control );

		if ( Discrete )
		{
			if ( DelayCount > 0 )
				DelayCount--;
			else
			{
				float Sensitivty = ButtonCheck::ThresholdSensitivity;
				if ( abs( Dir.X ) > Sensitivty )
				{
					getMyFloat()->setVal(static_cast<int>(getMyFloat()->getVal()) + Math::Sign(Dir.X));
					Slide();

					DelayCount = SelectDelay;
				}
			}
		}
		else
		{
			if ( abs( Dir.X ) > ::5 )
			{
				getMyFloat()->setVal(getMyFloat()->getVal() + Dir.X * Speed);
				Slide();

				Speed = Acceleration * MaxSlideSpeed + ( 1 - Acceleration ) * Speed;
			}

			if ( abs( Dir.X ) < .5f || Math::Sign( Dir.X ) != Math::Sign( PrevDir.X ) )
				Speed = InitialSlideSpeed;
		}

		if ( CurVal != getMyFloat()->getVal() )
		{
			if ( DelayToSlideSoundCount > DelayToSlideSound )
			{
				DelayToSlideSoundCount = 0;
				if ( SlideSound != 0 )
					SlideSound->Play();
			}
		}

		DelayToSlideSoundCount++;

		PrevDir = Dir;
	}

	void MenuSliderBase::InitializeInstanceFields()
	{
		DelayToSlideSound = Menu::DefaultMenuInfo::Menu_Slide_SoundDelay;
		DelayToSlideSoundCount = 0;
		InitialSlideSpeed = 1 / 55;
		MaxSlideSpeed = 3.5f / 55;
		Acceleration = .03f;
		Speed = 0;
#if defined(PC_VERSION)
		BL_HitPadding = Vector2();
		TR_HitPadding = Vector2();
#endif
		ShowText = false;
		Inverted = false;
	}
}
