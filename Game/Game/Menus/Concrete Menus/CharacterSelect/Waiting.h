#ifndef WAITING
#define WAITING

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Input/ButtonCheck.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"


namespace CloudberryKingdom
{

	struct Waiting : public CkBaseMenu
	{
	
		virtual ~Waiting()
		{
#ifdef BOOST_BIN
			OnDestructor( "Waiting" );
#endif
		}


		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
		bool CanGoBack;
	
		Waiting( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect, bool _CanGoBack );
		boost::shared_ptr<Waiting> Waiting_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect, bool _CanGoBack );
	
		virtual void ReleaseBody();
	
		virtual void Init();

		void MyDraw();
	
		virtual void MyPhsxStep();

	};
}


#endif	//#ifndef WAITING
