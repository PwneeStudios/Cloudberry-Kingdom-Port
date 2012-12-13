#ifndef ARROWMENU
#define ARROWMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ArrowMenu : public CkBaseMenu
	{
	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;

	
		virtual void ReleaseBody();

	
		std::shared_ptr<SimpleMenuBase> MySimple;
		ArrowMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent, const std::shared_ptr<SimpleMenuBase> &MySimple );
		void ArrowMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent, const std::shared_ptr<SimpleMenuBase> &MySimple );

		virtual void Init();

	
		virtual void MyDraw();

	
		virtual void OnAdd();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef ARROWMENU
