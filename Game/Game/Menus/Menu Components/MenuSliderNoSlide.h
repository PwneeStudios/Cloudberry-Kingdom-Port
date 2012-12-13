#ifndef MENUSLIDERNOSLIDE
#define MENUSLIDERNOSLIDE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuSliderNoSlide : public MenuSliderBase
	{
	
		MenuSliderNoSlide( const std::shared_ptr<EzText> &Text );

		MenuSliderNoSlide( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

#if defined(PC_VERSION)
	
		virtual void PC_OnLeftMouseDown();
#endif
	};
}


#endif	//#ifndef MENUSLIDERNOSLIDE
