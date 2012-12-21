#ifndef MENUSLIDERNOSLIDE
#define MENUSLIDERNOSLIDE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct MenuSliderNoSlide : public MenuSliderBase
	{
	
		MenuSliderNoSlide( const boost::shared_ptr<EzText> &Text );
		MenuSliderNoSlide( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		boost::shared_ptr<MenuSliderNoSlide> MenuSliderNoSlide_Construct( const boost::shared_ptr<EzText> &Text );
		boost::shared_ptr<MenuSliderNoSlide> MenuSliderNoSlide_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

#if defined(PC_VERSION)
	
		virtual void PC_OnLeftMouseDown();
#endif
	};

}


#endif	//#ifndef MENUSLIDERNOSLIDE
