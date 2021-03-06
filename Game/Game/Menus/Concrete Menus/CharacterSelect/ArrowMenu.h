#ifndef ARROWMENU
#define ARROWMENU

#include <small_header.h>

//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/SimpleMenu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"


namespace CloudberryKingdom
{

	struct ArrowMenu : public CkBaseMenu
	{
	
		virtual ~ArrowMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "ArrowMenu" );
#endif
		}


		boost::shared_ptr<CharacterSelect> MyCharacterSelect;

	
		virtual void ReleaseBody();

	
		boost::shared_ptr<SimpleMenuBase> MySimple;
		ArrowMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent, const boost::shared_ptr<SimpleMenuBase> &MySimple );
		boost::shared_ptr<ArrowMenu> ArrowMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent, const boost::shared_ptr<SimpleMenuBase> &MySimple );

		virtual void Init();

	
		virtual void MyDraw();

	
		virtual void OnAdd();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef ARROWMENU
