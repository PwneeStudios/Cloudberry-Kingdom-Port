#include <small_header.h>
#include "Game/Menus/Menu Components/MenuSliderNoSlide.h"

#include "Core/Input/ButtonCheck.h"
#include "Core/Text/EzText.h"
#include "Game/Menus/Menu Components/MenuSliderBase.h"

#include "Game/Tools/WrappedFloat.h"

namespace CloudberryKingdom
{

	MenuSliderNoSlide::MenuSliderNoSlide( const boost::shared_ptr<EzText> &Text )
	{
	}
	boost::shared_ptr<MenuSliderNoSlide> MenuSliderNoSlide::MenuSliderNoSlide_Construct( const boost::shared_ptr<EzText> &Text )
	{
		Init( Text, Text->Clone() );
		InitializeSlider();

		return boost::static_pointer_cast<MenuSliderNoSlide>( shared_from_this() );
	}

	MenuSliderNoSlide::MenuSliderNoSlide( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText )
	{
	}
	boost::shared_ptr<MenuSliderNoSlide> MenuSliderNoSlide::MenuSliderNoSlide_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText )
	{
		Init( Text, SelectedText );
		InitializeSlider();

		return boost::static_pointer_cast<MenuSliderNoSlide>( shared_from_this() );
	}

#if defined(PC_VERSION)
	void MenuSliderNoSlide::PC_OnLeftMouseDown()
	{
		if ( !ButtonCheck::State( ControllerButtons_A, Control ).Pressed )
			return;

		if ( getMyFloat()->getVal() == getMyFloat()->MaxVal )
			getMyFloat()->setVal(getMyFloat()->MinVal);
		else
			getMyFloat()->setVal(getMyFloat()->getVal() + 1);

		Slide();
	}
#endif
}
