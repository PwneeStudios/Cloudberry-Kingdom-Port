#ifndef MENUTOGGLE
#define MENUTOGGLE

#include <small_header.h>

//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/Menu Components/MenuItem.h"


namespace CloudberryKingdom
{

	struct MenuToggle : public MenuItem
	{

		virtual ~MenuToggle()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuToggle" );
#endif
		}

	
		MenuToggle( const boost::shared_ptr<EzFont> &Font );
		boost::shared_ptr<MenuToggle> MenuToggle_Construct( const boost::shared_ptr<EzFont> &Font );
	
		bool MyState;
	
		void Toggle( bool state );

		boost::shared_ptr<Lambda_1<bool> > OnToggle;
		virtual void PhsxStep( bool Selected );
	
		void InitializeInstanceFields();

	};

}


#endif	//#ifndef MENUTOGGLE
