#include <global_header.h>

namespace CloudberryKingdom
{

	MenuSliderNoSlide::MenuSliderNoSlide( const std::shared_ptr<EzText> &Text )
	{
		Init( Text, Text->Clone() );
		InitializeSlider();
	}

	MenuSliderNoSlide::MenuSliderNoSlide( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText )
	{
		Init( Text, SelectedText );
		InitializeSlider();
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
