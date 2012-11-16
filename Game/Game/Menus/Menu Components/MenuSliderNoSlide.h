#ifndef MENUSLIDERNOSLIDE
#define MENUSLIDERNOSLIDE

#include "MenuSliderBase.h"

namespace CloudberryKingdom
{
	class EzText;
}


namespace CloudberryKingdom
{
	class MenuSliderNoSlide : public MenuSliderBase
	{
	public:
		MenuSliderNoSlide( const std::shared_ptr<EzText> &Text );

		MenuSliderNoSlide( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

#if defined(PC_VERSION)
	protected:
		virtual void PC_OnLeftMouseDown();
#endif
	};
}


#endif	//#ifndef MENUSLIDERNOSLIDE
