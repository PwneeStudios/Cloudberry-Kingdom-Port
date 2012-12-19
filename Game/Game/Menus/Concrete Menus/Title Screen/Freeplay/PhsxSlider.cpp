#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	PhsxSlider::PhsxDataSetter::PhsxDataSetter( BobPhsx::CustomData MyType, const boost::shared_ptr<WrappedFloat> &MyFloat )
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
		std::wstring tempVector[] = { std::wstring( L"Pos" ), std::wstring( L"SelectedPos" ), std::wstring( L"!MyMenu" ), std::wstring( L"SliderShift" ), std::wstring( L"!MenuToAddTo" ) };
		return VecFromArray( tempVector );
	}

	boost::shared_ptr<EzFont> PhsxSlider::Font = 0;
	boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > PhsxSlider::Process = 0;

	PhsxSlider::PhsxSlider( Localization::Words word, BobPhsx::CustomData type ) : MenuSlider( boost::make_shared<EzText>( word, Font ) )
	{
		InitializeInstanceFields();
		MyType = type;

		setMyFloat( boost::make_shared<WrappedFloat>( CustomHero_GUI::HeroPhsxData[ MyType ], BobPhsx::CustomPhsxData::Bounds( type ).MinValue, BobPhsx::CustomPhsxData::Bounds( type ).MaxValue ) );
								   //CustomHero_GUI.Hero.MyCustomPhsxData[type],
								   //BobPhsx.CustomPhsxData.Bounds(type).DefaultValue,
		Process->Apply( shared_from_this() );
		ScaleText( .33f );

		getMyFloat()->SetCallback = boost::make_shared<PhsxDataSetter>(MyType, getMyFloat());

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
