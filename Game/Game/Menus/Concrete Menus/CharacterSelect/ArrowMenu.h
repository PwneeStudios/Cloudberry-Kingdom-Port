#ifndef ARROWMENU
#define ARROWMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ArrowMenu : public CkBaseMenu
	{
	
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
