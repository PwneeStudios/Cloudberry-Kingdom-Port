#ifndef MENUSLIDERNOSLIDE
#define MENUSLIDERNOSLIDE

#include <small_header.h>

//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/Menu Components/MenuSliderBase.h"


namespace CloudberryKingdom
{

	struct MenuSliderNoSlide : public MenuSliderBase
	{

		virtual ~MenuSliderNoSlide()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuSliderNoSlide" );
#endif
		}

	
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
