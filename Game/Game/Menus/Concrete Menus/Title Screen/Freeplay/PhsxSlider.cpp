#include <global_header.h>





namespace CloudberryKingdom
{

	PhsxSlider::PhsxDataSetter::PhsxDataSetter( BobPhsx::CustomData MyType, const std::shared_ptr<WrappedFloat> &MyFloat )
	{
		this->MyType = MyType;
		this->MyFloat = MyFloat;
	}

	void PhsxSlider::PhsxDataSetter::Apply()
	{
		CustomHero_GUI::HeroPhsxData[ MyType ] = MyFloat->getVal();
	}

	std::vector<std::wstring> PhsxSlider::GetViewables()
	{
		const std::wstring* tempVector[] = { _T( "Pos" ), _T( "SelectedPos" ), _T( "!MyMenu" ), _T( "SliderShift" ), _T( "!MenuToAddTo" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

std::shared_ptr<EzFont> PhsxSlider::Font = 0;
std::shared_ptr<Lambda_1<MenuItem*> > PhsxSlider::Process = 0;

	PhsxSlider::PhsxSlider( Localization::Words word, BobPhsx::CustomData type ) : MenuSlider( std::make_shared<EzText>( word, Font ) )
	{
		InitializeInstanceFields();
		MyType = type;

		setMyFloat( std::make_shared<WrappedFloat>( CustomHero_GUI::HeroPhsxData[ MyType ], BobPhsx::CustomPhsxData::Bounds( type ).MinValue, BobPhsx::CustomPhsxData::Bounds( type ).MaxValue ) );
								   //CustomHero_GUI.Hero.MyCustomPhsxData[type],
								   //BobPhsx.CustomPhsxData.Bounds(type).DefaultValue,
		Process->Apply( this );
		ScaleText( .33f );

		getMyFloat()->SetCallback = std::make_shared<PhsxDataSetter>(MyType, getMyFloat());

		SliderShift = Vector2( -296.6946f, -57.77405f );

		Slider->Scale( .66f );
		SliderBack->Scale( .73f );
		Start *= .8f;
		End *= .8f;

		GrayOutOnUnselectable = true;
	}

	void PhsxSlider::setState( const bool &value )
	{
		_State = value;
		if ( getState() )
		{
			MyText->Alpha = MySelectedText->Alpha = 1;
		}
		else
		{
			MyText->Alpha = MySelectedText->Alpha = .3f;
		}
	}

	const bool &PhsxSlider::getState() const
	{
		return _State;
	}

	void PhsxSlider::InitializeInstanceFields()
	{
		_State = true;
	}
}
