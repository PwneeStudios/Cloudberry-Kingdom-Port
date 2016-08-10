#ifndef BACKDROP
#define BACKDROP

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct CharSelectBackdrop : public CkBaseMenu
	{

		virtual ~CharSelectBackdrop()
		{
#ifdef BOOST_BIN
			OnDestructor( "CharSelectBackdrop" );
#endif
		}

	
		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

		CharSelectBackdrop();
		boost::shared_ptr<CharSelectBackdrop> CharSelectBackdrop_Construct();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( PresetPos Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

		void MyDraw();
		void SetPos();
	};
}


#endif	//#ifndef BACKDROP
